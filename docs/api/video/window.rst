.. default-domain:: cpp
.. highlight:: cpp
.. _sdlpp-video-window:

Window Management
===================

One of the nicest features of SDL is the ability to easily create a window regardless of the platform used.
SDL++ simplifies this even further by giving ``SDL_Window*`` a more object oriented API that interacts
seamlessly with the rest of the SDL++ API.

This file can be included through::

    #include <sdlpp/video/window.hpp>

.. namespace:: sdl

.. class:: window

    .. member:: static const auto npos

        Defines a position that is undefined. Equivalent to ``SDL_WINDOWPOS_UNDEFINED``.
    .. member:: static const auto centered

        Defines a position that is centered. Equivalent to ``SDL_WINDOWPOS_CENTERED``.
    .. type:: enum flags

        Defines the flags that are used for initialisation of the window. These
        are the same as the ``SDL_WINDOW_*`` flags except turned lower case and into
        snake_case.

        .. c:var fullscreen

            A fullscreen window.
        .. c:var fullscreen_desktop

            A fullscreen window at desktop resolution.
        .. c:var opengl

            A window usable with OpenGL.
        .. c:var hidden

            A window that is not visible.
        .. c:var borderless

            A borderless window.
        .. c:var resizable

            A window that can be resized.
        .. c:var minimized

            A window that starts out minimised.
        .. c:var maximized

            A window that starts out maximised.
        .. c:var input_grabbed

            A window that grabs all input focus.
        .. c:var highdpi

            A window that supports high-DPI if available.

    .. function:: window(const std::string& title, int width, int height, uint32_t f = 0)

        Creates a window with a title and a height and width. Initialisation flags
        could also be specified, but they default to zero. If window creation fails
        then :class:`error` is thrown.

        **Parameters:**

        - **title**: The title of the window.
        - **width**: The width of the window.
        - **height**: The height of the window.
        - **f**: The flags to initialise the window with.

    .. function:: bool is_open() const noexcept

        Checks if the window is open.
    .. function:: void fill(const colour& c)

        Fills the window with the specified :class:`colour`.
    .. function:: SDL_Window* data() const noexcept

        Returns the underlying pointer to the ``SDL_Window`` structure.
    .. function:: void close()

        Closes the window.
    .. function:: void update()

        Updates the window surface.
