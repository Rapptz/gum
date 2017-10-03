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

#ifndef GUM_CORE_INIT_HPP
#define GUM_CORE_INIT_HPP

#include <gum/core/config.hpp>
#include <gum/core/error.hpp>
#include <cstdlib>

namespace sdl {
inline void quit() noexcept {
#ifndef GUM_IMG_DISABLED
    IMG_Quit();
#endif
    SDL_Quit();
}

#ifndef GUM_IMG_DISABLED
#define GUM_IMG_DEF IMG_INIT_PNG | IMG_INIT_JPG
#else
#define GUM_IMG_DEF 0
#endif

inline int init(uint32_t sdl = SDL_INIT_EVERYTHING, uint32_t img = GUM_IMG_DEF) {
    auto result = SDL_Init(sdl);
    if(result < 0) {
        GUM_ERROR_HANDLER(result);
    }

#ifndef GUM_IMG_DISABLED
    auto img_result = IMG_Init(img);
    if((img_result & img) != img) {
        // Doesn't set the error flag, also doesn't return an error code so follow SDL_Init's < 0 convention.
        GUM_ERROR_HANDLER(-1);
    }
#else
    (void)img;
#endif

    std::atexit(::sdl::quit);
    return 0;
}
} // sdl

#undef GUM_IMG_DEF

#endif // GUM_CORE_INIT_HPP
