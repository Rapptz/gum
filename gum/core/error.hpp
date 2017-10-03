// gum
// Copyright (C) 2014 Rapptz

// This software is provided 'as-is', without any express or implied
// warranty.  In no event will the authors be held liable for any damages
// arising from the use of this software.

// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:

// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#ifndef GUM_CORE_ERROR_HPP
#define GUM_CORE_ERROR_HPP

#include <gum/core/config.hpp>
#include <stdexcept>

namespace sdl {
inline std::string last_error() {
    const char* result = SDL_GetError();
    SDL_ClearError();
    return result;
}

class error : public std::runtime_error {
public:
    error(): std::runtime_error(last_error()) {}
    error(const std::string& str): std::runtime_error(str) {}
};

#ifndef GUM_ERROR_HANDLER
#if defined(GUM_NO_EXCEPTIONS)
#define GUM_ERROR_HANDLER_NO_RET() do { ::SDL_Log("%s", SDL_GetError()); SDL_ClearError(); } while(0)
#define GUM_ERROR_HANDLER_VOID() do { GUM_ERROR_HANDLER_NO_RET(); return; } while(0)
#define GUM_ERROR_HANDLER(result) do { GUM_ERROR_HANDLER_NO_RET(); return result; } while(0)
#else
#define GUM_ERROR_HANDLER_NO_RET() throw ::sdl::error()
#define GUM_ERROR_HANDLER_VOID() GUM_ERROR_HANDLER_NO_RET()
#define GUM_ERROR_HANDLER(result) GUM_ERROR_HANDLER_NO_RET()
#endif // GUM_NO_EXCEPTIONS
#endif // GUM_ERROR_HANDLER
} // sdl

#endif // GUM_CORE_ERROR_HPP
