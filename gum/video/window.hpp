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

#ifndef GUM_VIDEO_WINDOW_HPP
#define GUM_VIDEO_WINDOW_HPP

#include <gum/core/error.hpp>
#include <gum/detail/type_traits.hpp>
#include <gum/video/vector.hpp>
#include <gum/video/colour.hpp>
#include <memory>
#include <SDL_render.h>
#include <SDL_video.h>
#include <SDL_mouse.h>
#include <string>
#include <cstdint>

namespace sdl {
struct window_deleter {
    void operator()(SDL_Window* window) const noexcept {
        if(window != nullptr) {
            SDL_DestroyWindow(window);
            window = nullptr;
        }
    }
};

struct renderer_deleter {
    void operator()(SDL_Renderer* renderer) const noexcept {
        if(renderer != nullptr) {
            SDL_DestroyRenderer(renderer);
            renderer = nullptr;
        }
    }
};

namespace renderer {
enum : uint32_t {
    software       = SDL_RENDERER_SOFTWARE,
    accelerated    = SDL_RENDERER_ACCELERATED,
    present_vsync  = SDL_RENDERER_PRESENTVSYNC,
    target_texture = SDL_RENDERER_TARGETTEXTURE,
};
} // renderer

struct window {
private:
    std::unique_ptr<SDL_Window, window_deleter> ptr;
    std::unique_ptr<SDL_Renderer, renderer_deleter> render;
public:
    static const auto npos     = SDL_WINDOWPOS_UNDEFINED;
    static const auto centered = SDL_WINDOWPOS_CENTERED;

    enum : uint32_t {
        fullscreen         = SDL_WINDOW_FULLSCREEN,
        fullscreen_desktop = SDL_WINDOW_FULLSCREEN_DESKTOP,
        opengl             = SDL_WINDOW_OPENGL,
        hidden             = SDL_WINDOW_HIDDEN,
        borderless         = SDL_WINDOW_BORDERLESS,
        resizable          = SDL_WINDOW_RESIZABLE,
        minimized          = SDL_WINDOW_MINIMIZED,
        maximized          = SDL_WINDOW_MAXIMIZED,
        input_grabbed      = SDL_WINDOW_INPUT_GRABBED,
        highdpi            = SDL_WINDOW_ALLOW_HIGHDPI
    };


    window(const std::string& title, const SDL_DisplayMode& display, uint32_t flag = 0):
        window(title, display.w, display.h, flag) {}

    window(const std::string& title, int width, int height, uint32_t flag = 0):
        ptr(nullptr), render(nullptr) {
        decltype(ptr) window_ptr(SDL_CreateWindow(title.c_str(), npos, npos, width, height, flag));
        if(window_ptr == nullptr) {
            GUM_ERROR_HANDLER_VOID();
        }

        decltype(render) render_ptr(SDL_CreateRenderer(window_ptr.get(), -1, renderer::accelerated));
        if(render_ptr == nullptr) {
            GUM_ERROR_HANDLER_VOID();
        }

        ptr.swap(window_ptr);
        render.swap(render_ptr);
    }

    bool is_open() const noexcept {
        return ptr != nullptr;
    }

    void clear(const colour& c = colour::black()) {
        SDL_SetRenderDrawColor(render.get(), c.r, c.g, c.b, c.a);
        SDL_RenderClear(render.get());
    }

    SDL_Window* data() const noexcept {
        return ptr.get();
    }

    SDL_Renderer* renderer() const noexcept {
        return render.get();
    }

    template<typename Drawable>
    void draw(Drawable& drawable) {
        static_assert(is_renderer_drawable<Drawable>::value, "Must provide a void draw(SDL_Renderer*) member function");
        drawable.draw(render.get());
    }

    float brightness() const noexcept {
        return SDL_GetWindowBrightness(ptr.get());
    }

    void brightness(float bright) {
        if(SDL_SetWindowBrightness(ptr.get(), bright)) {
            GUM_ERROR_HANDLER_VOID();
        }
    }

    int id() const noexcept {
        return SDL_GetWindowID(ptr.get());
    }

    uint32_t flags() const noexcept {
        return SDL_GetWindowFlags(ptr.get());
    }

    void grab_input(bool b = true) noexcept {
        SDL_SetWindowGrab(ptr.get(), b ? SDL_TRUE : SDL_FALSE);
    }

    void mouse_position(int x, int y) noexcept {
        SDL_WarpMouseInWindow(ptr.get(), x, y);
    }

    void mouse_position(const vector& pos) noexcept {
        mouse_position(pos.x, pos.y);
    }

    bool is_input_grabbed() const noexcept {
        return SDL_GetWindowGrab(ptr.get()) != SDL_FALSE;
    }

    void maximum_size(int width, int height) noexcept {
        SDL_SetWindowMaximumSize(ptr.get(), width, height);
    }

    void maximum_size(const vector& size) noexcept {
        maximum_size(size.x, size.y);
    }

    vector maximum_size() const noexcept {
        vector result;
        SDL_GetWindowMaximumSize(ptr.get(), &result.x, &result.y);
        return result;
    }

    void minimum_size(int width, int height) noexcept {
        SDL_SetWindowMinimumSize(ptr.get(), width, height);
    }

    void minimum_size(const vector& size) noexcept {
        minimum_size(size.x, size.y);
    }

    vector minimum_size() const noexcept {
        vector result;
        SDL_GetWindowMinimumSize(ptr.get(), &result.x, &result.y);
        return result;
    }

    void position(int x, int y) noexcept {
        SDL_SetWindowPosition(ptr.get(), x, y);
    }

    void position(const vector& pos) noexcept {
        position(pos.x, pos.y);
    }

    vector position() noexcept {
        vector result;
        SDL_GetWindowPosition(ptr.get(), &result.x, &result.y);
        return result;
    }

    void resize(int width, int height) noexcept {
        SDL_SetWindowSize(ptr.get(), width, height);
    }

    void resize(const vector& size) noexcept {
        resize(size.x, size.y);
    }

    vector size() const noexcept {
        vector result;
        SDL_GetWindowSize(ptr.get(), &result.x, &result.y);
        return result;
    }

    std::string title() const noexcept {
        return SDL_GetWindowTitle(ptr.get());
    }

    void title(const std::string& str) noexcept {
        SDL_SetWindowTitle(ptr.get(), str.c_str());
    }

    void show() noexcept {
        SDL_ShowWindow(ptr.get());
    }

    void hide() noexcept {
        SDL_HideWindow(ptr.get());
    }

    void maximise() noexcept {
        SDL_MaximizeWindow(ptr.get());
    }

    void minimise() noexcept {
        SDL_MinimizeWindow(ptr.get());
    }

    void restore() noexcept {
        SDL_RestoreWindow(ptr.get());
    }

    void raise() noexcept {
        SDL_RaiseWindow(ptr.get());
    }

    void bordered(bool b = true) noexcept {
        SDL_SetWindowBordered(ptr.get(), b ? SDL_TRUE : SDL_FALSE);
    }

    void to_fullscreen(bool b = true) {
        if(SDL_SetWindowFullscreen(ptr.get(), b ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0)) {
            GUM_ERROR_HANDLER_VOID();
        }
    }

    void close() noexcept {
        ptr.reset(nullptr);
    }

    void display() noexcept {
        SDL_RenderPresent(render.get());
    }

    void swap_window()
    {
        SDL_GL_SwapWindow(data());
    }
};
} // sdl

#endif // GUM_VIDEO_WINDOW_HPP
