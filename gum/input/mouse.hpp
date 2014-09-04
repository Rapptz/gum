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

#ifndef GUM_INPUT_MOUSE_HPP
#define GUM_INPUT_MOUSE_HPP

#include "../video/vector.hpp"
#include <SDL_mouse.h>

namespace sdl {
namespace mouse {
enum class button : char {
    left   = SDL_BUTTON_LEFT,
    middle = SDL_BUTTON_MIDDLE,
    right  = SDL_BUTTON_RIGHT,
    x1     = SDL_BUTTON_X1,
    x2     = SDL_BUTTON_X2
};

inline bool is_button_pressed(button b) noexcept {
    return SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(static_cast<char>(b));
}

inline vector position() noexcept {
    vector result;
    SDL_GetMouseState(&result.x, &result.y);
    return result;
}
} // mouse
} // sdl

#endif // GUM_INPUT_MOUSE_HPP
