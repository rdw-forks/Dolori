#include "Render/Surface.h"

#include <glad/glad.h>

#include "Common/Globals.h"
#include "Common/debug.h"

CSurface::CSurface() : m_w(), m_h(), m_sdl_surface(nullptr) {}

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
}

unsigned long CSurface::GetWidth() { return m_w; }

unsigned long CSurface::GetHeight() { return m_h; }

SDL_Surface *CSurface::GetSDLSurface() { return m_sdl_surface; }

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
                            const SPR_IMG *img, const uint32_t *pal) {
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
                           int width, int height, int xflip, int zoomx,
                           int zoomy) {
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
  dst_rect.w = width * zoomx;
  dst_rect.h = height * zoomy;

  SDL_BlitScaled(src->m_sdl_surface, &src_rect, m_sdl_surface, &dst_rect);
  UpdateGlTexture();
}

void CSurface::BlitSprite(int x, int y, CSprRes *spr_res, CMotion *cur_motion,
                          unsigned int *palette) {
  int nb_of_clips = cur_motion->NumberOfClips();

  for (int clip_id = 0; clip_id < nb_of_clips; clip_id++) {
    SPR_CLIP *clip;
    SPR_IMG *spr_img;

    clip = cur_motion->GetClip(clip_id);
    spr_img = spr_res->GetSprImg(clip->clip_type, clip->spr_index);
    // if (clip_id)
    //{
    //  v9 = clip->x + x - ox;
    //  v11 = y + clip->y - oy;
    //}
    // else
    //{
    //  v9 = x - spr_img->width / 2;
    //  ox = clip->x + spr_img->width / 2;
    //  v11 = y - spr_img->height / 2;
    //  oy = spr_img->height / 2 + clip->y;
    //}
  }
}

void CSurface::ClearSurface(SDL_Rect *rect, uint32_t color) {
  if (m_sdl_surface != nullptr) {
    SDL_FillRect(m_sdl_surface, rect, color);
  }
}

void CSurface::DrawSurface(int x, int y, int width, int height,
                           unsigned int color) {
  int s_width, left, top, s_height;
  int s_x;
  int s_y;

  s_x = x;
  s_width = width;
  left = 0;
  top = 0;
  s_height = height;

  if (x + width > g_3dDevice->GetWidth()) {
    s_width = g_3dDevice->GetWidth() - x;
  }

  s_y = y;
  if (y + height > g_3dDevice->GetHeight()) {
    s_height = g_3dDevice->GetHeight() - y;
  }

  if (x < 0) {
    left = -x;
    s_x = 0;
  }

  if (y < 0) {
    top = -y;
    s_y = 0;
  }

  if (s_width > left && s_height > top) {
    DrawSurfaceStretch(s_x, s_y, s_width, s_height);
  }
}

void CSurface::DrawSurfaceStretch(int x, int y, int width, int height) {
  g_Renderer->AddSurface(this, {x, y, width, height});
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
