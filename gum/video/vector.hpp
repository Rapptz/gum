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

#ifndef GUM_VIDEO_VECTOR_HPP
#define GUM_VIDEO_VECTOR_HPP

#include <SDL_rect.h>
#include <cmath>

namespace sdl {
struct vector : SDL_Point {
    constexpr vector() noexcept: SDL_Point{0, 0} {}
    constexpr vector(int x, int y) noexcept: SDL_Point{x, y} {}

    constexpr int length_squared() const noexcept {
        return (x * x) + (y * y);
    }

    double length() const noexcept {
        return std::sqrt(length_squared());
    }

    constexpr bool is_unit() const noexcept {
        return length_squared() == 1;
    }

    void normalise() {
        int len = static_cast<int>(length());
        if(len != 0 && len != 1) {
            x /= len;
            y /= len;
        }
    }

    vector normalised() const noexcept {
        vector result = { x, y };
        result.normalise();
        return result;
    }

    vector& operator+=(const vector& rhs) noexcept {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    vector& operator-=(const vector& rhs) noexcept {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    vector& operator/=(const vector& rhs) noexcept {
        x /= rhs.x;
        y /= rhs.y;
        return *this;
    }

    vector& operator*=(const vector& rhs) noexcept {
        x *= rhs.x;
        y *= rhs.y;
        return *this;
    }

    vector& operator*=(int scalar) noexcept {
        x *= scalar;
        y *= scalar;
        return *this;
    }
};

constexpr vector operator+(const vector& lhs, const vector& rhs) noexcept {
    return { lhs.x + rhs.x, lhs.y + rhs.y };
}

constexpr vector operator-(const vector& lhs, const vector& rhs) noexcept {
    return { lhs.x - rhs.x, lhs.y - rhs.y };
}

constexpr vector operator*(const vector& lhs, const vector& rhs) noexcept {
    return { lhs.x * rhs.x, lhs.y * rhs.y };
}

constexpr vector operator*(const vector& lhs, int scalar) noexcept {
    return { lhs.x * scalar, lhs.y * scalar };
}

constexpr vector operator*(int scalar, const vector& rhs) noexcept {
    return { rhs.x * scalar, rhs.y * scalar };
}

constexpr vector operator/(const vector& lhs, const vector& rhs) noexcept {
    return { lhs.x / rhs.x, lhs.y / rhs.y };
}

constexpr vector operator-(const vector& unary) noexcept {
    return { -unary.x, -unary.y };
}

constexpr bool operator==(const vector& lhs, const vector& rhs) noexcept {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

constexpr bool operator!=(const vector& lhs, const vector& rhs) noexcept {
    return !(lhs == rhs);
}

constexpr int dot(const vector& lhs, const vector& rhs) noexcept {
    return (lhs.x * rhs.x) + (lhs.y * rhs.y);
}

constexpr int determinant(const vector& lhs, const vector& rhs) noexcept {
    return (lhs.x * rhs.y) - (rhs.x * lhs.y);
}

inline int distance_squared(const vector& from, const vector& to) noexcept {
    int dx = from.x - to.x;
    int dy = from.y - to.y;
    return (dx * dx) + (dy * dy);
}

inline double distance(const vector& from, const vector& to) noexcept {
    return std::sqrt(distance_squared(from, to));
}

inline double angle_between(const vector& from, const vector& to) noexcept {
    return std::acos(dot(from, to) / (from.length() * to.length()));
}

inline double direction(const vector& from, const vector& to) noexcept {
    return std::atan2(to.y - from.y, to.x - from.x);
}
} // sdl

#endif // GUM_VIDEO_VECTOR_HPP
