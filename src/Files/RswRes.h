#ifndef DOLORI_RENDER_RSWRES_H_
#define DOLORI_RENDER_RSWRES_H_

#include <stdint.h>

#include <list>
#include <memory>
#include <string>

#include <glm/vec3.hpp>

#include "Files/Res.h"

#pragma pack(push)
#pragma pack(1)

typedef struct _ActorInfo {
  char name[0x28];
  int32_t anim_type;
  float anim_speed;
  int32_t block_type;
  char model_name[0x50];
  char node_name[0x50];
  float position[3];
  float rotation[3];
  float scale[3];
} ModelInfo;

#pragma pack(pop)

class CRswRes : public CRes {
 public:
  CRswRes();
  ~CRswRes();

  CRes* Clone();
  bool Load(const std::string&);

  const std::string& GetGnd() const;
  const std::string& GetAttr() const;
  const std::list<std::shared_ptr<ModelInfo>>& GetModels() const;

 protected:
  void Reset() override;

 private:
  std::list<std::shared_ptr<ModelInfo>> m_models;
  // std::list<C3dWorldRes::effectSrcInfo *> m_particles;
  // std::list<C3dWorldRes::soundSrcInfo *> m_sounds;
  struct SceneGraphNode* m_calculated_node;
  std::string m_ini_file;
  std::string m_gnd_file;
  std::string m_attr_file;
  std::string m_src_file;
  float m_water_level;
  int32_t m_water_type;
  float m_wave_height;
  float m_wave_speed;
  float m_wave_pitch;
  int32_t m_water_anim_speed;
  int32_t m_light_longitude;
  int32_t m_light_latitude;
  float m_light_opacity;
  glm::vec3 m_light_dir;
  glm::vec3 m_diffuse_col;
  glm::vec3 m_ambient_col;
  int32_t m_ground_top;
  int32_t m_ground_bottom;
  int32_t m_ground_left;
  int32_t m_ground_right;
};

// class C3dWorldRes {
//  CRes, offset = 0x0
//
//    public void C3dWorldRes(const class C3dWorldRes &)
//    public void C3dWorldRes::C3dWorldRes(class Exemplar, const char *, const
//    char *) public void C3dWorldRes::C3dWorldRes() public class CRes *
//    C3dWorldRes::Clone() public void C3dWorldRes::Reset() public unsigned char
//    C3dWorldRes::Load(const char *)
//    class std::list<C3dWorldRes::actorInfo *,
//    std::allocator<C3dWorldRes::actorInfo *> > m_3dActors
//
//    class std::list<C3dWorldRes::effectSrcInfo *,
//    std::allocator<C3dWorldRes::effectSrcInfo *> > m_particles
//
//    class std::list<C3dWorldRes::soundSrcInfo *,
//    std::allocator<C3dWorldRes::soundSrcInfo *> > m_sounds
//
//    struct SceneGraphNode * m_CalculatedNode
//    class std::string m_gndFile
//
//    class std::string m_attrFile
//
//    class std::string m_scrFile
//
//    float m_waterLevel
//    int m_waterType
//    float m_waveHeight
//    float m_waveSpeed
//    float m_wavePitch
//    int m_waterAnimSpeed
//    int m_lightLongitude
//    int m_lightLatitude
//    struct vector3d m_lightDir
//
//    struct vector3d m_diffuseCol
//
//    struct vector3d m_ambientCol
//
//    unsigned char m_verMajor
//    unsigned char m_verMinor
//    int m_groundTop
//    int m_groundBottom
//    int m_groundLeft
//    int m_groundRight
//    public class C3dWorldRes & operator=(const class C3dWorldRes &)
//    public void C3dWorldRes::~C3dWorldRes()
//    public void __local_vftable_ctor_closure()
//    public void * __vecDelDtor(unsigned int)
//}
//

// struct C3dWorldRes::actorInfo {
//  /* this+0x0 */ char[0x28] name
//  /* this+0x28 */ char[0x50] modelName
//  /* this+0x78 */ char[0x50] nodeName
//  /* this+0xc8 */ struct vector3d pos

//  /* this+0xd4 */ struct vector3d rot

//  /* this+0xe0 */ struct vector3d scale

//  /* this+0xec */ int animType
//  /* this+0xf0 */ int blockType
//  /* this+0xf4 */ float animSpeed
//  /* this+0xf8 */ float posx
//  /* this+0xfc */ float posy
//  /* this+0x100 */ float posz
//  public void actorInfo()
//  public struct C3dWorldRes::actorInfo & operator=(const struct
//  C3dWorldRes::actorInfo &)
//}

#endif  // DOLORI_RENDER_3DWORLDRES_H_
