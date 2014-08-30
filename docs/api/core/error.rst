.. default-domain:: cpp
.. highlight:: cpp
.. _sdlpp-core-error:

Error Handling
=================

SDL offers basic error handling through ``SDL_GetError`` which is fine, but is not typically the idiomatic way of
doing error handling in C++. When an error occurs in C++, the error is thrown as exception and the user is responsible
for handling the error.

This header defines the exception object that is thrown by different classes in SDL++ along with some other
functions that retrieve the error string and clears it for you.

This file can be included through::

    #include <sdlpp/core/error.hpp>

.. namespace:: sdl

.. class:: error

    :inherits: std::runtime_error

    Defines the exception object that is thrown when an error occurs on the SDL side.

    .. function:: error()

        An exception with ``SDL_GetError`` as the string.
        Calls ``SDL_ClearError`` to clean up the error afterwards.
    .. function:: error(const std::string& str)

        An exception with a custom string.
    .. function:: const char* what() const noexcept

        Returns the error string.


.. function:: std::string last_error() noexcept

    Returns the result of ``SDL_GetError``. This function calls
    ``SDL_ClearError`` right afterwards.
