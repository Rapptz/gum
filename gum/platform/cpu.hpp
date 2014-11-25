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

#ifndef GUM_PLATFORM_CPU_HPP
#define GUM_PLATFORM_CPU_HPP

#include <SDL_cpuinfo.h>

namespace sdl {
inline bool has_3dnow() noexcept {
    return SDL_Has3DNow() == SDL_TRUE;
}

inline bool has_avx() noexcept {
    return SDL_HasAVX() == SDL_TRUE;
}

inline bool has_altivec() noexcept {
    return SDL_HasAltiVec() == SDL_TRUE;
}

inline bool has_mmx() noexcept {
    return SDL_HasMMX() == SDL_TRUE;
}

inline bool has_rdtsc() noexcept {
    return SDL_HasRDTSC() == SDL_TRUE;
}

inline bool has_sse() noexcept {
    return SDL_HasSSE() == SDL_TRUE;
}

inline bool has_sse2() noexcept {
    return SDL_HasSSE2() == SDL_TRUE;
}

inline bool has_sse3() noexcept {
    return SDL_HasSSE3() == SDL_TRUE;
}

inline bool has_sse41() noexcept {
    return SDL_HasSSE41() == SDL_TRUE;
}

inline bool has_sse42() noexcept {
    return SDL_HasSSE42() == SDL_TRUE;
}

inline int system_ram() noexcept {
    return SDL_GetSystemRAM();
}

inline int logical_cpu_cores() noexcept {
    return SDL_GetCPUCount();
}

inline int cpu_cache_line_size() noexcept {
    return SDL_GetCPUCacheLineSize();
}
} // sdl

#endif // GUM_PLATFORM_CPU_HPP

