.. default-domain:: cpp
.. highlight:: cpp
.. _gum-core-init:

Initialisation
===============

.. |error| replace:: :ref:`gum-core-error`
.. |opt| replace:: :ref:`gum-required-libs`

As many are aware, SDL requires initialisation of its internal subsystems. Mainly, you
initialise the subsystems you need, and then at the end of the program you call :sdl:`Quit`.

This file can be included through::

    #include <gum/core/init.hpp>

.. namespace:: sdl

.. function:: void quit() noexcept

    Calls :sdl:`Quit`. Provided for consistency.

    This also quits the appropriate external libraries if they are enabled. See |opt| for
    more details.
.. function:: void init(uint32_t sdl = SDL_INIT_EVERYTHING, uint32_t img = unspecified)

    Calls the appropriate initialisation initialisation functions with the flags provided.

    The function first initialises SDL using :sdl:`Init` using the flags provided. If
    ``GUM_IMG_DISABLED`` is not defined then SDL2_image is initialised using ``IMG_Init`` with
    the flags specified. It defaults to ``IMG_INIT_PNG | IMG_INIT_JPG``. For more information
    on disabling this, see |opt|.

    After the initialisation steps are over, :func:`quit` is registered for ``std::atexit``, relieving
    the user of calling :func:`quit` at the end.

    If an error occurs, the error handler is called. See |error| for more details.
