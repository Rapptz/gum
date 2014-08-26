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

#ifndef SDLPP_INIT_HPP
#define SDLPP_INIT_HPP

#include "error.hpp"
#include <SDL.h>

namespace sdl {
/**
 * @brief RAII wrapper around SDL_Init
 * @details Wraps the call of SDL_Init with the
 * corresponding SDL_Quit so you don't forget.
 *
 * Defines all the SDL_INIT_* flags through an
 * enum as well.
 *
 * Just like SDL_Init it should only be called once.
 */
struct init {
private:
    bool has_quit = false;
public:
    enum flags : int {
        timer           = SDL_INIT_TIMER,
        audio           = SDL_INIT_AUDIO,
        video           = SDL_INIT_VIDEO,
        joystick        = SDL_INIT_JOYSTICK,
        haptic          = SDL_INIT_HAPTIC,
        game_controller = SDL_INIT_GAMECONTROLLER,
        events          = SDL_INIT_EVENTS,
        no_parachute    = SDL_INIT_NOPARACHUTE,
        everything      = SDL_INIT_EVERYTHING
    };

    init(const init&) = delete;
    init(init&&) = delete;
    init& operator=(const init&) = delete;
    init& operator=(init&&) = delete;

    /**
     * @brief Initialises SDL
     * @details Initialises SDL with the flags given.
     * The enum of flags translate one to one with snake_case.
     * e.g.
     * - SDL_INIT_TIMER -> sdl::init::timer
     * - SDL_INIT_GAMECONTROLLER -> sdl::init::game_controller
     *
     * @param f flag to initialise SDL with
     */
    init(flags f = flags::everything) {
        if(SDL_Init(static_cast<int>(f)) < 0) {
            throw error();
        }
    }

    /**
     * @brief Forces an SDL_Quit
     * @details Forces an SDL_Quit. Multiple calls
     * do not quit more than once.
     */
    void quit() noexcept {
        if(!has_quit) {
            SDL_Quit();
            has_quit = true;
        }
    }

    /**
     * @brief Quits a given subsystem.
     *
     * @param f subsystem to quit
     */
    void quit(flags f) noexcept {
        if(was_initialised(f)) {
            SDL_QuitSubSystem(static_cast<int>(f));
        }
    }

    /**
     * @brief Initialises a subsystem.
     * @details Initialises a subsystem by the given
     * flag.
     *
     * @param f flag to initialise the subsystem.
     */
    void start(flags f) const {
        if(SDL_InitSubSystem(static_cast<int>(f)) < 0) {
            throw error();
        }
    }

    /**
     * @brief Checks if a subsystem was initialised
     *
     * @param f flag to check initialisation of
     * @return `true` if initialised, `false` otherwise
     */
    bool was_initialised(flags f = flags::everything) const noexcept {
        return SDL_WasInit(static_cast<int>(f));
    }

    ~init() {
        quit();
    }
};
} // sdl

#endif // SDLPP_INIT_HPP
