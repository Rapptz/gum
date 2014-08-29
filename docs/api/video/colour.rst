.. _sdlpp-video-colour:
.. default-domain:: cpp
.. highlight:: cpp

Colour
=======

SDL offers an ``SDL_Color`` struct that handles RGBA colours. As an extension, SDL++ offers a slightly improved
version of this struct. By taking its address, it can turn into a regular ``SDL_Color*``. This header also
defines some commonly available colours for use.

This file can be included through::

    #include <sdlpp/video/colour.hpp>

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

    .. member:: static const colour red
                static const colour green
                static const colour blue
                static const colour black
                static const colour white
                static const colour transparent
                static const colour yellow
                static const colour magenta
                static const colour cyan

        Defines common colours to use.

.. type:: color

    Defines an alias to use :class:`colour` with en_US spelling.
