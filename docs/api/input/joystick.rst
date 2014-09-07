.. default-domain:: cpp
.. highlight:: cpp
.. _gum-input-joystick:

Joystick Support
===================

.. |error| replace:: :ref:`gum-core-error`

SDL provides nice support for joysticks. ``gum`` wraps this up to use RAII to ease the use of :sdl:`Joystick`.
It also wraps up :sdl:`Joystick` in a more object oriented interface.

This file can be included through::

    #include <gum/input/joystick.hpp>

.. namespace:: sdl

Some renames have been provided for consistency.

+---------------------+-----------------------+
| Gum type            | Original SDL name     |
+---------------------+-----------------------+
| joystick_id         | SDL_JoystickID        |
+---------------------+-----------------------+
| joystick_guid       | SDL_JoystickGUID      |
+---------------------+-----------------------+
| hat\:\:centered     | SDL_HAT_CENTERED      |
+---------------------+-----------------------+
| hat\:\:up           | SDL_HAT_UP            |
+---------------------+-----------------------+
| hat\:\:right        | SDL_HAT_RIGHT         |
+---------------------+-----------------------+
| hat\:\:down         | SDL_HAT_DOWN          |
+---------------------+-----------------------+
| hat\:\:left         | SDL_HAT_LEFT          |
+---------------------+-----------------------+
| hat\:\:right_up     | SDL_HAT_RIGHTUP       |
+---------------------+-----------------------+
| hat\:\:right_down   | SDL_HAT_RIGHTDOWN     |
+---------------------+-----------------------+
| hat\:\:left_up      | SDL_HAT_LEFTUP        |
+---------------------+-----------------------+
| hat\:\:left_down    | SDL_HAT_LEFTDOWN      |
+---------------------+-----------------------+


.. function:: int number_of_joysticks()

    Returns the number of attached joysticks. If an error occurs (i.e. :sdl:`NumJoysticks` returns a negative number) then
    the error handler is called. See |error|.
.. function:: std::string joystick_name_at(int index) noexcept

    Returns the name of the joystick at the specified index. If no name is found, an empty string is returned.

.. class:: joystick

    A wrapper around `SDL_Joystick <https://wiki.libsdl.org/CategoryJoystick>`_.

    .. function:: joystick() noexcept

        Creates an uninitialised/unattached joystick. All operations except :func:`joystick::is_attached`
        will lead to errors.
    .. function:: joystick(int index = 0)

        Creates an initialised joystick from an index specified. The index should be less than the number returned
        from :func:`number_of_joysticks`. If initialisation fails, the error handler is called. See |error|.
    .. function:: bool is_attached() const noexcept

        Checks if the joystick is attached.
    .. function:: int16_t axis(int index) const

        Returns the position of the axis provided. Modern joysticks, 0 is the X axis and 1 is the Y axis.
        The value returned represents the position of the axis. The index should be less than the value
        returned by :func:`joystick::axes`. If an error happens, the error handler is called. See |error|.
    .. function:: bool is_pressed(int button) const noexcept

        Checks if a button is currently pressed. The button index should be less than the value returned by
        :func:`joystick::buttons`.
    .. function:: std::string name() const noexcept

        Returns the name of the joystick. If the name cannot be found, returns an empty string.
    .. function:: int axes() const

        Returns the number of axes available by the joystick. If an error occurs, the error handler is called.
        See |error|.
    .. function:: int buttons() const

        Returns the number of buttons available by the joystick. If an error occurs, the error handler is called.
        See |error|.
    .. function:: int hats() const

        Returns the number of hats available by the joystick. More information about what a hat is can be found
        `here <http://en.wikipedia.org/wiki/Joystick#Hat_switch>`_. If an error occurs, the error handler is called.
        See |error|.
    .. function:: uint8_t hat_status(int index = 0) const noexcept

        Returns the status of the hat at the specified index. The value should be less than the value returned by
        :func:`joystick::hats`. The value returned is one of the directions specified :ref:`above <gum-input-joystick>`.
    .. function:: joystick_guid guid() const

        Returns a unique identifier to the joystick. If an error occurs, a zero GUID is returned.
    .. function:: joystick_id id() const

        Returns the instance ID to the joystick. If an error occurs, the error handler is called. See |error|.
    .. function:: SDL_Joystick* data() const noexcept

        Returns a pointer to the underlying ``SDL_Joystick`` structure.

        .. attention::

            Calling :sdl:`JoystickClose` on the returned pointer will lead to
            a double delete. Do not do it. Setting it to null will leak memory. Only
            use this function if you know what you're doing.

