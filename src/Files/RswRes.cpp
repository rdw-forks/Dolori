#include "Files/RswRes.h"

#include "Common/debug.h"
#include "Files/File.h"

#define RSW_RES_HEADER "GRSW"

#pragma pack(push)
#pragma pack(1)

typedef struct _RswHeader {
  uint32_t magic;
  uint8_t version_major;
  uint8_t version_minor;
} RswHeader;

#pragma pack(pop)

typedef enum _WORLD_OBJECT_TYPE {
  WORLD_OBJECT_TYPE_MODEL = 1,
  WORLD_OBJECT_TYPE_LIGHT,
  WORLD_OBJECT_TYPE_SOUND,
  WORLD_OBJECT_TYPE_EFFECT
} WORLD_OBJECT_TYPE;

CRswRes::CRswRes()
    : m_calculated_node(), m_water_level(), m_light_opacity(0.5f) {}

CRswRes::~CRswRes() {}

CRes* CRswRes::Clone() { return new CRswRes(); }

bool CRswRes::Load(const std::string& filename) {
  RswHeader header;
  char buffer[40];
  CFile fp;

  LOG(debug, "Loading {}", filename);

  if (!fp.Open(filename, false)) {
    LOG(error, "Failed to find file: {}", filename);
    return false;
  }

  fp.Read(&header, sizeof(header));
  if (memcmp(&header.magic, RSW_RES_HEADER, sizeof(header.magic)) != 0) {
    LOG(error, "File is not of the expected format: {}", filename);
    return false;
  }

  const uint16_t version = (header.version_major << 8) | (header.version_minor);
  LOG(debug, "RSW file version: {:x}", version);

  fp.Read(buffer, sizeof(buffer));
  buffer[sizeof(buffer) - 1] = '\0';
  m_ini_file = buffer;

  fp.Read(buffer, sizeof(buffer));
  buffer[sizeof(buffer) - 1] = '\0';
  m_gnd_file = buffer;

  fp.Read(buffer, sizeof(buffer));
  buffer[sizeof(buffer) - 1] = '\0';
  m_attr_file = buffer;

  if (version >= 0x104) {
    fp.Read(buffer, sizeof(buffer));
    buffer[sizeof(buffer) - 1] = '\0';
    m_src_file = buffer;
  }

  if (version >= 0x103) {
    fp.Read(&m_water_level, sizeof(m_water_level));
    if (version >= 0x108) {
      fp.Read(&m_water_type, sizeof(m_water_type));
      fp.Read(&m_wave_height, sizeof(m_wave_height));
      fp.Read(&m_wave_speed, sizeof(m_wave_speed));
      fp.Read(&m_wave_pitch, sizeof(m_wave_pitch));
      if (version >= 0x109) {
        fp.Read(&m_water_anim_speed, sizeof(m_water_anim_speed));
      }
    }
  }

  if (version >= 0x105) {
    fp.Read(&m_light_longitude, sizeof(m_light_longitude));
    fp.Read(&m_light_latitude, sizeof(m_light_latitude));
    fp.Read(&m_diffuse_col, sizeof(m_diffuse_col));
    fp.Read(&m_ambient_col, sizeof(m_ambient_col));
    if (version >= 0x107) {
      fp.Read(&m_light_opacity, sizeof(m_light_opacity));
    }
  }

  if (version >= 0x106) {
    fp.Read(&m_ground_top, sizeof(m_ground_top));
    fp.Read(&m_ground_bottom, sizeof(m_ground_bottom));
    fp.Read(&m_ground_left, sizeof(m_ground_left));
    fp.Read(&m_ground_right, sizeof(m_ground_right));
  }

  int32_t objects_count;
  fp.Read(&objects_count, sizeof(objects_count));

  for (size_t i = 0; i < objects_count; i++) {
    int32_t object_type;
    fp.Read(&object_type, sizeof(object_type));

    switch (object_type) {
      case WORLD_OBJECT_TYPE_MODEL: {
        const auto model_info = std::make_shared<ModelInfo>();

        if (version >= 0x103) {
          fp.Read(&model_info->name, sizeof(model_info->name));
          fp.Read(&model_info->anim_type, sizeof(model_info->anim_type));
          fp.Read(&model_info->anim_speed, sizeof(model_info->anim_speed));
          fp.Read(&model_info->block_type, sizeof(model_info->block_type));
        } else {
          memset(model_info->name, 0, sizeof(model_info->name));
          model_info->anim_type = 0;
          model_info->anim_speed = 0.f;
          model_info->block_type = 0;
        }

        fp.Read(&model_info->model_name, sizeof(model_info->model_name));
        fp.Read(&model_info->node_name, sizeof(model_info->node_name));
        fp.Read(&model_info->position, sizeof(model_info->position));
        fp.Read(&model_info->rotation, sizeof(model_info->rotation));
        fp.Read(&model_info->scale, sizeof(model_info->scale));

        m_models.push_back(std::move(model_info));
      } break;
      case WORLD_OBJECT_TYPE_LIGHT: {
        // TODO
        char name[80];
        fp.Read(&name, sizeof(name));

        float pos[3];
        fp.Read(&pos, sizeof(pos));

        uint32_t color[3];
        fp.Read(&color, sizeof(color));

        float range;
        fp.Read(&range, sizeof(range));
      } break;
      case WORLD_OBJECT_TYPE_SOUND: {
        // TODO
        char name[80];
        fp.Read(&name, sizeof(name));

        char file[80];
        fp.Read(&file, sizeof(file));

        float pos[3];
        fp.Read(&pos, sizeof(pos));

        float vol;
        fp.Read(&vol, sizeof(vol));

        uint32_t width, height;
        fp.Read(&width, sizeof(width));
        fp.Read(&height, sizeof(height));

        float range;
        fp.Read(&range, sizeof(range));

        float cycle;
        if (version >= 0x200) {
          fp.Read(&cycle, sizeof(cycle));
        } else {
          cycle = 0.f;
        }

      } break;
      case WORLD_OBJECT_TYPE_EFFECT: {
        // TODO
        char name[80];
        fp.Read(&name, sizeof(name));

        float pos[3];
        fp.Read(&pos, sizeof(pos));

        uint32_t id;
        fp.Read(&id, sizeof(id));

        float delay;
        fp.Read(&delay, sizeof(delay));

        float param[4];
        fp.Read(&param, sizeof(param));
      } break;
      default:
        LOG(error, "Unknown object type ({})", object_type);
        return false;
    }
  }

  fp.Close();

  return true;
}

void CRswRes::Reset() { m_models.clear(); }

const std::string& CRswRes::GetGnd() const { return m_gnd_file; }

const std::string& CRswRes::GetAttr() const { return m_attr_file; }

const std::list<std::shared_ptr<ModelInfo>>& CRswRes::GetModels() const {
  return m_models;
}

const glm::vec3& CRswRes::GetDiffuseColor() const { return m_diffuse_col; }

const glm::vec3& CRswRes::GetAmbientColor() const { return m_ambient_col; }

int32_t CRswRes::GetLightLongitude() const { return m_light_longitude; }

int32_t CRswRes::GetLightLatitude() const { return m_light_latitude; }

float CRswRes::GetLightOpacity() const { return m_light_opacity; }
