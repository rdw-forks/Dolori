#ifndef DOLORI_RENDER_RPFACE_H_
#define DOLORI_RENDER_RPFACE_H_

#include <GL/glew.h>
#include <SDL_opengl.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "Render/Texture.h"
#include "Render/tlvertex3d.h"

class CRPFace {
 public:
  virtual ~CRPFace();

  void set_texture(CTexture* texture);

  void SetGeomInfo(int, const struct TlVertex3d&);
  void SetColorInfo(int, unsigned long);
  float GetWCoord(int index) const;
  void Draw() const;
  // public void RPFace::SetGeomInfo(int, const struct vector4d &)
  // public void RPFace::SetGeomInfo(int, const struct tlvertex3d &)
  // public void RPFace::InitSpecular()

 protected:
  CRPFace();
  CRPFace(int num_vertices);

 protected:
  GLenum m_primType;
  std::vector<glm::vec3> m_vertices;
  std::vector<glm::vec2> m_texture_coords;
  std::vector<unsigned short> m_indices;
  CTexture* m_texture;
  std::vector<float> m_oows;

  // unsigned long srcAlphaMode;
  // unsigned long destAlphaMode;
  // unsigned long mtPreset;
};

#endif  // DOLORI_RENDER_RPFACE_H_
