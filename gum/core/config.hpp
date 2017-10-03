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

#ifndef GUM_CORE_CONFIG_HPP
#define GUM_CORE_CONFIG_HPP

// provides configuration macros for gum
#if defined(GUM_RAW_SDL)
#   if !defined(GUM_IMG_DISABLED)
#       define GUM_IMG_DISABLED 1
#   endif
#endif // disable all

/**
 * We're going to over-zealously include the entirety of SDL so we don't
 * have to deal with the different ways the file can be included or installed
 * on different systems. Since we need to call SDL_Init anyway there's no actual
 * penalty in compilation speeds.
 */

#if defined(__has_include)
#   if __has_include(<SDL2/SDL.h>)
#      include <SDL2/SDL.h>
#   elif __has_include(<SDL/SDL.h>)
#      include <SDL/SDL.h>
#   elif __has_include(<SDL.h>)
#      include <SDL.h>
#   endif
#else
#   include <SDL.h>
#endif

#ifndef GUM_IMG_DISABLED
#   if defined(__has_include)
#      if __has_include(<SDL2/SDL_image.h>)
#         include <SDL2/SDL_image.h>
#      elif __has_include(<SDL/SDL_image.h>)
#         include <SDL/SDL_image.h>
#      elif __has_include(<SDL_image.h>)
#         include <SDL_image.h>
#      endif
#   else
#     include <SDL_image.h>
#   endif
#endif

#endif // GUM_CORE_CONFIG_HPP
