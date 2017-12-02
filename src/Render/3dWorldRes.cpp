#include "3dWorldRes.h"
#include "../Common/ErrorMsg.h"
#include "../Files/File.h"

C3dWorldRes::C3dWorldRes() { m_calculated_node = NULL; }

C3dWorldRes::~C3dWorldRes() {}

CRes* C3dWorldRes::Clone() { return new C3dWorldRes(); }

bool C3dWorldRes::Load(const char* filename) {
  RSW_HEADER header;
  char buffer[40];
  float x, y, z;
  CFile fp;

  if (!fp.Open(filename, false)) {
    std::string error = "Cannot find ";
    error += filename;
    ErrorMsg(error.c_str());
    return false;
  }

  fp.Read(&header, sizeof(header));
  if (header.magic != 'WSRG') {
    std::string error = "Illegal file format: ";
    error += filename;
    ErrorMsg(error.c_str());
    fp.Close();
    return false;
  }

  fp.Read(buffer, sizeof(buffer));
  m_ini_file = buffer;
  fp.Read(buffer, sizeof(buffer));
  m_gnd_file = buffer;
  fp.Read(buffer, sizeof(buffer));
  m_attr_file = buffer;
  if (header.version >= 0x104) {
    fp.Read(buffer, sizeof(buffer));
    m_src_file = buffer;
  }

  if (header.version >= 0x103) {
    fp.Read(&m_water_level, sizeof(m_water_level));
    if (header.version >= 0x108) {
      fp.Read(&m_water_type, sizeof(m_water_type));
      fp.Read(&m_wave_height, sizeof(m_wave_height));
      fp.Read(&m_wave_speed, sizeof(m_wave_speed));
      fp.Read(&m_wave_pitch, sizeof(m_wave_pitch));
      if (header.version >= 0x109) {
        fp.Read(&m_water_anim_speed, sizeof(m_water_anim_speed));
      }
    }
  }

  if (header.version >= 0x105) {
    fp.Read(&m_light_longitude, sizeof(m_light_longitude));
    fp.Read(&m_light_latitude, sizeof(m_light_latitude));
    fp.Read(&x, sizeof(x));
    fp.Read(&y, sizeof(y));
    fp.Read(&z, sizeof(z));
    m_diffuse_col = CVector3d(x, y, z);
    fp.Read(&x, sizeof(x));
    fp.Read(&y, sizeof(y));
    fp.Read(&z, sizeof(z));
    m_ambient_col = CVector3d(x, y, z);
    if (header.version >= 0x107) {
      fp.Read(&m_light_opacity, sizeof(m_light_opacity));
    }
  }

  if (header.version >= 0x106) {
    fp.Read(&m_ground_top, sizeof(m_ground_top));
    fp.Read(&m_ground_bottom, sizeof(m_ground_bottom));
    fp.Read(&m_ground_left, sizeof(m_ground_left));
    fp.Read(&m_ground_right, sizeof(m_ground_right));
  }

  // TODO: Objects

  fp.Close();

  return true;
}

void C3dWorldRes::Reset() {}

const char* C3dWorldRes::GetGnd() { return m_gnd_file.c_str(); }

const char* C3dWorldRes::GetAttr() { return m_attr_file.c_str(); }
