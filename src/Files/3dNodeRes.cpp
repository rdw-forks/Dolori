#include "Files/3dNodeRes.h"

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Common/Globals.h"
#include "Common/debug.h"
#include "Render/Renderer.h"

C3dNodeRes::C3dNodeRes() : info(), offset_matrix(), vbo(nullptr) {}

void C3dNodeRes::Load(uint16_t version, CFile& file) {
  char buffer[0x28];

  vbo = nullptr;

  file.Read(&buffer, sizeof(buffer));
  buffer[sizeof(buffer) - 1] = '\0';
  name = buffer;
  file.Read(&buffer, sizeof(buffer));
  buffer[sizeof(buffer) - 1] = '\0';
  parentname = buffer;

  // Textures
  int32_t textures_count;
  file.Read(&textures_count, sizeof(textures_count));

  textures.resize(textures_count);
  file.Read(textures.data(), textures_count * sizeof(textures[0]));

  // Info
  file.Read(&info, sizeof(info));

  offset_matrix = glm::mat4();
  offset_matrix[0][0] = info.mat3[0];
  offset_matrix[0][1] = info.mat3[1];
  offset_matrix[0][2] = info.mat3[2];

  offset_matrix[1][0] = info.mat3[3];
  offset_matrix[1][1] = info.mat3[4];
  offset_matrix[1][2] = info.mat3[5];

  offset_matrix[2][0] = info.mat3[6];
  offset_matrix[2][1] = info.mat3[7];
  offset_matrix[2][2] = info.mat3[8];

  position = glm::make_vec3(info.position);
  offset_vector = glm::make_vec3(info.offset);

  // Vertices
  int32_t vertices_count;
  file.Read(&vertices_count, sizeof(vertices_count));

  vertices.resize(vertices_count);
  file.Read(vertices.data(), vertices_count * sizeof(vertices[0]));

  // Texture vertices
  int32_t tex_vertices_count;
  file.Read(&tex_vertices_count, sizeof(tex_vertices_count));

  tex_vertices.resize(tex_vertices_count);
  for (int32_t i = 0; i < tex_vertices_count; i++) {
    if (version >= 0x102) {
      file.Read(&tex_vertices[i].color, sizeof(tex_vertices[i].color));
    } else {
      tex_vertices[i].color = 0;
    }

    file.Read(&tex_vertices[i].position, sizeof(tex_vertices[i].position));
  }

  // Faces
  int32_t faces_count;
  file.Read(&faces_count, sizeof(faces_count));

  faces.resize(faces_count);
  for (int32_t i = 0; i < faces_count; i++) {
    file.Read(&faces[i], sizeof(faces[i]) - sizeof(faces[i].smooth_group));
    if (version >= 0x102) {
      file.Read(&faces[i].smooth_group, sizeof(faces[i].smooth_group));
    } else {
      faces[i].smooth_group = 0;
    }
  }

  // Position keys
  if (version >= 0x105) {
    int32_t poskeyframe_count;
    file.Read(&poskeyframe_count, sizeof(poskeyframe_count));

    poskeyframes.resize(poskeyframe_count);
    for (int32_t i = 0; i < poskeyframe_count; i++) {
      file.Read(&poskeyframes[i], sizeof(poskeyframes[i]));
    }
  }

  // Rotation keys
  int32_t rotkeyframe_count;
  file.Read(&rotkeyframe_count, sizeof(rotkeyframe_count));

  rotkeyframes.resize(rotkeyframe_count);
  for (int32_t i = 0; i < rotkeyframe_count; i++) {
    file.Read(&rotkeyframes[i], sizeof(rotkeyframes[i]));
  }
}

void C3dNodeRes::FetchChildren(
    const std::map<std::string, std::shared_ptr<C3dNodeRes>>& nodes) {
  for (auto node : nodes) {
    if (node.second.get() != this && node.second->parentname == name) {
      node.second->parent = this;
      children.push_back(node.second);
    }
  }

  for (auto child : children) {
    child->FetchChildren(nodes);
  }
}

void C3dNodeRes::ComputeModelViewMatrix(const C3dActor* model) {
  modelview_matrix = glm::mat4();

  if (parent == nullptr) {
    if (!children.empty()) {
      modelview_matrix =
          glm::translate(modelview_matrix,
                         glm::vec3(-model->GetBbRange().x, -model->GetBbMax().y,
                                   -model->GetBbRange().z));
    } else {
      modelview_matrix = glm::translate(
          modelview_matrix,
          glm::vec3(0, -model->GetBbMax().y + model->GetBbRange().y, 0));
    }
  } else {
    modelview_matrix = glm::translate(modelview_matrix, position);
  }

  if (rotkeyframes.empty()) {
    if (fabs(info.rot_angle) > 0.01) {
      modelview_matrix = glm::rotate(
          modelview_matrix, glm::radians(info.rot_angle * 180.0f / 3.14159f),
          glm::make_vec3(info.rot_axis));
    }
  } else {
    // TODO(LinkZ): Animation
    const auto quaternion = glm::make_quat(rotkeyframes[0].quaternion);
    modelview_matrix *= glm::mat4_cast(glm::normalize(quaternion));
  }

  modelview_matrix = glm::scale(modelview_matrix, glm::make_vec3(info.scale));

  for (auto child : children) {
    child->ComputeModelViewMatrix(model);
  }
}
void C3dNodeRes::ComputeNodeViewMatrix(const C3dActor* model) {
  nodeview_matrix = glm::mat4();

  if (parent == nullptr && children.empty()) {
    nodeview_matrix =
        glm::translate(nodeview_matrix, -1.0f * model->GetBbRange());
  } else {
    nodeview_matrix = glm::translate(nodeview_matrix, offset_vector);
  }

  nodeview_matrix *= offset_matrix;

  for (auto child : children) {
    child->ComputeNodeViewMatrix(model);
  }
}

