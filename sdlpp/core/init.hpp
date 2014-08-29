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

struct init {
private:
    bool has_quit = false;
public:
    enum flags : uint32_t {
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

    init(uint32_t subsystems = flags::video) {
        if(SDL_Init(subsystems) < 0) {
            throw error();
        }
    }

    ~init() {
        quit();
    }

    void quit() noexcept {
        if(!has_quit) {
            SDL_Quit();
            has_quit = true;
        }
    }

    void quit(uint32_t subsystem) noexcept {
        if(was_initialised(subsystem)) {
            SDL_QuitSubSystem(subsystem);
        }
    }

    void start(uint32_t subsystem) const {
        if(SDL_InitSubSystem(subsystem) < 0) {
            throw error();
        }
    }

    bool was_initialised(uint32_t subsystem = flags::video) const noexcept {
        return SDL_WasInit(subsystem);
    }
};
} // sdl

#endif // SDLPP_CORE_INIT_HPP
