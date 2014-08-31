.. default-domain:: cpp
.. highlight:: cpp

.. _gum-core:

Gum Core
=============

The ``gum`` core module defines things that allow you to query core things about SDL. These
include things such as the version, errors, and initialisation of SDL.

Certain functions are available only if the master file is included::

    #include <gum/core.hpp>

.. function:: void delay(unsigned ms)

    Delays the program for the specified millisecond time. This function uses
    ``SDL_Delay`` internally so it shares the same pros and cons.


Contents:

.. toctree::
    :maxdepth: 1

    core/init
    core/error
    core/version

