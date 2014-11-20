.. default-domain:: cpp
.. highlight:: cpp
.. _gum-core-error:

Error Handling
=================

SDL offers basic error handling through :sdl:`GetError`. ``gum`` provides a more idiomatic method for error handling. When an error occurs in C++, the error is thrown as an exception and the user is responsible
for handling the error. However, sometimes this isn't needed and sometimes you want to interact with the errors yourself.
``gum`` offers a way to do that through macros.

This header defines the exception object that is thrown by different classes in ``gum`` along with some other
functions that retrieve the error string and clears it for you.

This file can be included through::

    #include <gum/core/error.hpp>

.. namespace:: sdl

.. c:macro:: GUM_NO_EXCEPTIONS

    If this macro is defined, no exceptions are thrown and the error handler
    is set to use :sdl:`Log` instead.
.. c:macro:: GUM_ERROR_HANDLER(result)

    If finer gratuity is needed for error handling, you can define this macro with an
    error handler to use. Note that the macro is called as ``GUM_ERROR_HANDLER(result);`` with
    the trailing semicolon. The result parameter is what the function would return. The return
    value is not guaranteed to be meaningful. ``void`` functions have an empty result parameter.
    The default handler is:

    .. code-block:: cpp

        throw sdl::error()

    However, if :c:macro:`GUM_NO_EXCEPTIONS` is defined, then the handler is changed to:

    .. code-block:: cpp

        do { SDL_Log("%s", SDL_GetError()); SDL_ClearError(); return result; } while(0)

    You should strive to use these as examples of what to do. Note that external libraries
    also use :sdl:`GetError` and :sdl:`SetError` to do their error handling.

    .. warning::

        You should only really use this if you absolutely know what you're doing.

.. class:: error

    :inherits: std::runtime_error

    Defines the exception object that is thrown when an error occurs on the SDL side.

    .. function:: error()

        An exception with :sdl:`GetError` as the string.
        Calls :sdl:`ClearError` to clean up the error afterwards.
    .. function:: error(const std::string& str)

        An exception with a custom string.
    .. function:: const char* what() const noexcept

        Returns the error string.


.. function:: std::string last_error()

    Returns the result of :sdl:`GetError`. This function calls
    :sdl:`ClearError` right afterwards. Note that this works
    even with external libraries used by gum.
