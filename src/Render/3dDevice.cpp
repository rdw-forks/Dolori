#include "Render/3dDevice.h"

#include <SDL_ttf.h>
#include <glad/glad.h>
#include <il.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Common/ErrorMsg.h"
#include "Common/Globals.h"
#include "Common/debug.h"
#include "Render/SurfaceWallpaper.h"

C3dDevice::C3dDevice()
    : m_sdlWnd(),
      m_glCtx(),
      m_dwRenderWidth(),
      m_dwRenderHeight(),
      m_bIsFullscreen(),
      m_pfRShiftR(),
      m_pfRShiftL(),
      m_pfGShiftR(),
      m_pfGShiftL(),
      m_pfBShiftR(),
      m_pfBShiftL(),
      m_pfAShiftR(),
      m_pfAShiftL(),
      m_pfBitCount(),
      m_pfRBitMask(),
      m_pfGBitMask(),
      m_pfBBitMask(),
      m_pfABitMask(),
      m_dwMinTextureWidth(),
      m_dwMinTextureHeight(),
      m_dwMaxTextureWidth(),
      m_dwMaxTextureHeight(),
      m_dwMaxTextureAspectRatio(),
      m_bSupportBltStretch(),
      m_bSupportTextureSurface(),
      m_fMaterialDiffuseR(),
      m_fMaterialDiffuseG(),
      m_fMaterialDiffuseB(),
      m_fMaterialAmbientR(),
      m_fMaterialAmbientG(),
      m_fMaterialAmbientB() {}

long C3dDevice::Init(uint32_t width, uint32_t height, uint32_t msaa_samples,
                     uint32_t dwFlags) {
  unsigned int flags;

  m_bIsFullscreen = (dwFlags & DEVICE_FLAG_FULLSCREEN) != 0;
  const bool vsync = (dwFlags & DEVICE_FLAG_VSYNC) != 0;
  m_dwRenderWidth = width;
  m_dwRenderHeight = height;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    return -1;
  }

  if (TTF_Init() < 0) {
    return -1;
  }

  // Pixel format (A8R8G8B8)
  SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);

  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

  // Multi-sampling anti-aliasing
  if (msaa_samples > 0) {
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, msaa_samples);
  }

  // OpenGL version
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  flags = SDL_WINDOW_OPENGL;
  if (m_bIsFullscreen) {
    flags |= SDL_WINDOW_FULLSCREEN | SDL_WINDOW_RESIZABLE;
  }

  m_sdlWnd = SDL_CreateWindow("Dolori", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, m_dwRenderWidth,
                              m_dwRenderHeight, flags);
  if (m_sdlWnd == nullptr) {
    LOG(error, "Failed to create a window");
    return -1;
  }

  m_glCtx = SDL_GL_CreateContext(m_sdlWnd);
  if (m_glCtx == nullptr) {
    LOG(error, "Failed to create an OpenGL context");
    return -1;
  }

  EnableVsync(vsync);

  // Load extensions
  if (gladLoadGLLoader(SDL_GL_GetProcAddress) == 0) {
    return -1;
  }

  LOG(info, "Vendor:   {}", glGetString(GL_VENDOR));
  LOG(info, "Renderer: {}", glGetString(GL_RENDERER));
  LOG(info, "Version:  {}", glGetString(GL_VERSION));

  // Set the viewport
  glViewport(0, 0, m_dwRenderWidth, m_dwRenderHeight);
  if (glGetError() != GL_NO_ERROR) {
    return -1;
  }

  glEnable(GL_DEPTH_TEST);
  if (glGetError() != GL_NO_ERROR) {
    return -1;
  }

  glEnable(GL_BLEND);
  if (glGetError() != GL_NO_ERROR) {
    return -1;
  }

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // Bind a dummy vao to comply with core profile's specifications
  GLuint dummy_vao;
  glGenVertexArrays(1, &dummy_vao);
  glBindVertexArray(dummy_vao);

  // Initialize DevIL
  ilInit();
  ilClearColour(255, 255, 255, 0);
  ilOriginFunc(IL_ORIGIN_UPPER_LEFT);
  ilEnable(IL_ORIGIN_SET);

  // Check for error
  ILenum ilError = ilGetError();
  if (ilError != IL_NO_ERROR) {
    return -1;
  }

  return 0;
}

long C3dDevice::DestroyObjects() {
  if (m_sdlWnd != nullptr) {
    SDL_DestroyWindow(m_sdlWnd);
  }

  TTF_Quit();
  SDL_Quit();

  return 0;
}

CRenderer* C3dDevice::CreateRenderer(int arg) {
  CRenderer* renderer = new CRenderer();
  PIXEL_FORMAT pf;

  if (!renderer->Init()) {
    LOG(error, "Failed to initialize renderer");
    return nullptr;
  }

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
  if (renderer) {
    delete renderer;
  }
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

int C3dDevice::GetWidth() const { return m_dwRenderWidth; }

int C3dDevice::GetHeight() const { return m_dwRenderHeight; }

std::shared_ptr<CSurface> C3dDevice::CreateWallPaper(unsigned int w,
                                                     unsigned int h) {
  if (w > m_dwMaxTextureWidth || h > m_dwMaxTextureHeight) {
    return std::make_shared<CSurfaceWallpaper>(m_dwRenderWidth,
                                               m_dwRenderHeight);
  }

  return g_TexMgr->CreateTexture(w, h, PF_A8R8G8B8);
}

void C3dDevice::ConvertPalette(uint32_t* dest, PALETTE_ENTRY* palette,
                               size_t pal_count) {
  for (size_t i = 0; i < pal_count; i++) {
    const PALETTE_ENTRY& current_entry = palette[i];

    if (current_entry.peRed == 0xFF && current_entry.peBlue == 0xFF) {
      dest[i] = 0x0;
    } else {
      dest[i] = (0xFF << 24) | (current_entry.peRed) |
                (current_entry.peGreen << 8) | (current_entry.peBlue << 16);
    }
  }
}

void C3dDevice::EnableVsync(bool enable) {
  if (enable) {
    SDL_GL_SetSwapInterval(1);
  } else {
    SDL_GL_SetSwapInterval(0);
  }
}
