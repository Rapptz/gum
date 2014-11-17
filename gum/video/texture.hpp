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

#ifndef GUM_VIDEO_TEXTURE_HPP
#define GUM_VIDEO_TEXTURE_HPP

#include <gum/core/error.hpp>
#include <SDL_render.h>
#include <SDL_surface.h>
#include <utility>

namespace sdl {
struct texture {
private:
    union {
        SDL_Texture* tex;
        SDL_Surface* sur;
    } value;

    enum class ptr : char {
        none,
        texture,
        surface
    } type = ptr::none;
public:
    texture() = default;
    explicit texture(const std::string& filename) {
        load_file(filename);
    }

    texture(texture&& other) noexcept {
        switch(other.type) {
        case ptr::texture:
            std::swap(value.tex, other.value.tex);
            other.value.tex = nullptr;
            break;
        case ptr::surface:
            std::swap(value.sur, other.value.sur);
            other.value.sur = nullptr;
            break;
        default:
            break;
        }
        type = other.type;
    }

    ~texture() {
        clear();
    }

    texture& operator=(texture&& other) noexcept {
        switch(other.type) {
        case ptr::texture:
            std::swap(value.tex, other.value.tex);
            other.value.tex = nullptr;
            break;
        case ptr::surface:
            std::swap(value.sur, other.value.sur);
            other.value.sur = nullptr;
            break;
        default:
            break;
        }
        type = other.type;
        return *this;
    }

    void load_file(const std::string& filename) {
        if(type == ptr::texture) {
            SDL_DestroyTexture(value.tex);
        }
        value.sur = SDL_LoadBMP(filename.c_str());
        if(value.sur == nullptr) {
            auto&& err = last_error();
            GUM_ERROR_HANDLER(err,);
        }

        type = ptr::surface;
    }

    template<typename Window>
    void hardware_accelerate(const Window& win) {
        if(type != ptr::surface) {
            return;
        }

        auto result = SDL_CreateTextureFromSurface(win.renderer(), value.sur);
        if(result == nullptr) {
            auto&& err = last_error();
            GUM_ERROR_HANDLER(err,);
        }
        SDL_FreeSurface(value.sur);
        value.tex = result;
        type = ptr::texture;
    }

    void clear() noexcept {
        switch(type) {
        case ptr::texture:
            SDL_DestroyTexture(value.tex);
            break;
        case ptr::surface:
            SDL_FreeSurface(value.sur);
            break;
        default:
            break;
        }
        type = ptr::none;
    }

    bool is_texture() const noexcept {
        return type == ptr::texture;
    }

    bool is_surface() const noexcept {
        return type == ptr::surface;
    }

    explicit operator bool() const noexcept {
        switch(type) {
        case ptr::texture:
            return value.tex != nullptr;
        case ptr::surface:
            return value.sur != nullptr;
        default:
            return false;
        }
    }

    SDL_Texture* data() const noexcept {
        return value.tex;
    }

    SDL_Surface* surface() const noexcept {
        return value.sur;
    }
};
} // sdl

#endif // GUM_VIDEO_TEXTURE_HPP
