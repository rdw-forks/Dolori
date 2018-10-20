#include "Render/Surface.h"

#include <glad/glad.h>

#include "Common/Globals.h"
#include "Common/debug.h"

CSurface::CSurface()
    : m_w(), m_h(), m_sdl_surface(nullptr), m_sdl_surface_xflipped(nullptr) {}

CSurface::CSurface(unsigned long w, unsigned long h) : CSurface() {
  Create(w, h);
  m_sdl_surface = SDL_CreateRGBSurface(SDL_SWSURFACE, m_w, m_h, 32, 0xff,
                                       0xff00, 0xff0000, 0xff000000);
  UpdateGlTexture();
}

CSurface::CSurface(SDL_Surface *surface) {
  Create(surface->w, surface->h);
  m_sdl_surface = surface;
  UpdateGlTexture();
}

CSurface::~CSurface() {
  if (m_sdl_surface != nullptr) {
    SDL_FreeSurface(m_sdl_surface);
  }

  if (m_sdl_surface_xflipped != nullptr) {
    SDL_FreeSurface(m_sdl_surface_xflipped);
  }
}

unsigned long CSurface::GetWidth() const { return m_w; }

unsigned long CSurface::GetHeight() const { return m_h; }

SDL_Surface *CSurface::GetSDLSurface() const { return m_sdl_surface; }

SDL_Surface *CSurface::GetSDLSurfaceXFlipped() {
  if (m_sdl_surface == nullptr) {
    return nullptr;
  }

  if (m_sdl_surface_xflipped == nullptr) {
    m_sdl_surface_xflipped = SDL_CreateRGBSurface(
        SDL_SWSURFACE, m_w, m_h, 32, 0xff, 0xff00, 0xff0000, 0xff000000);
    if (m_sdl_surface_xflipped == nullptr) {
      return nullptr;
    }

    const int pitch = m_sdl_surface->pitch;
    const int line_length = m_sdl_surface->w;
    auto pixels = static_cast<uint8_t *>(m_sdl_surface->pixels);
    auto rpixels = static_cast<uint8_t *>(m_sdl_surface_xflipped->pixels);

    for (auto line = 0; line < m_sdl_surface->h; ++line) {
      std::reverse_copy(reinterpret_cast<uint32_t *>(pixels),
                        reinterpret_cast<uint32_t *>(pixels) + line_length,
                        reinterpret_cast<uint32_t *>(rpixels));
      pixels += pitch;
      rpixels += pitch;
    }
  }

  return m_sdl_surface_xflipped;
}

void CSurface::Create(unsigned long w, unsigned long h) {
  m_w = w;
  m_h = h;
}

void CSurface::Update(int x, int y, int width, int height, const ILubyte *image,
                      int drawOnlyNoTrans) {
  if (m_sdl_surface != nullptr &&
      (m_sdl_surface->w != width || m_sdl_surface->h != height)) {
    SDL_FreeSurface(m_sdl_surface);
    m_sdl_surface = nullptr;
  }

  if (m_sdl_surface == nullptr) {
    Create(width, height);
    m_sdl_surface = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, 32, 0xff,
                                         0xff00, 0xff0000, 0xff000000);
  }

  SDL_LockSurface(m_sdl_surface);
  memcpy(m_sdl_surface->pixels, image, m_sdl_surface->w * m_sdl_surface->h * 4);
  SDL_UnlockSurface(m_sdl_surface);
  UpdateGlTexture();
}

void CSurface::UpdateSprite(int x, int y, int width, int height,
                            const SprImg *img, const uint32_t *pal) {
  if (m_sdl_surface != nullptr &&
      (m_sdl_surface->w != width || m_sdl_surface->h != height)) {
    SDL_FreeSurface(m_sdl_surface);
    m_sdl_surface = nullptr;
  }

  if (m_sdl_surface == nullptr) {
    Create(width, height);
    m_sdl_surface = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, 32, 0xff,
                                         0xff00, 0xff0000, 0xff000000);
  }

  int surface_size = m_sdl_surface->w * m_sdl_surface->h;
  uint32_t *surface_data = (uint32_t *)m_sdl_surface->pixels;

  SDL_LockSurface(m_sdl_surface);
  for (int i = 0; i < surface_size; i++) {
    if (img->image_8bit[i]) {
      surface_data[i] = pal[img->image_8bit[i]];
    } else {
      surface_data[i] = 0;
    }
  }

  SDL_UnlockSurface(m_sdl_surface);
  UpdateGlTexture();
}

