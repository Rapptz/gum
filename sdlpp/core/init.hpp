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

#ifndef SDLPP_CORE_INIT_HPP
#define SDLPP_CORE_INIT_HPP

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
    /**
     * @brief Flags that specify what subsystem to initialise.
     * @details These flags should be `OR`'d together to initialise
     * multiple subsystems. e.g. `sdl::init::timer | sdl::init::audio`
     * to initialise the timer and audio subsystems. The flags are
     * the same as the ones from SDL except turned lower case and in
     * snake_case.
     */
    enum flags : int {
        timer           = SDL_INIT_TIMER,           ///< Initialises the timer subsystem
        audio           = SDL_INIT_AUDIO,           ///< Initialises the audio subsystem
        video           = SDL_INIT_VIDEO,           ///< Initialises the video subsystem
        joystick        = SDL_INIT_JOYSTICK,        ///< Initialises the joystick subsystem
        haptic          = SDL_INIT_HAPTIC,          ///< Initialises the force feedback subsystem
        game_controller = SDL_INIT_GAMECONTROLLER,  ///< Initialises the game controller subsystem
        events          = SDL_INIT_EVENTS,          ///< Initialises the events subsystem
        everything      = SDL_INIT_EVERYTHING       ///< Initialises every subsystem
    };

    init(const init&) = delete;
    init(init&&) = delete;
    init& operator=(const init&) = delete;
    init& operator=(init&&) = delete;

    /**
     * @brief Initialises SDL
     * @details Initialises SDL with the flags given. By default,
     * it just initialises the video subsystem. `SDL_Init` also
     * initialises the File I/O, Threading, and Event Handling
     * subsystems.
     *
     * @param subsystems The subsystems to initialise SDL with
     */
    init(int subsystems = flags::video) {
        if(SDL_Init(subsystems) < 0) {
            throw error();
        }
    }

    /**
     * @brief The destructor.
     * @details Calls `SDL_Quit` internally to quit all the subsystems.
     */
    ~init() {
        quit();
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
     * @param subsystem The subsystem to quit
     */
    void quit(int subsystem) noexcept {
        if(was_initialised(subsystem)) {
            SDL_QuitSubSystem(subsystem);
        }
    }

    /**
     * @brief Initialises a subsystem.
     * @details Initialises a subsystem by the given
     * flag.
     *
     * @param subsystem The subsystem to initialise.
     */
    void start(int subsystem) const {
        if(SDL_InitSubSystem(subsystem) < 0) {
            throw error();
        }
    }

    /**
     * @brief Checks if a subsystem was initialised
     *
     * @param subsystem The subsystem to check initialisation of.
     * @return `true` if initialised, `false` otherwise.
     */
    bool was_initialised(int subsystem = flags::video) const noexcept {
        return SDL_WasInit(subsystem);
    }
};
} // sdl

#endif // SDLPP_CORE_INIT_HPP
