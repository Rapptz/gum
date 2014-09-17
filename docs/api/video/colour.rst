.. default-domain:: cpp
.. highlight:: cpp
.. _gum-video-colour:

Colour
=======

SDL offers an :sdl:`Color` struct that handles RGBA colours. As an extension, ``gum`` offers a slightly improved
version of this struct. By taking its address, it can turn into a regular pointer to :sdl:`Color`. This header also
defines some commonly available colours for use.

This file can be included through::

    #include <gum/video/colour.hpp>

.. namespace:: sdl

.. class:: colour

    :inherits: SDL_Color

    A class that defines colour properties.

    .. member:: uint8_t r

        Specifies the red colour. Should be in the range of 0 to 255.
    .. member:: uint8_t g

        Specifies the green colour. Should be in the range of 0 to 255.
    .. member:: uint8_t b

        Specifies the blue colour. Should be in the range of 0 to 255.
    .. member:: uint8_t a

        Specifies the alpha (transparency) setting. Should be in the range of 0 to 255.
        0 means transparent, 255 means translucent.

    .. function:: colour() noexcept

        The default constructor. Defines the colour black.
    .. function:: colour(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) noexcept

        Constructs a colour from the given RGBA values.

    .. member:: static colour red() noexcept
                static colour green() noexcept
                static colour blue() noexcept
                static colour black() noexcept
                static colour white() noexcept
                static colour transparent() noexcept
                static colour yellow() noexcept
                static colour magenta() noexcept
                static colour cyan() noexcept

        Defines common colours to use.

.. type:: color

    Defines an alias to use :class:`colour` with en_US spelling.
