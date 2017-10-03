// gum
// Copyright (C) 2014-2016 Rapptz

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

#ifndef GUM_DETAIL_TYPE_TRAITS_HPP
#define GUM_DETAIL_TYPE_TRAITS_HPP

#include <type_traits>
#include <utility>

// forward declarations
struct SDL_Renderer;

namespace sdl {
namespace detail {
struct is_renderer_drawable_impl {
    template<typename T, typename U = decltype(std::declval<T>().draw(std::declval<SDL_Renderer*>()))>
    static std::true_type test(int);
    template<typename...>
    static std::false_type test(...);
};
} // detail

template<typename Drawable>
struct is_renderer_drawable : decltype(detail::is_renderer_drawable_impl::test<Drawable>(0)) {};
} // sdl

#endif // GUM_DETAIL_TYPE_TRAITS_HPP
