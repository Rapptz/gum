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

#ifndef GUM_INPUT_JOYSTICK_HPP
#define GUM_INPUT_JOYSTICK_HPP

#include <gum/core/error.hpp>
#include <SDL_joystick.h>
#include <cstdint>
#include <string>
#include <memory>

namespace sdl {
struct joystick_deleter {
    void operator()(SDL_Joystick* joy) const noexcept {
        if(SDL_JoystickGetAttached(joy) == SDL_TRUE) {
            SDL_JoystickClose(joy);
        }
    }
};

using joystick_id   = SDL_JoystickID;
using joystick_guid = SDL_JoystickGUID;

inline int number_of_joysticks() {
    int x = SDL_NumJoysticks();
    if(x < 0) {
        auto&& err = last_error();
        GUM_ERROR_HANDLER(err, x);
    }
    return x;
}

inline std::string joystick_name_at(int index) noexcept {
    const char* name = SDL_JoystickNameForIndex(index);
    if(name == nullptr) {
        return "";
    }
    return { name };
}

namespace hat {
enum : uint8_t {
    centered    = SDL_HAT_CENTERED,
    up          = SDL_HAT_UP,
    right       = SDL_HAT_RIGHT,
    down        = SDL_HAT_DOWN,
    left        = SDL_HAT_LEFT,
    right_up    = SDL_HAT_RIGHTUP,
    right_down  = SDL_HAT_RIGHTDOWN,
    left_up     = SDL_HAT_LEFTUP,
    left_down   = SDL_HAT_LEFTDOWN
};
} // hat

struct joystick {
private:
    std::unique_ptr<SDL_Joystick, joystick_deleter> ptr;
public:
    joystick() noexcept = default;
    joystick(int index = 0): ptr(SDL_JoystickOpen(index)) {
        if(ptr == nullptr) {
            auto&& err = last_error();
            GUM_ERROR_HANDLER(err,);
        }
    }

    bool is_attached() const noexcept {
        return SDL_JoystickGetAttached(ptr.get());
    }

    int16_t axis(int i) const {
        int16_t result = SDL_JoystickGetAxis(ptr.get(), i);
        if(result == 0) {
            auto&& err = last_error();
            GUM_ERROR_HANDLER(err, result);
        }
        return result;
    }

    bool is_pressed(int button) const noexcept {
        return SDL_JoystickGetButton(ptr.get(), button);
    }

    SDL_Joystick* data() const noexcept {
        return ptr.get();
    }

    std::string name() const noexcept {
        const char* result = SDL_JoystickName(ptr.get());
        if(result == nullptr) {
            return "";
        }
        return { result };
    }

    int axes() const {
        int result = SDL_JoystickNumAxes(ptr.get());
        if(result < 0) {
            auto&& err = last_error();
            GUM_ERROR_HANDLER(err, result);
        }
        return result;
    }

    int buttons() const {
        int result = SDL_JoystickNumButtons(ptr.get());
        if(result < 0) {
            auto&& err = last_error();
            GUM_ERROR_HANDLER(err, result);
        }
        return result;
    }

    int hats() const {
        int result = SDL_JoystickNumHats(ptr.get());
        if(result < 0) {
            auto&& err = last_error();
            GUM_ERROR_HANDLER(err, result);
        }
        return result;
    }

    uint8_t hat_status(int index = 0) const noexcept {
        return SDL_JoystickGetHat(ptr.get(), index);
    }

    joystick_guid guid() const noexcept {
        return SDL_JoystickGetGUID(ptr.get());
    }

    joystick_id id() const {
        joystick_id result = SDL_JoystickInstanceID(ptr.get());
        if(result == 0) {
            auto&& err = last_error();
            GUM_ERROR_HANDLER(err, result);
        }
        return result;
    }
};
} // sdl

#endif // GUM_INPUT_JOYSTICK_HPP
