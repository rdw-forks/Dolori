#ifndef DOLORI_RENDER_3DWORLDRES_H_
#define DOLORI_RENDER_3DWORLDRES_H_

#include <list>
#include "Common/Vector3d.h"
#include "Res.h"

#pragma pack(push)
#pragma pack(1)

typedef struct RSW_HEADER {
  uint32_t magic;
  uint16_t version;
} RSW_HEADER;

#pragma pack(pop)

class C3dWorldRes : public CRes {
 public:
  C3dWorldRes();
  ~C3dWorldRes();

  CRes* Clone();
  bool Load(const char*);
  void Reset();
  const char* GetGnd();
  const char* GetAttr();

 private:
  // std::list<C3dWorldRes::actorInfo *> m_3dActors;
  // std::list<C3dWorldRes::effectSrcInfo *> m_particles;
  // std::list<C3dWorldRes::soundSrcInfo *> m_sounds;
  struct SceneGraphNode* m_calculated_node;
  std::string m_ini_file;
  std::string m_gnd_file;
  std::string m_attr_file;
  std::string m_src_file;
  float m_water_level;
  int m_water_type;
  float m_wave_height;
  float m_wave_speed;
  float m_wave_pitch;
  int m_water_anim_speed;
  int m_light_longitude;
  int m_light_latitude;
  float m_light_opacity;
  CVector3d m_light_dir;
  CVector3d m_diffuse_col;
  CVector3d m_ambient_col;
  unsigned char m_ver_major;
  unsigned char m_ver_minor;
  int m_ground_top;
  int m_ground_bottom;
  int m_ground_left;
  int m_ground_right;
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

#endif  // DOLORI_RENDER_3DWORLDRES_H_
