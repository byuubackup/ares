#if defined(DISPLAY_XORG)
  #include <GL/gl.h>
  #include <GL/glx.h>
  #ifndef glGetProcAddress
    #define glGetProcAddress(name) (*glXGetProcAddress)((const GLubyte*)(name))
  #endif
#elif defined(DISPLAY_QUARTZ)
  #include <OpenGL/gl3.h>
#elif defined(DISPLAY_WINDOWS)
  #include <GL/gl.h>
  #include <GL/glext.h>
  #ifndef glGetProcAddress
    #define glGetProcAddress(name) wglGetProcAddress(name)
  #endif
#endif

auto IntGetProcAddress(const char* name) -> void* {
  return (void*)glGetProcAddress(name);
}

auto screen_init(n64video_config* config) -> void {
}

auto screen_adjust(int32_t width_out, int32_t height_out, int32_t* width, int32_t* height, int32_t* x, int32_t* y) -> void {
}

auto screen_update() -> void {
}

auto screen_close() -> void {
}
