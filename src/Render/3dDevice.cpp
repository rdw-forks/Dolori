#include "3dDevice.h"
#include <GL/glew.h>
#include <GL/glu.h>
#include <SDL_opengl.h>
#include <SDL_ttf.h>
#include <il.h>
#include "../Common/Globals.h"
#include "../Render/SurfaceWallpaper.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

C3dDevice::C3dDevice() {}

long C3dDevice::Init(uint32_t dwFlags) {
  unsigned int flags;

  m_bIsFullscreen = dwFlags & 1;

  // SDL_SetMainReady();
  if (SDL_Init(SDL_INIT_VIDEO) < 0) return -1;
  if (TTF_Init() < 0) return -1;

  // Pixel format
  SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  // SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, bpp);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

  flags = SDL_WINDOW_OPENGL;
  if (m_bIsFullscreen) flags |= SDL_WINDOW_FULLSCREEN | SDL_WINDOW_RESIZABLE;
  m_sdlWnd = SDL_CreateWindow("Dolori", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                              SCREEN_HEIGHT, flags);
  if (!m_sdlWnd) return -1;

  m_glCtx = SDL_GL_CreateContext(m_sdlWnd);
  if (!m_glCtx) return -1;

  GLenum glewError = glewInit();
  if (glewError != GLEW_OK) return -1;

  // Set the viewport
  glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

  // Initialize Projection Matrix
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, 0.0, 1.0);

  // Initialize Modelview Matrix
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // Initialize clear color
  glClearColor(0.f, 0.f, 0.f, 1.f);

  GLenum error = glGetError();
  if (error != GL_NO_ERROR) return -1;

  // Initialize DevIL
  ilInit();
  ilClearColour(255, 255, 255, 0);
  ilOriginFunc(IL_ORIGIN_UPPER_LEFT);
  ilEnable(IL_ORIGIN_SET);

  // Check for error
  ILenum ilError = ilGetError();
  if (ilError != IL_NO_ERROR) return -1;

  m_dwRenderWidth = SCREEN_WIDTH;
  m_dwRenderHeight = SCREEN_HEIGHT;

  return 0;
}

long C3dDevice::DestroyObjects() {
  if (m_sdlWnd) SDL_DestroyWindow(m_sdlWnd);
  TTF_Quit();
  SDL_Quit();

  return 0;
}

CRenderer* C3dDevice::CreateRenderer(int arg) {
  CRenderer* renderer = new CRenderer();
  PIXEL_FORMAT pf;

  switch (m_pfRBitMask) {
    case 0xF800u:
      pf = PF_R5G6B5;
      break;
    case 0x7C00u:
      pf = PF_R5G5B5;
      break;
    case 0x1Fu:
      // ErrorMsg(msg);
      pf = PF_R5G6B5;
      break;
    default:
      if (m_pfBitCount == 32) {
        pf = PF_A8R8G8B8;
      } else {
        // ErrorMsg(aNotSupportedMo);
        pf = PF_UNSUPPORTED;
      }
      break;
  }

  renderer->SetPixelFormat(pf);
  renderer->SetSize(m_dwRenderWidth, m_dwRenderHeight);

  return renderer;
}

void C3dDevice::DestroyRenderer(CRenderer* renderer) {
  if (renderer) delete renderer;
}

long C3dDevice::Clear(unsigned long color) {
  float a, r, g, b;

  a = ((color >> 24) & 0xFF) / 255.f;
  r = ((color >> 16) & 0xFF) / 255.f;
  g = ((color >> 8) & 0xFF) / 255.f;
  b = ((color)&0xFF) / 255.f;
  glClearColor(r, g, b, a);
  return 0;
}

long C3dDevice::ClearZBuffer() {
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  return 0;
}

long C3dDevice::ShowFrame() {
  SDL_GL_SwapWindow(m_sdlWnd);

  return 0;
}

int C3dDevice::GetWidth() { return m_dwRenderWidth; }

int C3dDevice::GetHeight() { return m_dwRenderHeight; }

CSurface* C3dDevice::CreateWallPaper(unsigned int w, unsigned int h) {
  CSurface* result;

  if (w > m_dwMaxTextureWidth || h > m_dwMaxTextureHeight) {
    result = new CSurfaceWallpaper(m_dwRenderWidth, m_dwRenderHeight);
  } else {
    result = g_TexMgr->CreateTexture(w, h, PF_A8R8G8B8);
  }

  return result;
}

void C3dDevice::ConvertPalette(uint32_t* dest, PALETTE_ENTRY* palette,
                               int pal_count) {
  PALETTE_ENTRY* current_entry;

  for (int i = 0; i < pal_count; i++) {
    current_entry = &palette[i];
    if (current_entry->peRed == 0xFF && current_entry->peBlue == 0xFF) {
      dest[i] = 0x0;
    } else {
      dest[i] = (0xFF << 24) | (current_entry->peRed) |
                (current_entry->peGreen << 8) | (current_entry->peBlue << 16);
      // dest[i] = (current_entry->peBlue >> 3) +
      //          4 * ((current_entry->peGreen & 0xF8) +
      //               32 * ((current_entry->peRed & 0xF8) + 256));
    }
  }
}