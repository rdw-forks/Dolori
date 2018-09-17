#ifndef DOLORI_FILES_3DNODERES_H_
#define DOLORI_FILES_3DNODERES_H_

#include <list>
#include <map>
#include <memory>
#include <string>

#include <glm/glm.hpp>

#include "Files/File.h"
#include "Render/Texture.h"
#include "Render/VBO.h"

#pragma pack(push)
#pragma pack(1)

typedef struct _NodeInfo {
  float mat3[9];
  float offset[3];
  float position[3];
  float rot_angle;
  float rot_axis[3];
  float scale[3];
} NodeInfo;

typedef struct _ModelVertex {
  glm::vec3 position;
} ModelVertex;

typedef struct _TextureVertex {
  uint32_t color;
  glm::vec2 position;
} TextureVertex;

typedef struct _FaceInfo {
  uint16_t vertex_id[3];
  uint16_t tex_vertex_id[3];
  uint16_t tex_id;
  uint16_t padding;
  int32_t two_sides;
  int32_t smooth_group;
} FaceInfo;

typedef struct _PosKeyFrame {
  int32_t frame;
  float position[3];
} PosKeyFrame;

typedef struct _RotKeyFrame {
  int32_t frame;
  float quaternion[4];
} RotKeyFrame;

#pragma pack(pop)

typedef struct _VboIndex {
  int32_t texture_id;
  size_t first;
  size_t count;
} VboIndex;

// Forward declaration
class C3dActor;

class C3dNodeRes {
 public:
  C3dNodeRes();

  void Load(uint16_t version, CFile &file);
  void FetchChildren(
      const std::map<std::string, std::shared_ptr<C3dNodeRes>> &nodes);
  void ComputeModelViewMatrix(const C3dActor *model);
  void ComputeNodeViewMatrix(const C3dActor *model);
  void ComputeBoundingBox(glm::vec3 &bbmin_out, glm::vec3 &bbmax_out);
  void ComputeRealBoundingBox(const glm::mat4 &matrix, glm::vec3 &bbmin_out,
                              glm::vec3 &bbmax_out);
  void Render(const C3dActor *, const glm::mat4 &);

  std::string name;
  std::string parentname;
  NodeInfo info;
  std::vector<int32_t> textures;
  std::vector<ModelVertex> vertices;
  std::vector<TextureVertex> tex_vertices;
  std::vector<FaceInfo> faces;
  std::vector<PosKeyFrame> poskeyframes;
  std::vector<RotKeyFrame> rotkeyframes;
  glm::mat4 offset_matrix;
  glm::vec3 offset_vector;
  glm::vec3 position;
  glm::mat4 cached_matrix;
  glm::mat4 matrix_sub;
  glm::mat4 modelview_matrix;
  glm::mat4 nodeview_matrix;
  C3dNodeRes *parent;
  std::list<std::shared_ptr<C3dNodeRes>> children;
  std::shared_ptr<CGlVBO> vbo;
  std::list<VboIndex> vbo_indices;
  unsigned char alpha;
  // class C3dPosAnim posanim;
  // class C3dRotAnim rotanim;
  glm::vec3 bbmin;
  glm::vec3 bbmax;
  glm::vec3 bbrange;
};

//    struct C3dNodeRes {
//     public void C3dNodeRes(const struct C3dNodeRes &)
//  public void C3dNodeRes::C3dNodeRes()
//  public void C3dNodeRes::~C3dNodeRes()
//  public void C3dNodeRes::Release()
//  /* this+0x0 */ char[0x80] name
//  /* this+0x80 */ char[0x80] parentname
//  /* this+0x100 */ class C3dModelRes * scene
//  /* this+0x104 */ struct C3dNodeRes * parent
//  /* this+0x108 */ class std::list<C3dNodeRes *,std::allocator<C3dNodeRes *> >
//  child

//  /* this+0x114 */ class C3dMesh * mesh
//  /* this+0x118 */ int numTexture
//  /* this+0x11c */ class CTexture * * texture
//  /* this+0x120 */ float[0x3] pos
//  /* this+0x12c */ float[0x3] rotaxis
//  /* this+0x138 */ float rotangle
//  /* this+0x13c */ float[0x3] scale
//  /* this+0x148 */ unsigned char alpha
//  /* this+0x14c */ class C3dPosAnim posanim

//  /* this+0x15c */ class C3dRotAnim rotanim

//  public struct C3dNodeRes & operator=(const struct C3dNodeRes &)
//  public void * __vecDelDtor(unsigned int)
//}

#endif  // DOLORI_FILES_3DNODERES_H_
