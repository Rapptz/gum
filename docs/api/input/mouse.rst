.. default-domain:: cpp
.. highlight:: cpp
.. _gum-input-mouse:

Mouse Support
================

SDL offers rudementary mouse support. ``gum`` extends this to be a little more easy to use. Not many facilities
are currently available, such as creation of a cursor and setting the cursor state. These will be added soon.

Things in this header are defined in the ``sdl::mouse`` subnamespace.

This file can be included through::

    #include <gum/input/mouse.hpp>

.. namespace:: sdl

.. type:: enum class mouse::button

    Represents buttons on the mouse.

    .. c:var:: left

        Represents the left mouse button.
    .. c:var:: middle

        Represents the middle mouse button.
    .. c:var:: right

        Represents the right mouse button.
    .. c:var:: x1

        Represents the first extra mouse button.
    .. c:var:: x2

        Represents the second extra mouse button.

.. function:: bool mouse::is_button_pressed(mouse::button b) noexcept

    Checks if the button specified is currently being pressed. Note that this does not
    query the global mouse state, but rather the state of the focus window. You can grab
    the focus of the mouse with :func:`window::grab_input`.
.. function:: vector position() noexcept

    Returns the position of the mouse relative to the focused window. You can grab
    the focus of the mouse with :func:`window::grab_input`. As a caveat, this returns
    (0, 0) after the initial call if events haven't been pumped using ``SDL_PumpEvent``.
    This will be fixed in the future.
