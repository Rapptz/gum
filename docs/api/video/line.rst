.. default-domain:: cpp
.. highlight:: cpp
.. namespace:: sdl
.. _gum-video-line:

Drawable Lines
=================

A line with a begin point and an end point.

This file can be included through::

    #include <gum/video/line.hpp>

.. class:: line

    Represents a line that can be rendered to the screen.

    .. function:: line() noexcept

        Createa a line with a begin and end point of (0, 0).
    .. function:: line(int x1, int y1, int x2, int y2) noexcept
                  line(const vector& one, const vector& two) noexcept

        Creates a line with the specified begin and end points. Note that using a negative value
        would result in undefined behaviour.
    .. function:: void first_point(int x, int y) noexcept
                  void first_point(const vector& v) noexcept
                  vector first_point() const noexcept

        Retrieves or specifies the begin point of the line. Note that using a negative value
        would result in undefined behaviour.
    .. function:: void second_point(int x, int y) noexcept
                  void second_point(const vector& v) noexcept
                  vector second_point() const noexcept

        Retrieves or specifies the end point of the line. Note that using a negative value
        would result in undefined behaviour.
    .. function:: void fill(colour c) noexcept
                  colour fill() const noexcept

        Retrieves of specifies the colour to fill the line with. Default colour is white.
    .. function:: void draw(SDL_Renderer* render)

        Draws the line using a hardware accelerated renderer. This allows
        the line to meet the requirements of :class:`is_renderer_drawable\<T>`.

