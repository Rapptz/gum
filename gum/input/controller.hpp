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

#ifndef GUM_INPUT_CONTROLLER_HPP
#define GUM_INPUT_CONTROLLER_HPP

#include <gum/core/error.hpp>
#include <SDL_gamecontroller.h>
#include <string>
#include <memory>

namespace sdl {
namespace detail {
struct controller_deleter {
    void operator()(SDL_GameController* controller) const noexcept {
        if(SDL_GameControllerGetAttached(controller) == SDL_TRUE) {
            SDL_GameControllerClose(controller);
            controller = nullptr;
        }
    }
};
} // detail

struct controller {
private:
    std::unique_ptr<SDL_GameController, detail::controller_deleter> ptr;
public:
    controller() = default;
    controller(int index): ptr(SDL_GameControllerOpen(index)) {
        if(ptr == nullptr) {
            GUM_ERROR_HANDLER();
        }
    }

    enum class button : int {
        invalid        = SDL_CONTROLLER_BUTTON_INVALID,
        a              = SDL_CONTROLLER_BUTTON_A,
        b              = SDL_CONTROLLER_BUTTON_B,
        x              = SDL_CONTROLLER_BUTTON_X,
        y              = SDL_CONTROLLER_BUTTON_Y,
        back           = SDL_CONTROLLER_BUTTON_BACK,
        guide          = SDL_CONTROLLER_BUTTON_GUIDE,
        start          = SDL_CONTROLLER_BUTTON_START,
        left_stick     = SDL_CONTROLLER_BUTTON_LEFTSTICK,
        right_stick    = SDL_CONTROLLER_BUTTON_RIGHTSTICK,
        left_shoulder  = SDL_CONTROLLER_BUTTON_LEFTSHOULDER,
        right_shoulder = SDL_CONTROLLER_BUTTON_RIGHTSHOULDER,
        dpad_up        = SDL_CONTROLLER_BUTTON_DPAD_UP,
        dpad_down      = SDL_CONTROLLER_BUTTON_DPAD_DOWN,
        dpad_left      = SDL_CONTROLLER_BUTTON_DPAD_LEFT,
        dpad_right     = SDL_CONTROLLER_BUTTON_DPAD_RIGHT,
        max            = SDL_CONTROLLER_BUTTON_MAX
    };

    enum class axis : int {
        invalid       = SDL_CONTROLLER_AXIS_INVALID,
        left_x        = SDL_CONTROLLER_AXIS_LEFTX,
        left_y        = SDL_CONTROLLER_AXIS_LEFTY,
        right_x       = SDL_CONTROLLER_AXIS_RIGHTX,
        right_y       = SDL_CONTROLLER_AXIS_RIGHTY,
        trigger_left  = SDL_CONTROLLER_AXIS_TRIGGERLEFT,
        trigger_right = SDL_CONTROLLER_AXIS_TRIGGERRIGHT,
        max           = SDL_CONTROLLER_AXIS_MAX
    };

    void create(int index) {
        ptr.reset(SDL_GameControllerOpen(index));
        if(ptr == nullptr) {
            GUM_ERROR_HANDLER();
        }
    }

    bool is_attached() const noexcept {
        return SDL_GameControllerGetAttached(ptr.get());
    }

    int16_t axis_state(axis a) const noexcept {
        return SDL_GameControllerGetAxis(ptr.get(), static_cast<SDL_GameControllerAxis>(a));
    }

    bool is_pressed(button b) const noexcept {
        return SDL_GameControllerGetButton(ptr.get(), static_cast<SDL_GameControllerButton>(b));
    }

    SDL_GameController* data() const noexcept {
        return ptr.get();
    }

    std::string name() const {
        const char* result = SDL_GameControllerName(ptr.get());
        if(result == nullptr) {
            return "Unknown";
        }
        return { result };
    }
};

inline controller::button to_button(const std::string& str) noexcept {
    return static_cast<controller::button>(SDL_GameControllerGetButtonFromString(str.c_str()));
}

inline controller::axis to_axis(const std::string& str) noexcept {
    return static_cast<controller::axis>(SDL_GameControllerGetAxisFromString(str.c_str()));
}

inline std::string to_string(controller::button b) {
    const char* result = SDL_GameControllerGetStringForButton(static_cast<SDL_GameControllerButton>(b));
    if(result == nullptr) {
        return "";
    }
    return { result };
}

inline std::string to_string(controller::axis a) {
    const char* result = SDL_GameControllerGetStringForAxis(static_cast<SDL_GameControllerAxis>(a));
    if(result == nullptr) {
        return "";
    }
    return { result };
}

inline int number_of_controllers() {
    int x = SDL_NumJoysticks();
    if(x < 0) {
        GUM_ERROR_HANDLER(x);
    }
    return x;
}

inline bool is_controller(int index) {
    return SDL_IsGameController(index);
}

inline bool add_controller_mapping(const std::string& mapping) {
    int result = SDL_GameControllerAddMapping(mapping.c_str());
    if(result == -1) {
        GUM_ERROR_HANDLER(false);
    }
    return result == 1;
}

inline int add_controller_mapping_from_file(const std::string& filename) {
    int result = SDL_GameControllerAddMappingsFromFile(filename.c_str());
    if(result == -1) {
        GUM_ERROR_HANDLER(result);
    }
    return result;
}

inline std::string controller_name(int index) {
    const char* result = SDL_GameControllerNameForIndex(index);
    if(result == nullptr) {
        return "Unknown";
    }
    return result;
}
} // sdl

#endif // GUM_INPUT_CONTROLLER_HPP
