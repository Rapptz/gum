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

#ifndef GUM_INPUT_EVENT_HPP
#define GUM_INPUT_EVENT_HPP

#include <SDL_events.h>
#include <chrono>
#include <cstdint>

// SDL's event system is fine as-is. Just provide typedefs for consistency.
// Also possibly wrap up some functions to be more C++-like.
namespace sdl {
using controller_axis_event   = SDL_ControllerAxisEvent;
using controller_button_event = SDL_ControllerButtonEvent;
using controller_device_event = SDL_ControllerDeviceEvent;
using dollar_gesture_event    = SDL_DollarGestureEvent;
using drop_event              = SDL_DropEvent;
using finger                  = SDL_Finger;
using event                   = SDL_Event;
using joy_axis_event          = SDL_JoyAxisEvent;
using joy_ball_event          = SDL_JoyBallEvent;
using joy_button_event        = SDL_JoyButtonEvent;
using joy_device_event        = SDL_JoyDeviceEvent;
using joy_hat_event           = SDL_JoyHatEvent;
using keyboard_event          = SDL_KeyboardEvent;
using mouse_button_event      = SDL_MouseButtonEvent;
using mouse_motion_event      = SDL_MouseMotionEvent;
using mouse_wheel_event       = SDL_MouseWheelEvent;
using multi_gesture_event     = SDL_MultiGestureEvent;
using quit_event              = SDL_QuitEvent;
using syswm_event             = SDL_SysWMEvent;
using text_editing_event      = SDL_TextEditingEvent;
using text_input_event        = SDL_TextInputEvent;
using touch_finger_event      = SDL_TouchFingerEvent;
using user_event              = SDL_UserEvent;
using window_event            = SDL_WindowEvent;

// SDL_WINDOWEVENT compatible enum
namespace window_event_id {
enum : uint32_t {
    shown         = SDL_WINDOWEVENT_SHOWN,
    hidden        = SDL_WINDOWEVENT_HIDDEN,
    exposed       = SDL_WINDOWEVENT_EXPOSED,
    moved         = SDL_WINDOWEVENT_MOVED,
    resized       = SDL_WINDOWEVENT_RESIZED,
    size_changed  = SDL_WINDOWEVENT_SIZE_CHANGED,
    minimised     = SDL_WINDOWEVENT_MINIMIZED,
    maximised     = SDL_WINDOWEVENT_MAXIMIZED,
    restored      = SDL_WINDOWEVENT_RESTORED,
    enter         = SDL_WINDOWEVENT_ENTER,
    leave         = SDL_WINDOWEVENT_LEAVE,
    focus_gained  = SDL_WINDOWEVENT_FOCUS_GAINED,
    focus_lost    = SDL_WINDOWEVENT_FOCUS_LOST,
    close         = SDL_WINDOWEVENT_CLOSE
};
} // window_event

namespace events {
enum : uint32_t {
    first_event                = SDL_FIRSTEVENT,
    quit                       = SDL_QUIT,
    app_terminating            = SDL_APP_TERMINATING,
    app_low_memory             = SDL_APP_LOWMEMORY,
    app_will_enter_background  = SDL_APP_WILLENTERBACKGROUND,
    app_did_enter_background   = SDL_APP_DIDENTERBACKGROUND,
    app_will_enter_foreground  = SDL_APP_WILLENTERFOREGROUND,
    app_did_enter_foreground   = SDL_APP_DIDENTERFOREGROUND,
    window_event               = SDL_WINDOWEVENT,
    syswm_event                = SDL_SYSWMEVENT,
    key_down                   = SDL_KEYDOWN,
    key_up                     = SDL_KEYUP,
    text_editing               = SDL_TEXTEDITING,
    text_input                 = SDL_TEXTINPUT,
    mouse_motion               = SDL_MOUSEMOTION,
    mouse_button_down          = SDL_MOUSEBUTTONDOWN,
    mouse_button_up            = SDL_MOUSEBUTTONUP,
    mouse_wheel                = SDL_MOUSEWHEEL,
    joy_axis_motion            = SDL_JOYAXISMOTION,
    joy_ball_motion            = SDL_JOYBALLMOTION,
    joy_hat_motion             = SDL_JOYHATMOTION,
    joy_button_down            = SDL_JOYBUTTONDOWN,
    joy_button_up              = SDL_JOYBUTTONUP,
    joy_device_added           = SDL_JOYDEVICEADDED,
    joy_device_removed         = SDL_JOYDEVICEREMOVED,
    controller_axis_motion     = SDL_CONTROLLERAXISMOTION,
    controller_button_down     = SDL_CONTROLLERBUTTONDOWN,
    controller_button_up       = SDL_CONTROLLERBUTTONUP,
    controller_device_added    = SDL_CONTROLLERDEVICEADDED,
    controller_device_removed  = SDL_CONTROLLERDEVICEREMOVED,
    controller_device_remapped = SDL_CONTROLLERDEVICEREMAPPED,
    finger_down                = SDL_FINGERDOWN,
    finger_up                  = SDL_FINGERUP,
    finger_motion              = SDL_FINGERMOTION,
    dollar_gesture             = SDL_DOLLARGESTURE,
    dollar_record              = SDL_DOLLARRECORD,
    multi_gesture              = SDL_MULTIGESTURE,
    clipboard_update           = SDL_CLIPBOARDUPDATE,
    drop_file                  = SDL_DROPFILE,
    render_targets_reset       = SDL_RENDER_TARGETS_RESET,
    user_event                 = SDL_USEREVENT,
    last_event                 = SDL_LASTEVENT
};
} // events


namespace event_queue {
inline void clear(uint32_t type) noexcept {
    SDL_FlushEvent(type);
}

template<typename... Rest>
inline void clear(uint32_t type, Rest... rest) noexcept {
    clear(type);
    clear(rest...);
}

inline void clear_range(uint32_t min, uint32_t max) noexcept {
    SDL_FlushEvents(min, max);
}

inline bool has(uint32_t type) noexcept {
    return SDL_HasEvent(type);
}

template<typename... Rest>
inline bool has(uint32_t type, Rest... rest) noexcept {
    return has(type) && has(rest...);
}

inline bool has_range(uint32_t min, uint32_t max) noexcept {
    return SDL_HasEvents(min, max);
}

inline void pump() noexcept {
    SDL_PumpEvents();
}
} // event_queue

inline bool poll_event(event& e) noexcept {
    return SDL_PollEvent(&e);
}

inline bool wait_event(event& e) noexcept {
    return SDL_WaitEvent(&e);
}

inline bool wait_event_for(event& e, int ms) noexcept {
    return SDL_WaitEventTimeout(&e, ms);
}

template<typename Rep, typename Period>
inline bool wait_event_for(event& e, const std::chrono::duration<Rep, Period>& time) noexcept {
    return SDL_WaitEventTimeout(&e, std::chrono::duration_cast<std::chrono::milliseconds>(time).count());
}
} // sdl

#endif // GUM_INPUT_EVENT_HPP
