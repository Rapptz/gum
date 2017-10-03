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

#ifndef GUM_VIDEO_SURFACE_HPP
#define GUM_VIDEO_SURFACE_HPP

#include <gum/core/error.hpp>
#include <gum/platform/endian.hpp>
#include <gum/video/rect.hpp>
#include <gum/video/colour.hpp>
#include <cstdint>
#include <memory>

namespace sdl {
namespace detail {
struct surface_deleter {
    void operator()(SDL_Surface* surface) const noexcept {
        SDL_FreeSurface(surface);
    }
};

template<bool B>
struct surface_mask;

template<>
struct surface_mask<true> {
    static constexpr uint32_t red   = 0xff000000;
    static constexpr uint32_t green = 0x00ff0000;
    static constexpr uint32_t blue  = 0x0000ff00;
    static constexpr uint32_t alpha = 0x000000ff;
};

template<>
struct surface_mask<false> {
    static constexpr uint32_t red   = 0x000000ff;
    static constexpr uint32_t green = 0x0000ff00;
    static constexpr uint32_t blue  = 0x00ff0000;
    static constexpr uint32_t alpha = 0xff000000;
};
} // detail

struct surface {
private:
    std::unique_ptr<SDL_Surface, detail::surface_deleter> ptr;
public:
    static constexpr uint32_t red   = detail::surface_mask<is_big_endian::value>::red;
    static constexpr uint32_t green = detail::surface_mask<is_big_endian::value>::green;
    static constexpr uint32_t blue  = detail::surface_mask<is_big_endian::value>::blue;
    static constexpr uint32_t alpha = detail::surface_mask<is_big_endian::value>::alpha;
    surface() noexcept {
        create(1, 1, 32);
    }

    surface(int width, int height, int depth = 32) {
        create(width, height, depth);
    }

    surface(const std::string& filename) {
        load_file(filename);
    }

    void load_file(const std::string& filename) {
        // delete surface if it's already active
        if(ptr != nullptr) {
            ptr.reset(nullptr);
        }

    #ifndef GUM_IMG_DISABLED
        ptr.reset(IMG_Load(filename.c_str()));
    #else
        ptr.reset(SDL_LoadBMP(filename.c_str()));
    #endif
        if(ptr == nullptr) {
            GUM_ERROR_HANDLER_VOID();
        }
    }

    void create(int width, int height, int depth = 32) {
        ptr.reset(SDL_CreateRGBSurface(0, width, height, depth, red, green, blue, alpha));
        if(ptr == nullptr) {
            GUM_ERROR_HANDLER_VOID();
        }
    }

    SDL_Surface* data() const noexcept {
        return ptr.get();
    }

    explicit operator bool() const noexcept {
        return ptr.get() != nullptr;
    }

    rect clip() const noexcept {
        rect result;
        SDL_GetClipRect(ptr.get(), &result);
        return result;
    }

    bool clip(const rect& area) noexcept {
        return SDL_SetClipRect(ptr.get(), &area) == SDL_TRUE;
    }

    sdl::colour colour() const {
        sdl::colour result;
        if(SDL_GetSurfaceColorMod(ptr.get(), &result.r, &result.g, &result.b) != 0) {
            GUM_ERROR_HANDLER_NO_RET();
        }
        if(SDL_GetSurfaceAlphaMod(ptr.get(), &result.a) != 0) {
            GUM_ERROR_HANDLER_NO_RET();
        }
        return result;
    }

    void colour(const sdl::colour& c) {
        if(SDL_SetSurfaceColorMod(ptr.get(), c.r, c.g, c.b) != 0) {
            GUM_ERROR_HANDLER_VOID();
        }
        if(SDL_SetSurfaceAlphaMod(ptr.get(), c.a) != 0) {
            GUM_ERROR_HANDLER_VOID();
        }
    }

    SDL_Point size() const noexcept {
        return { ptr->w, ptr->h };
    }

    int length() const noexcept {
        return ptr->w * ptr->h;
    }

    bool must_lock() const noexcept {
        auto* surf = ptr.get();
        return SDL_MUSTLOCK(surf) == SDL_TRUE;
    }

    void lock() {
        if(SDL_LockSurface(ptr.get()) != 0) {
            GUM_ERROR_HANDLER_VOID();
        }
    }

    void unlock() noexcept {
        SDL_UnlockSurface(ptr.get());
    }

    uint32_t* pixels() const noexcept {
        return static_cast<uint32_t*>(ptr->pixels);
    }
};
} // sdl

#endif // GUM_VIDEO_SURFACE_HPP
