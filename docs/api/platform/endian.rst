.. default-domain:: cpp
.. highlight:: cpp
.. namespace:: sdl

.. _gum-platform-endian:

Byte Order
==============

SDL provides a rich API for byte ordering and swapping in its ``SDL_endian.h`` header. Since it's sufficient
enough it's not explicitly wrapped any further since endian issues are hard to come up except in networking.
Nevertheless, this file provides a type trait for compile-time detection of endianness.

This file can be included through::

    #include <gum/platform/endian.hpp>

.. class:: is_big_endian

    :inherits: `std::integral_constant <http://en.cppreference.com/w/cpp/types/integral_constant>`_

    This trait specifies if the current platform is big endian. So ``::value`` would return ``true`` if
    the platform is big endian, otherwise it'd be ``false``.
