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

#ifndef GUM_VIDEO_DISPLAY_MODE_HPP
#define GUM_VIDEO_DISPLAY_MODE_HPP

#include <SDL_video.h>
#include <vector>

namespace sdl {
int number_of_video_displays() {
    int result = SDL_GetNumVideoDisplays();
    if(result < 1) {
        throw error();
    }
    return result;
}

struct display_mode : SDL_DisplayMode {
    static std::vector<display_mode> available(int index = 0) {
        int count = SDL_GetNumDisplayModes(index);
        if(count < 1) {
            throw error();
        }

        display_mode mode;
        std::vector<display_mode> result;
        for(int i = 0; i < count; ++i) {
            if(SDL_GetDisplayMode(index, i, &mode)) {
                throw error();
            }
            result.push_back(mode);
        }

        return result;
    }

    static display_mode desktop(int index = 0) {
        display_mode result;
        if(SDL_GetDesktopDisplayMode(index, &result)) {
            throw error();
        }
        return result;
    }

    static display_mode closest(const display_mode& to, int index = 0) {
        display_mode result;
        if(SDL_GetClosestDisplayMode(index, &to, &result) == nullptr) {
            throw error();
        }
        return result;
    }
};
} // sdl

#endif // GUM_VIDEO_DISPLAY_MODE_HPP
