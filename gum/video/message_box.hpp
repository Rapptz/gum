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

#ifndef GUM_VIDEO_MESSAGE_BOX_HPP
#define GUM_VIDEO_MESSAGE_BOX_HPP

#include <SDL_video.h>
#include <cstdint>
#include <string>
#include <vector>

namespace sdl {
struct message_box {
private:
    SDL_MessageBoxColorScheme scheme;
    std::vector<SDL_MessageBoxButtonData> buttons;
    SDL_MessageBoxData data;
public:
    message_box() = default;

    enum : uint32_t {
        error   = SDL_MESSAGEBOX_ERROR,
        warning = SDL_MESSAGEBOX_WARNING,
        info    = SDL_MESSAGEBOX_INFORMATION
    };

    enum colour : uint32_t {
        background        = SDL_MESSAGEBOX_COLOR_BACKGROUND,
        text              = SDL_MESSAGEBOX_COLOR_TEXT,
        button_border     = SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
        button_background = SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
        button_selected   = SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
    };

    enum class button : int {
        invalid = -1,
        no = 0,
        yes = 1,
        cancel = 2
    };

    void colour(uint32_t index, SDL_MessageBoxColor colour) noexcept {
        scheme.colors[index] = colour;
    }

    void add_button(int id, const std::string& text, uint32_t flag = 0) {
        buttons.push_back({ flag, id, text.c_str() });
    }

    int show() noexcept {
        data.numbuttons = buttons.size();
        data.buttons = buttons.data();
        data.colorScheme = &scheme;
        int button_id;
        if(SDL_ShowMessageBox(&data, &button_id) != 0) {
            return -1;
        }
        return button_id;
    }

    void window(SDL_Window* win) noexcept {
        data.window = win;
    }

    void flags(uint32_t flag) noexcept {
        data.flags = flag;
    }

    void title(const std::string& str) noexcept {
        data.title = str.c_str();
    }

    void message(const std::string& str) noexcept {
        data.message = str.c_str();
    }

    static bool simple(const std::string& title, const std::string& message, uint32_t flag = info, SDL_Window* window = nullptr) noexcept {
        return SDL_ShowSimpleMessageBox(flag, title.c_str(), message.c_str(), window) == 0;
    }

    static button confirmation(const std::string& title, const std::string& message, SDL_Window* window = nullptr) noexcept {
        static const SDL_MessageBoxButtonData buttons_[] = {
            { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 2, "Cancel" },
            {                                       0, 0, "No" },
            { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "Yes" }
        };

        SDL_MessageBoxData messageboxdata = {
            SDL_MESSAGEBOX_INFORMATION, window, title.c_str(), message.c_str(), SDL_arraysize(buttons_), buttons_, nullptr
        };

        int button_id = -1;
        if(SDL_ShowMessageBox(&messageboxdata, &button_id) != 0) {
            return button::invalid;
        }
        return static_cast<button>(button_id);
    }
};
} // sdl

#endif // GUM_VIDEO_MESSAGE_BOX_HPP
