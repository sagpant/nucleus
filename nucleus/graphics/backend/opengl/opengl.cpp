/**
 * (c) 2014-2016 Alexandro Sanchez Bach. All rights reserved.
 * Released under GPL v2 license. Read LICENSE for more details.
 */

#include "opengl.h"
#include "nucleus/logger/logger.h"

// Load extensions
#if defined(GRAPHICS_OPENGL_API_WGL)
#define LOAD_EXTENSION(type, function) { \
    function = reinterpret_cast<type>(wglGetProcAddress(#function)); \
    if (!function) { \
        logger.error(LOG_GRAPHICS, "Could not load OpenGL extension '%s'", #function); \
        return false; \
    } \
}
#elif defined(GRAPHICS_OPENGL_API_GLX)
#define LOAD_EXTENSION(type, function) { \
    function = reinterpret_cast<type>(glXGetProcAddress(#function)); \
    if (!function) { \
        logger.error(LOG_GRAPHICS, "Could not load OpenGL extension '%s'", #function); \
        return false; \
    } \
}
#elif defined(GRAPHICS_OPENGL_API_EGL)
#define LOAD_EXTENSION(type, function) { \
    function = reinterpret_cast<type>(eglGetProcAddress(#function)); \
    if (!function) { \
        logger.error(LOG_GRAPHICS, "Could not load OpenGL ES extension '%s'", #function); \
        return false; \
    } \
}
#endif

namespace gfx {
namespace opengl {

// Declare extensions
#define DECLARE_EXTENSION(type, function) type function;
#define EXTENSION DECLARE_EXTENSION
#include "opengl.inl"
#undef EXTENSION
#undef DECLARE_EXTENSION

bool initializeOpenGL() {
#define EXTENSION LOAD_EXTENSION
#include "opengl.inl"
#undef EXTENSION

    return true;
}

}  // namespace opengl
}  // namespace gfx
