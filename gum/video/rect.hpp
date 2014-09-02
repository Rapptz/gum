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

#ifndef GUM_VIDEO_RECT_HPP
#define GUM_VIDEO_RECT_HPP

#include <SDL_rect.h>

namespace sdl {
struct rect : public SDL_Rect {
    constexpr rect() noexcept: SDL_Rect{0, 0, 0, 0} {}
    constexpr rect(int x, int y, int w, int h) noexcept: SDL_Rect{x, y, w, h} {}

    bool intersects(const rect& other) const noexcept {
        return SDL_HasIntersection(this, &other);
    }

    bool empty() const noexcept {
        return SDL_RectEmpty(this);
    }

    rect union_with(const rect& other) const noexcept {
        rect result;
        SDL_UnionRect(this, &other, &result);
        return result;
    }
};

constexpr bool operator==(const rect& lhs, const rect& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.w == rhs.w && lhs.h == rhs.h;
}

constexpr bool operator!=(const rect& lhs, const rect& rhs) {
    return !(lhs == rhs);
}

constexpr bool operator<(const rect& lhs, const rect& rhs) {
    return lhs.x != rhs.x ? lhs.x < rhs.x :
           lhs.y != rhs.y ? lhs.y < rhs.y :
           lhs.w != rhs.w ? lhs.w < rhs.w :
           lhs.h != rhs.h ? lhs.h < rhs.h : false;
}

constexpr bool operator>(const rect& lhs, const rect& rhs) {
    return rhs < lhs;
}

constexpr bool operator<=(const rect& lhs, const rect& rhs) {
    return !(rhs < lhs);
}

constexpr bool operator>=(const rect& lhs, const rect& rhs) {
    return !(lhs < rhs);
}
} // sdl

#endif // GUM_VIDEO_RECT_HPP
