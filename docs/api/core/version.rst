.. default-domain:: cpp
.. highlight:: cpp
.. _gum-core-version:

Version Information
====================

This header provides a way to query the compile time version information (through the use of SDL version macros)
and the runtime version information through a runtime function also provided by SDL. The purpose of this header is
to wrap them up in a nice manner that don't involve a faux constructor.

This file can be included through::

    #include <gum/core/version.hpp>

.. namespace:: sdl

.. class:: compiled_version

    A struct that represents the compile time version information of SDL.
    The interface is purely static, though it can be instantiated to retrieve
    specific parts of the version.

    .. member:: uint8_t major

        Represents the major version of SDL. This is the 1 in 1.2.3
    .. member:: uint8_t minor

        Represents the minor version of SDL. This is the 2 in 1.2.3
    .. member:: uint8_t patch

        Represents the patch level of SDL. This is the 3 in 1.2.3
    .. function:: constexpr compiled_version()

        Default constructor. Initialises the appropriate version
        members with the appropriate macros provided by SDL.
    .. function:: static constexpr unsigned single_number() noexcept

        Returns a single number representation of the current version.
        For example, 1.2.3 is turned into the single number 1203.
    .. function:: static constexpr bool is_at_least(uint8_t mj, uint8_t mi, uint8_t pt = 0) noexcept

        Checks if the compiled version is at least the specified version.

        **Parameters:**

        - **mj**: The major version to compare against.
        - **mi**: The minor version to compare against.
        - **pt**: The patch version to compare against.

.. class:: linked_version

    A struct that represents the runtime version information of SDL.
    The interface requires instantiation but is purely public, similar
    to ``SDL_version``.

    .. member:: uint8_t major

        Represents the major version of SDL. This is the 1 in 1.2.3
    .. member:: uint8_t minor

        Represents the minor version of SDL. This is the 2 in 1.2.3
    .. member:: uint8_t patch

        Represents the patch level of SDL. This is the 3 in 1.2.3
    .. function:: linked_version() noexcept

        Default constructor that initialises the version information
        as if calling ``SDL_GetVersion``.
