// gum
// Copyright (C) 2016 Borgleader

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

#ifndef GUM_GL_CONTEXT_HPP
#define GUM_GL_CONTEXT_HPP

#include <gum/video/window.hpp>

namespace sdl {
namespace gl {
struct context {
    enum class flags : int32_t {
        none = 0,
        debug = SDL_GL_CONTEXT_DEBUG_FLAG,
        forward_compatible = SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG,
        robust_access = SDL_GL_CONTEXT_ROBUST_ACCESS_FLAG,
        reset_isolation = SDL_GL_CONTEXT_RESET_ISOLATION_FLAG
    };

    enum class profile_mask : int32_t {
        core = SDL_GL_CONTEXT_PROFILE_CORE,
        compatibility = SDL_GL_CONTEXT_PROFILE_COMPATIBILITY,
        es = SDL_GL_CONTEXT_PROFILE_ES
    };

    struct version {
        int major;
        int minor;
    };

    explicit context(window& w) noexcept: gl_context(SDL_GL_CreateContext(w.data())) {}

    ~context() {
        if(gl_context) {
            SDL_GL_DeleteContext(gl_context);
        }
    }

    context(const context&) = delete;
    context(context&&) = delete;

    context& operator=(const context&) = delete;
    context& operator=(context&&) = delete;

    int make_current(window& w) const {
        return SDL_GL_MakeCurrent(w.data(), gl_context);
    }

    explicit operator bool() const {
        return gl_context != nullptr;
    }
private:
    SDL_GLContext gl_context;
};

enum class attribute : int32_t {
    red_size = SDL_GL_RED_SIZE,
    green_size = SDL_GL_GREEN_SIZE,
    blue_size = SDL_GL_BLUE_SIZE,
    alpha_size = SDL_GL_ALPHA_SIZE,
    buffer_size = SDL_GL_BUFFER_SIZE,
    depth_size = SDL_GL_DEPTH_SIZE,
    stencil_size = SDL_GL_STENCIL_SIZE,
    accum_red_size = SDL_GL_ACCUM_RED_SIZE,
    accum_green_size = SDL_GL_ACCUM_GREEN_SIZE,
    accum_blue_size = SDL_GL_ACCUM_BLUE_SIZE,
    accum_alpha_size = SDL_GL_ACCUM_ALPHA_SIZE,
    multisamplebuffers = SDL_GL_MULTISAMPLEBUFFERS,
    multisamplesamples = SDL_GL_MULTISAMPLESAMPLES,
};

constexpr auto red_size = attribute::red_size;
constexpr auto green_size = attribute::green_size;
constexpr auto blue_size = attribute::blue_size;
constexpr auto alpha_size = attribute::alpha_size;
constexpr auto buffer_size = attribute::buffer_size;
constexpr auto depth_size = attribute::depth_size;
constexpr auto stencil_size = attribute::stencil_size;
constexpr auto accum_red_size = attribute::accum_red_size;
constexpr auto accum_green_size = attribute::accum_green_size;
constexpr auto accum_blue_size = attribute::accum_blue_size;
constexpr auto accum_alpha_size = attribute::accum_alpha_size;
constexpr auto multisamplebuffers = attribute::multisamplebuffers;
constexpr auto multisamplesamples = attribute::multisamplesamples;

enum class feature {
    doublebuffer = SDL_GL_DOUBLEBUFFER,
    stereo = SDL_GL_STEREO,
    accelerated_visual = SDL_GL_ACCELERATED_VISUAL,
    share_with_current_context = SDL_GL_SHARE_WITH_CURRENT_CONTEXT,
    framebuffer_srgb_capable = SDL_GL_FRAMEBUFFER_SRGB_CAPABLE,
    context_release_behavior = SDL_GL_CONTEXT_RELEASE_BEHAVIOR
};

constexpr auto doublebuffer = feature::doublebuffer;
constexpr auto stereo = feature::stereo;
constexpr auto accelerated_visual = feature::accelerated_visual;
constexpr auto share_with_current_context = feature::share_with_current_context;
constexpr auto famebuffer_srgb_capable = feature::framebuffer_srgb_capable;
constexpr auto context_release_behavior = feature::context_release_behavior;

int set_attribute(context::flags flags) {
    return SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, static_cast<int>(flags));
}

int set_attribute(context::profile_mask mask) {
    return SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, static_cast<int>(mask));
}

int set_attribute(context::version v) {
    auto ret = SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, v.major);
    if (ret != 0)
        return ret;

    return SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, v.minor);
}

int set_attribute(attribute attr, int value) {
    return SDL_GL_SetAttribute(static_cast<SDL_GLattr>(attr), value);
}

int set_attribute(feature feat, bool enabled) {
    return SDL_GL_SetAttribute(static_cast<SDL_GLattr>(feat), enabled ? 0 : 1);
}

int set_swap_interval(int interval) {
    return SDL_GL_SetSwapInterval(interval);
}
} // gl
} // sdl

#endif // GUM_GL_CONTEXT_HPP
