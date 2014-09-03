.. default-domain:: cpp
.. highlight:: cpp
.. _gum-video-point:

Drawable Points
==================

A drawable point that extends ``SDL_Point``. Used for drawing a single pixel in the screen.

This file can be included through::

    #include <gum/video/point.hpp>

.. namespace:: sdl

.. class:: point

    .. member:: int x

        The x position. A negative number results in undefined behaviour.
    .. member:: int y

        The y position. A negative number results in undefined behaviour.
    .. function:: point(int x = 0, int y = 0) noexcept

        Creates a point at position x and y. A negative number results in undefined behaviour.
    .. function:: void fill(colour c) noexcept
                  colour fill() const noexcept

        Retrieves or specifies the colour to use when rendering the point.
    .. function:: void draw(SDL_Renderer* render)

        Draws the point using a hardware accelerated renderer. This allows
        the point to meet the requirements of :class:`is_renderer_drawable\<T>`.
