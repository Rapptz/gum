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
#include <gum/video/colour.hpp>
#include <SDL_render.h>
#include <type_traits>
#include <utility>

namespace sdl {
namespace detail {
struct texture_deleter {
    void operator()(SDL_Texture* texture) const noexcept {
        SDL_DestroyTexture(texture);
    }
};

struct has_renderer_impl {
    template<typename T, typename U = decltype(std::declval<T&>().renderer())>
    static std::is_same<U, SDL_Renderer*> test(int);
    template<typename...>
    static std::false_type test(...);
};

template<typename T>
struct has_renderer : decltype(has_renderer_impl::test<T>(0)) {};

struct renderer_trait {
    template<typename T, typename std::enable_if<has_renderer<T>::value, int>::type = 0>
    static SDL_Renderer* get(const T& t) {
        return t.renderer();
    }

    template<typename T, typename std::enable_if<!has_renderer<T>::value, int>::type = 0>
    static SDL_Renderer* get(const T& t) {
        return t;
    }
};

template<typename T>
struct is_valid_renderer : std::integral_constant<bool, std::is_same<T, SDL_Renderer*>::value || has_renderer<T>::value> {};
} // detail

struct texture {
private:
    std::unique_ptr<SDL_Texture, detail::texture_deleter> ptr;
public:
    texture() = default;

    template<typename Window>
    texture(int width, int height, const Window& win, int access = SDL_TEXTUREACCESS_STATIC) {
        create(width, height, win, access);
    }

    template<typename Window>
    texture(const std::string& filename, const Window& win) {
        load_file(filename, win);
    }

    template<typename Window>
    void create(int width, int height, const Window& win, int access = SDL_TEXTUREACCESS_STATIC) {
        static_assert(detail::is_valid_renderer<Window>::value, "Type must either be an sdl::window or SDL_Renderer*");
        ptr.reset(SDL_CreateTexture(detail::renderer_trait::get(win), SDL_PIXELFORMAT_RGBA8888, access, width, height));
        if(ptr == nullptr) {
            GUM_ERROR_HANDLER_VOID();
        }
    }

    template<typename Window>
    void load_file(const std::string& filename, const Window& win) {
        static_assert(detail::is_valid_renderer<Window>::value, "Type must either be an sdl::window or SDL_Renderer*");
        #ifndef GUM_DISABLED_IMG
        auto* surface = IMG_Load(filename.c_str());
        #else
        auto* surface = SDL_LoadBMP(filename.c_str());
        #endif

        if(surface == nullptr) {
            GUM_ERROR_HANDLER_VOID();
        }

        ptr.reset(SDL_CreateTextureFromSurface(detail::renderer_trait::get(win), surface));
        SDL_FreeSurface(surface);

        if(ptr == nullptr) {
            GUM_ERROR_HANDLER_VOID();
        }
    }

    SDL_Texture* data() const noexcept {
        return ptr.get();
    }

    explicit operator bool() const noexcept {
        return ptr.get() != nullptr;
    }

    SDL_Point size() const {
        SDL_Point result;
        if(SDL_QueryTexture(ptr.get(), nullptr, nullptr, &result.x, &result.y) != 0) {
            GUM_ERROR_HANDLER_NO_RET();
        }
        return result;
    }

    sdl::colour colour() const {
        sdl::colour result;
        if(SDL_GetTextureColorMod(ptr.get(), &result.r, &result.g, &result.b) != 0) {
            GUM_ERROR_HANDLER_NO_RET();
        }
        if(SDL_GetTextureAlphaMod(ptr.get(), &result.a) != 0) {
            GUM_ERROR_HANDLER_NO_RET();
        }
        return result;
    }

    void colour(const sdl::colour& c) {
        if(SDL_SetTextureColorMod(ptr.get(), c.r, c.g, c.b) != 0) {
            GUM_ERROR_HANDLER_NO_RET();
        }
        if(SDL_SetTextureAlphaMod(ptr.get(), c.a) != 0) {
            GUM_ERROR_HANDLER_NO_RET();
        }
    }
};
} // sdl

#endif // GUM_VIDEO_TEXTURE_HPP
