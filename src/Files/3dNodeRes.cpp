#include "Files/3dNodeRes.h"

void C3dNodeRes::Load(uint16_t version, CFile& file) {
  file.Read(&name, sizeof(name));
  file.Read(&parentname, sizeof(parentname));

  // Textures
  int32_t textures_count;
  file.Read(&textures_count, sizeof(textures_count));

  std::vector<int32_t> texture_ids(textures_count);
  file.Read(texture_ids.data(), textures_count * sizeof(texture_ids[0]));

  // Info
  file.Read(&info, sizeof(info));

  // Vertices
  int32_t vertices_count;
  file.Read(&vertices_count, sizeof(vertices_count));

  std::vector<ModelVertex> vertices(vertices_count);
  file.Read(vertices.data(), vertices_count * sizeof(vertices[0]));

  // Texture vertices
  int32_t tex_vertices_count;
  file.Read(&tex_vertices_count, sizeof(tex_vertices_count));

  std::vector<TextureVertex> tex_vertices(tex_vertices_count);
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

  std::vector<FaceInfo> faces(faces_count);
  for (int32_t i = 0; i < faces_count; i++) {
    file.Read(&faces[i], sizeof(faces[i]) - sizeof(faces[i].smooth_group));
    if (version >= 0x102) {
      file.Read(&faces[i].smooth_group, sizeof(faces[i].smooth_group));
    } else {
      faces[i].smooth_group = 0;
    }
  }

  // PosKeyFrame
  if (version >= 0x105) {
    int32_t poskeyframe_count;
    file.Read(&poskeyframe_count, sizeof(poskeyframe_count));

    std::vector<PosKeyFrame> poskeyframes(poskeyframe_count);
    for (int32_t i = 0; i < poskeyframe_count; i++) {
      file.Read(&poskeyframes[i], sizeof(poskeyframes[i]));
    }
  }

  // RotKeyFrame
  int32_t rotkeyframe_count;
  file.Read(&rotkeyframe_count, sizeof(rotkeyframe_count));

  std::vector<RotKeyFrame> rotkeyframes(rotkeyframe_count);
  for (int32_t i = 0; i < rotkeyframe_count; i++) {
    file.Read(&rotkeyframes[i], sizeof(rotkeyframes[i]));
  }
}
