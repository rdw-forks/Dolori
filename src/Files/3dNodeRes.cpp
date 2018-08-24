#include "Files/3dNodeRes.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Common/Globals.h"
#include "Common/debug.h"
#include "Render/Renderer.h"

void C3dNodeRes::Load(uint16_t version, CFile& file) {
  char buffer[0x28];

  vbo = nullptr;

  file.Read(&buffer, sizeof(buffer));
  name = buffer;
  file.Read(&buffer, sizeof(buffer));
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
    if (node.second != shared_from_this() && node.second->parentname == name) {
      node.second->parent = this;
      children.push_back(node.second);
    }
  }

  for (auto child : children) {
    child->FetchChildren(nodes);
  }
}

void C3dNodeRes::ComputeModelViewMatrix() {
  modelview_matrix = glm::mat4();

  if (parent == nullptr) {
    if (children.size() > 0) {
      //      modelview_matrix = glm::translate(
      //          modelview_matrix,
      //          glm::vec3(-model->bbrange.x, -model->bbmax.y,
      //          -model->bbrange.z));
    } else {
      //      modelview_matrix =
      //          glm::translate(modelview_matrix,
      //                         glm::vec3(0, -model->bbmax.y +
      //                         model->bbrange.y, 0));
    }
  } else {
    modelview_matrix = glm::translate(modelview_matrix, position);
  }

  if (rotkeyframes.size() == 0) {
    if (fabs(info.rot_angle) > 0.01) {
      const auto rot_axis =
          glm::vec3(info.rot_axis[0], info.rot_axis[1], info.rot_axis[2]);
      modelview_matrix = glm::rotate(
          modelview_matrix, glm::radians(info.rot_angle * 180.0f / 3.14159f),
          glm::vec3(rot_axis));
    }
  } else {
    // TODO: Animation
    const auto quaternion =
        glm::quat(rotkeyframes[0].quaternion[0], rotkeyframes[0].quaternion[1],
                  rotkeyframes[0].quaternion[2], rotkeyframes[0].quaternion[3]);
    modelview_matrix *= glm::mat4_cast(glm::normalize(quaternion));
  }

  const auto scale = glm::vec3(info.scale[0], info.scale[1], info.scale[2]);
  modelview_matrix = glm::scale(modelview_matrix, scale);

  if (parent == nullptr && children.size() == 0) {
    // modelview_matrix = glm::translate(modelview_matrix, -1.0f *
    // model->bbrange);
  } else {
    modelview_matrix = glm::translate(modelview_matrix, offset_vector);
  }

  modelview_matrix *= offset_matrix;

  for (auto child : children) {
    child->ComputeModelViewMatrix();
  }
}

void C3dNodeRes::ComputeBoundingBox(glm::vec3& bbmin_out,
                                    glm::vec3& bbmax_out) {
  if (parent != nullptr) {
    bbmin = glm::vec3(0, 0, 0);
    bbmax = glm::vec3(0, 0, 0);
  } else {
    bbmin = glm::vec3(9999999, 9999999, 9999999);
    bbmax = glm::vec3(-9999999, -9999999, -9999999);
  }

  glm::mat4 myMat = offset_matrix;
  for (unsigned int i = 0; i < faces.size(); i++) {
    for (int ii = 0; ii < 3; ii++) {
      auto v = glm::vec4(
          glm::make_vec3(vertices[faces[i].vertex_id[ii]].position), 1);
      v = myMat * v;
      if (parent != nullptr || children.size() != 0) {
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
    for (unsigned int i = 0; i < 3; i++) {
      bbmax_out[c] = glm::max(bbmax_out[c], bbmax[c]);
      bbmin_out[c] = glm::min(bbmin_out[c], bbmin[c]);
    }
  }

  for (auto child : children) {
    child->ComputeBoundingBox(bbmin_out, bbmax_out);
  }
}

void C3dNodeRes::ComputeRealBoundingBox(glm::mat4& matrix_out,
                                        glm::vec3& bbmin_out,
                                        glm::vec3& bbmax_out) {
  glm::mat4 mat1 = matrix_out * modelview_matrix;

  for (unsigned int i = 0; i < faces.size(); i++) {
    for (int ii = 0; ii < 3; ii++) {
      const glm::vec4 v =
          mat1 *
          glm::vec4(glm::make_vec3(vertices[faces[i].vertex_id[ii]].position),
                    1);
      bbmin_out.x = glm::min(bbmin_out.x, v.x);
      bbmin_out.y = glm::min(bbmin_out.y, v.y);
      bbmin_out.z = glm::min(bbmin_out.z, v.z);

      bbmax_out.x = glm::max(bbmax_out.x, v.x);
      bbmax_out.y = glm::max(bbmax_out.y, v.y);
      bbmax_out.z = glm::max(bbmax_out.z, v.z);
    }
  }

  for (auto child : children) {
    child->ComputeRealBoundingBox(mat1, bbmin_out, bbmax_out);
  }
}

void C3dNodeRes::Render(const glm::mat4& matrix, int, unsigned char) {
  if (vbo == nullptr) {
    std::vector<ModelVertex> mod_vertices;
    vbo = std::make_shared<CGlVBO>();
    vbo->SetVertexFormat<ModelVertex>();

    for (size_t i = 0; i < faces.size(); i++) {
      for (size_t v = 0; v < 3; v++) {
        mod_vertices.push_back(vertices[faces[i].vertex_id[v]]);
      }
    }

    vbo->SetData(mod_vertices.data(), mod_vertices.size());
  }

  auto render_block = std::make_shared<RenderBlock3d>();
  render_block->modelview_matrix = &matrix;
  render_block->nodeview_matrix = &modelview_matrix;
  render_block->vbo = vbo;
  render_block->texture = nullptr;
  g_Renderer->AddWorldRenderBlock(std::move(render_block));

  for (auto child : children) {
    child->Render(modelview_matrix, 0, 0);
  }
}