void CSurface::CopyRect(int x, int y, int w, int h, SDL_Surface *src) {
  if (src == nullptr || m_sdl_surface == nullptr) {
    return;
  }
  SDL_Rect dst_rect;
  dst_rect.x = x;
  dst_rect.y = y;
  dst_rect.w = w;
  dst_rect.h = h;
  SDL_BlitSurface(src, nullptr, m_sdl_surface, &dst_rect);
  UpdateGlTexture();
}

void CSurface::BlitBitmap(int x, int y, int w, int h, const ILubyte *bitmap) {
  if (bitmap == nullptr || m_sdl_surface == nullptr) {
    return;
  }

  SDL_Surface *surface;
  surface = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32, 0xff, 0xff00,
                                 0xff0000, 0xff000000);
  SDL_LockSurface(surface);
  memcpy(surface->pixels, bitmap, surface->w * surface->h * 4);
  SDL_UnlockSurface(surface);

  CopyRect(x, y, w, h, surface);

  SDL_FreeSurface(surface);
}

void CSurface::BlitSurface(int x, int y, CSurface *src, int srcx, int srcy,
                           int width, int height, int xflip, float zoomx,
                           float zoomy) {
  if (src == nullptr || m_sdl_surface == nullptr) {
    return;
  }

  SDL_Rect src_rect, dst_rect;
  src_rect.x = srcx;
  src_rect.y = srcy;
  src_rect.w = width;
  src_rect.h = height;

  dst_rect.x = x;
  dst_rect.y = y;
  dst_rect.w = static_cast<int>(width * zoomx);
  dst_rect.h = static_cast<int>(height * zoomy);

  SDL_Surface *sdl_surface =
      xflip == 1 ? src->GetSDLSurfaceXFlipped() : src->GetSDLSurface();
  SDL_BlitScaled(sdl_surface, &src_rect, m_sdl_surface, &dst_rect);
  UpdateGlTexture();
}

// TODO(LinkZ): This method's implementation is not actually finished
void CSurface::BlitSprite(int x, int y, CSprRes *spr_res, CMotion *cur_motion,
                          uint32_t *palette) {
  size_t nb_of_clips = cur_motion->NumberOfClips();
  int origin_x = 0;
  int origin_y = 0;
  int off_x = 0;
  int off_y = 0;

  for (size_t clip_id = 0; clip_id < nb_of_clips; clip_id++) {
    const SprClip *clip = cur_motion->GetClip(clip_id);
    const SprImg *spr_img =
        spr_res->GetSprImg(clip->clip_type, clip->spr_index);

    if (clip_id > 0) {
      off_x = clip->x + x - origin_x;
      off_y = clip->y + y - origin_x;
    } else {
      off_x = x - spr_img->width / 2;
      off_y = y - spr_img->height / 2;
      origin_x = clip->x + spr_img->width / 2;
      origin_y = clip->y + spr_img->height / 2;
    }

    // ...

    CSurface *surface =
        g_Renderer->GetSpriteIndex(spr_img, spr_res->GetPalette());
    if (surface == nullptr) {
      surface = g_Renderer->AddSpriteIndex(spr_img, spr_res->GetPalette());
    }

    BlitSurface(off_x, off_y, surface, 0, 0, spr_img->width, spr_img->height,
                clip->is_mirror, clip->zoomx, clip->zoomy);
  }
}

void CSurface::ClearSurface(SDL_Rect *rect, uint32_t color) {
  if (m_sdl_surface != nullptr) {
    SDL_FillRect(m_sdl_surface, rect, color);
  }
}

void CSurface::DrawSurface(int x, int y, int width, int height,
                           unsigned int color) {
  if (x + width > g_3dDevice->GetWidth()) {
    width = g_3dDevice->GetWidth() - x;
  }

  if (y + height > g_3dDevice->GetHeight()) {
    height = g_3dDevice->GetHeight() - y;
  }

  if (x < 0) {
    x = 0;
  }

  if (y < 0) {
    y = 0;
  }

  if (width > 0 && height > 0) {
    DrawSurfaceStretch(x, y, width, height);
  }
}

void CSurface::DrawSurfaceStretch(int x, int y, int width, int height) {
  g_Renderer->AddSurface({this, {x, y}, width, height});
}

void CSurface::UpdateGlTexture() {
  Bind(GL_TEXTURE_2D);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_sdl_surface->w, m_sdl_surface->h, 0,
               GL_RGBA, GL_UNSIGNED_BYTE, m_sdl_surface->pixels);

  glGenerateMipmap(GL_TEXTURE_2D);

  float largest_supported_anisotropy;
  glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &largest_supported_anisotropy);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT,
                  largest_supported_anisotropy);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
}
