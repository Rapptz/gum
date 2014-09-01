.. default-domain:: cpp
.. highlight:: cpp
.. namespace:: sdl
.. _gum-video-display-mode:

Window Display Modes
=========================

.. |error| replace:: :ref:`gum-core-error`

SDL offers a way to query the display mode of a display (monitor, etc) that is proper for a :class:`window`. ``gum``
offers a way to wrap this up in a way that doesn't deal with loops or counters.

This file can be included through::

    #include <gum/video/display_mode.hpp>

.. function:: int number_of_video_displays()

    Returns the number of video displays available. Note that for all functions that take
    in a display index, the index should be in the range of 0 to ``number_of_video_displays() - 1``.
    If an error occurs, the error handler is invoked. See |error|.

.. class:: display_mode

    :inherits: SDL_DisplayMode

    A class with a mostly static interface meant to query certain display modes. By taking
    its address, it allows you to get the underlying ``SDL_DisplayMode*`` for use with the
    SDL C API.

    .. member:: uint32_t format

        The pixel format used. A value of 0 is unspecified pixel format.
    .. member:: int w

        The width of the window.
    .. member:: int h

        The height of the window.
    .. member:: int refresh_rate

        The refresh rate (in Hz) of the window. A value of 0 is unspecified refresh rate.
    .. function:: static std::vector<display_mode> available(int index = 0)

        Returns all available and valid display modes for the current display. A display index of 0 is the main display.
        If an error occurs, the error handler is invoked. See |error|.
    .. function:: static display_mode desktop(int index = 0)

        Returns the desktop display mode for the current display as if calling ``SDL_GetDesktopDisplayMode``.
        A display index of 0 is the main display. If an error occurs, the error handler is invoked. See |error|.
    .. function:: static display_mode closest(const display_mode& to, int index = 0)
                  static display_mode closest(int width, int height, int index = 0)

        Returns the closest display mode for the current display to the one desired.
        Instead of a :class:`display_mode`, a width and a height could be used instead.
        If an error occurs, the error handler is invoked. See |error|.


