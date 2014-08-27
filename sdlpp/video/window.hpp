// SDL++
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

#ifndef SDLPP_VIDEO_WINDOW_HPP
#define SDLPP_VIDEO_WINDOW_HPP

#include "surface.hpp"
#include <SDL_video.h>
#include <string>
#include <cstdint>

namespace sdl {
/**
 * @brief A window that could be drawn to.
 * @details This struct is a wrapper around `SDL_Window` that
 * allows for easier construction and a more object oriented way
 * of retrieving and setting its properties.
 */
struct window {
private:
    std::unique_ptr<SDL_Window, decltype(SDL_DestroyWindow)*> ptr;
    surface_view surf;
public:
    static const auto npos     = SDL_WINDOWPOS_UNDEFINED;       ///< Represents an undefined window position.
    static const auto centered = SDL_WINDOWPOS_CENTERED;        ///< Represents a centered window position.

    /**
     * @brief Flags used to initialise the window with.
     * @details The flags are pretty similar to the ones provided
     * by the all-caps SDL version. The difference is it's made
     * to lower case and `snake_case`. Examples:
     *
     * - `SDL_WINDOW_FULLSCREEN` -> `sdl::window::fullscreen`.
     * - `SDL_WINDOW_INPUT_GRABBED` -> `sdl::window::input_grabbed`.
     *
     * Just like regular SDL, you can use bitwise OR to combine flags
     * together. Since `SDL_WINDOW_SHOWN` is ignored by `SDL_CreateWindow`
     * it is not available in this enum nor should it be used.
     */
    enum flags : uint32_t {
        fullscreen         = SDL_WINDOW_FULLSCREEN,           ///< A fullscreen window.
        fullscreen_desktop = SDL_WINDOW_FULLSCREEN_DESKTOP,   ///< A fullscreen window at desktop resolution.
        opengl             = SDL_WINDOW_OPENGL,               ///< A window usable with OpenGL.
        hidden             = SDL_WINDOW_HIDDEN,               ///< A window that is not visible.
        borderless         = SDL_WINDOW_BORDERLESS,           ///< A borderless window.
        resizable          = SDL_WINDOW_RESIZABLE,            ///< A window that can be resized.
        minimized          = SDL_WINDOW_MINIMIZED,            ///< A window that starts out minimised.
        maximized          = SDL_WINDOW_MAXIMIZED,            ///< A window that starts out maximised.
        input_grabbed      = SDL_WINDOW_INPUT_GRABBED,        ///< A window that grabs all input focus.
        highdpi            = SDL_WINDOW_ALLOW_HIGHDPI         ///< A window that supports high-DPI if available.
    };

    /**
     * @brief Creates the window.
     * @details The window is created as if calling `SDL_CreateWindow` with
     * no position specified. If the window cannot be created, then an error is
     * thrown.
     *
     * @param title The title string of the window.
     * @param width The width of the window.
     * @param height The height of the window.
     * @param f The flags to pass to initialisation of the window.
     */
    window(const std::string& title, int width, int height, uint32_t f = 0):
    ptr(SDL_CreateWindow(title.c_str(), npos, npos, width, height, f), SDL_DestroyWindow) {
        if(ptr == nullptr) {
            throw error();
        }

        surf = surface_view(SDL_GetWindowSurface(ptr.get()));
    }

    /**
     * @brief Checks if the window is currently open.
     */
    bool is_open() const noexcept {
        return ptr != nullptr;
    }

    /**
     * @brief Fills the window with a colour.
     */
    void fill(const color& c) {
        surf.fill(c);
    }

    /**
     * @brief Returns the internal SDL_Window pointer.
     * @details This pointer should be considered a 'view'.
     * There is no way to retrieve ownership of the window's `SDL_Window`
     * pointer. As a result, calling `SDL_DestroyWindow` on this pointer
     * is not advised at all.
     * @return The internal `SDL_Window` pointer.
     */
    SDL_Window* data() const noexcept {
        return ptr;
    }

    /**
     * @brief Closes the window.
     */
    void close() {
        ptr.reset(nullptr);
    }

    template<typename Deleter>
    void display(const basic_surface<Deleter>& s) {
        surf.blit(s);
    }

    /**
     * @brief Updates the window surface.
     * @details This function is equivalent to calling
     * `SDL_UpdateWindowSurface`.
     */
    void update() {
        SDL_UpdateWindowSurface(ptr.get());
    }
};
} // sdl

#endif // SDLPP_VIDEO_WINDOW_HPP
