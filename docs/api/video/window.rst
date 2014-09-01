.. default-domain:: cpp
.. highlight:: cpp
.. _gum-video-window:

Window Management
===================

.. |error| replace:: :ref:`gum-core-error`

SDL has the ability to create windows easily regardless of the platform used.
``gum`` simplifies this even further by giving ``SDL_Window*`` a more object oriented API that interacts
seamlessly with the rest of the ``gum`` API.

This file can be included through::

    #include <gum/video/window.hpp>

.. namespace:: sdl

An enumerator is provided in the ``sdl::renderer`` namespace. This is used to store the flags
for initialisation of the internal ``SDL_Renderer*`` of the :class:`window`. Its values are as
follows:

.. c:var:: renderer::software

    The renderer would use a software fallback.
.. c:var:: renderer::accelerated

    The renderer would request hardware acceleration.
.. c:var:: renderer::present_vsync

    The renderer would enable vsync if available.
.. c:var:: renderer::target_texture

    The renderer would support rendering to textures.

.. class:: window

    .. member:: static const auto npos

        Defines an undefined position. Equivalent to ``SDL_WINDOWPOS_UNDEFINED``.
    .. member:: static const auto centered

        Defines a centered position. Equivalent to ``SDL_WINDOWPOS_CENTERED``.
    .. type:: enum flags

        Defines the flags that are used for initialisation of the window. These
        are the same as the ``SDL_WINDOW_*`` flags except turned lower case and into
        snake_case.

        .. c:var:: fullscreen

            A fullscreen window.
        .. c:var:: fullscreen_desktop

            A fullscreen window at desktop resolution.
        .. c:var:: opengl

            A window usable with OpenGL.
        .. c:var:: hidden

            A window that is not visible.
        .. c:var:: borderless

            A borderless window.
        .. c:var:: resizable

            A window that can be resized.
        .. c:var:: minimized

            A window that starts out minimised.
        .. c:var:: maximized

            A window that starts out maximised.
        .. c:var:: input_grabbed

            A window that grabs all input focus.
        .. c:var:: highdpi

            A window that supports high-DPI if available.

    .. function:: window(const std::string& title, const SDL_DisplayMode& display, uint32_t f = 0)
                  window(const std::string& title, int width, int height, uint32_t f = 0)

        Creates a window with a title and a display mode or width and height. The :class:`display_mode` is
        used for retrieving the height and the width of the window. Initialisation flags
        could also be specified, but they default to zero. Also creates a hardware
        accelerated renderer to render things into the window.

        If the creation of the renderer fails, or the initialisation of the window fails
        then the error handler is invoked. See |error|.

        **Parameters:**

        - **title**: The title of the window.
        - **width**: The width of the window.
        - **height**: The height of the window.
        - **f**: The flags to initialise the window with.

    .. function:: bool is_open() const noexcept

        Checks if the window is open.
    .. function:: float brightness() const noexcept
                  void brightness(float b)

        Sets or gets the display of the window's brightness. Returns 0.0 for completely dark, and
        1.0 for normal brightness. If retrieval fails, the error handler is invoked. See |error|.
    .. function:: void clear(const colour& c)

        Clears the window with the specified :class:`colour`.
    .. function:: SDL_Window* data() const noexcept

        Returns the underlying pointer to the ``SDL_Window`` structure.

        .. attention::

            Calling ``SDL_DestroyWindow`` on the returned pointer will lead to
            a double delete. Do not do it. Setting it to null will leak memory. Only
            use this function if you know what you're doing.
    .. function:: SDL_Renderer* renderer() const noexcept

        Returns the underlying pointer to the ``SDL_Window`` structure.

        .. attention::

            Calling ``SDL_DestroyRenderer`` on the returned pointer will lead to
            a double delete. Do not do it. Setting it to null will leak memory. Only
            use this function if you know what you're doing.
    .. function:: void close() noexcept

        Closes the window. Doing any further operations on a closed window outside of
        recreation of the window is undefined behaviour.
    .. function:: void display() noexcept

        Displays the rendering to the screen. Note that this function should be called
        last in the batch of draw calls.