void C3dNodeRes::ComputeBoundingBox(glm::vec3& bbmin_out,
                                    glm::vec3& bbmax_out) {
  if (parent != nullptr) {
    bbmin = glm::vec3(0, 0, 0);
    bbmax = glm::vec3(0, 0, 0);
  } else {
    bbmin = glm::vec3(INT_MAX, INT_MAX, INT_MAX);
    bbmax = glm::vec3(INT_MIN, INT_MIN, INT_MIN);
  }

  for (const auto& face : faces) {
    for (int ii = 0; ii < 3; ii++) {
      auto v = glm::vec4(vertices[face.vertex_id[ii]].position, 1);
      v = offset_matrix * v;
      if (parent != nullptr || !children.empty()) {
        v += glm::vec4(position + offset_vector, 1);
      }

      for (int c = 0; c < 3; c++) {
        bbmin[c] = glm::min(bbmin[c], v[c]);
        bbmax[c] = glm::max(bbmax[c], v[c]);
      }
    }
  }

  bbrange = (bbmin + bbmax) / 2.0f;

  for (int c = 0; c < 3; c++) {
    bbmax_out[c] = glm::max(bbmax_out[c], bbmax[c]);
    bbmin_out[c] = glm::min(bbmin_out[c], bbmin[c]);
  }

  for (auto child : children) {
    child->ComputeBoundingBox(bbmin_out, bbmax_out);
  }
}

void C3dNodeRes::ComputeRealBoundingBox(const glm::mat4& matrix,
                                        glm::vec3& bbmin_out,
                                        glm::vec3& bbmax_out) {
  const glm::mat4 mat2 = matrix * modelview_matrix * nodeview_matrix;
  for (const auto& face : faces) {
    for (int ii = 0; ii < 3; ii++) {
      const glm::vec4 v =
          mat2 * glm::vec4(vertices[face.vertex_id[ii]].position, 1);
      bbmin_out.x = glm::min(bbmin_out.x, v.x);
      bbmin_out.y = glm::min(bbmin_out.y, v.y);
      bbmin_out.z = glm::min(bbmin_out.z, v.z);

      bbmax_out.x = glm::max(bbmax_out.x, v.x);
      bbmax_out.y = glm::max(bbmax_out.y, v.y);
      bbmax_out.z = glm::max(bbmax_out.z, v.z);
    }
  }

  const glm::mat4 mat1 = matrix * modelview_matrix;
  for (auto child : children) {
    child->ComputeRealBoundingBox(mat1, bbmin_out, bbmax_out);
  }
}

void C3dNodeRes::Render(const C3dActor* model, const glm::mat4& matrix) {
  if (vbo == nullptr) {
    // Generate the vbo
    vbo = std::make_shared<CGlVBO>();
    vbo->SetVertexFormat<VertexP3T2N3>();

    // Sort vertices by texture
    std::unordered_map<int32_t, std::vector<VertexP3T2N3>> verts_by_texid;
    for (const auto& face : faces) {
      const auto tex_id = textures[face.tex_id];
      for (size_t v = 0; v < 3; v++) {
        const glm::vec3 normal = glm::normalize(
            glm::cross(vertices[face.vertex_id[1]].position -
                           vertices[face.vertex_id[0]].position,
                       vertices[face.vertex_id[2]].position -
                           vertices[face.vertex_id[0]].position));
        verts_by_texid[tex_id].push_back(
            {vertices[face.vertex_id[v]].position,
             tex_vertices[face.tex_vertex_id[v]].position, normal});
      }
    }

    std::vector<VertexP3T2N3> sorted_vertices;
    for (const auto& pair : verts_by_texid) {
      vbo_indices.push_back(
          {pair.first, sorted_vertices.size(), pair.second.size()});
      sorted_vertices.insert(std::end(sorted_vertices), std::begin(pair.second),
                             std::end(pair.second));
    }

    vbo->SetData(sorted_vertices.data(), sorted_vertices.size());

    cached_matrix = matrix * modelview_matrix * nodeview_matrix;
    matrix_sub = matrix * modelview_matrix;
  }

  for (const auto& vbo_index : vbo_indices) {
    RenderBlock3d* render_block = g_Renderer->BorrowRenderBlock();
    render_block->modelview_matrix =
        glm::value_ptr(model->GetModelViewMatrix());
    render_block->nodeview_matrix = glm::value_ptr(cached_matrix);
    render_block->vbo = vbo;
    render_block->vbo_first_item = vbo_index.first;
    render_block->vbo_item_count = vbo_index.count;

    const auto texture = model->GetTexture(vbo_index.texture_id);
    if (texture != nullptr) {
      render_block->gl_texture_id = texture->texture_id();
    } else {
      render_block->gl_texture_id = 0;
    }

    g_Renderer->AddWorldRenderBlock(render_block);
  }

  for (auto child : children) {
    child->Render(model, matrix_sub);
  }
}
