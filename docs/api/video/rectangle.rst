.. default-domain:: cpp
.. highlight:: cpp
.. namespace:: sdl
.. _gum-video-rectangle:

Drawable Rectangles
======================

A drawable shape that represents a rectangle. This shouldn't be confused with :class:`rect`. Although the two
are similar, :class:`rect` is used to represent a rectangle object while :class:`rectangle` is used to represent a
rectangle that could be drawn to the screen.

This file can be included through::

    #include <gum/video/rectangle.hpp>

.. class:: rectangle

    Encapsulates a rectangle that can be drawn.

    .. function:: rectangle(int width, int height) noexcept
                  rectangle(vector size) noexcept

        Creates a rectangle with the specified width and height. The default
        position is (0, 0). Specifying negative width and height is undefined behaviour.
    .. function:: void position(int x, int y) noexcept
                  void position(const vector& pos) noexcept
                  vector position() const noexcept

        Retrieves or specifies the position to render the rectangle at. If the position
        specified is negative, then 0 is used instead.
    .. function:: void size(int width, int height) noexcept
                  void size(const vector& pos) noexcept
                  vector size() const noexcept

        Retrieves or specifies the size of the rectangle. If the size is negative, an
        empty area of (0, 0) is used instead.
    .. function:: void fill(colour c) noexcept
                  colour fill() const noexcept

        Retrieves or specifies the colour to use for the filling of the rectangle.
        Default colour is white.
    .. function:: void outline(colour c) noexcept
                  colour outline() const noexcept

        Retrieves or specifies the colour to use for the outline of the rectangle.
        Default colour is white.
    .. function:: void draw(SDL_Renderer* renderer)

        Draws using a hardware accelerated renderer. This allows the rectangle to
        meet the requirements of :class:`is_renderer_drawable\<T>`.
