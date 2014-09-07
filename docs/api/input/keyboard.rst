.. default-domain:: cpp
.. highlight:: cpp
.. namespace:: sdl
.. _gum-input-keyboard:

Keyboard Support
==================

SDL provides a powerful keyboard input mechanism that is better left untouched. ``gum`` merely provides convenience wrappers
around it with a few renames for consistency and idiomatic approach.

This file can be included through::

    #include <gum/input/keyboard.hpp>

More information about keyboard handling can be found through
`the SDL documentation <https://wiki.libsdl.org/CategoryKeyboard>`_.

.. toctree::
    :maxdepth: 2

    keyboard_renames

The interface for ``gum``'s keyboard support is separated throughout 3 separate subnamespaces.

- ``sdl::key`` for regular virtual keyboard related things, see :sdl:`Keycode`.
- ``sdl::modifier`` for modifier key related things, see :sdl:`Keymod`.
- ``sdl::scan`` for regular physical keyboard related things, see :sdl:`Scancode`.

Some things aren't under a subnamespace. They provide functions related to on-screen keyboards and
text input.

.. function:: bool has_screen_keyboard() noexcept

    Checks if the platform has screen keyboard support. Calls :sdl:`HasScreenKeyboardSupport`.
.. function:: void start_text_input() noexcept

    Starts the receiving of input of Unicode text. Calls :sdl:`StartTextInput`.
.. function:: void stop_text_input() noexcept

    Stops the receiving of input of Unicode text. Calls :sdl:`StopTextInput`.
.. function:: bool is_text_input_active() noexcept

    Checks if text input is active (i.e. if :func:`start_text_input` was called). Calls :sdl:`IsTextInputActive`.
.. function:: void text_input_rect(SDL_Rect rect) noexcept

    Sets the rectangle that enables text input. Calls :sdl:`SetTextInputRect`.

    .. note::

        Although the signature specifies ``SDL_Rect``, the use of :class:`rect` is also allowed.

.. for some reason, the substitutions aren't working. I put them in manually.

.. _gum-input-keyboard-virtual:

Virtual Keyboard
--------------------

.. function:: int32_t key::from_string(const std::string& str) noexcept

    Returns a :ref:`key <gum-input-keyboard-keycodes>` from a human readable string representation.
    See :sdl:`Scancode` for a list of human readable strings.
.. function:: int32_t key::from_scan(uint32_t scan_code) noexcept

    Returns a :ref:`key <gum-input-keyboard-keycodes>` from a :ref:`scan code <gum-input-keyboard-scancodes>`.
.. function:: std::string key::to_string(int32_t key_code) noexcept

    Returns a human readable string representation of a :ref:`key <gum-input-keyboard-keycodes>`.
    See :sdl:`Scancode` for a list of human readable strings.
.. function:: bool key::is_pressed(int32_t key_code) noexcept

    Checks if the :ref:`key <gum-input-keyboard-keycodes>` has been pressed.
    Before processing, it is converted into a :ref:`scan code <gum-input-keyboard-scancodes>` and passed
    into the array returned from :sdl:`GetKeyboardState`.
.. _gum-input-keyboard-physical:

Physical Keyboard
-----------------------

.. function:: int32_t scan::from_string(const std::string& str) noexcept

    Returns a :ref:`scan code <gum-input-keyboard-scancodes>` from a human readable string representation.
    See :sdl:`Scancode` for a list of human readable strings.
.. function:: int32_t scan::from_key(int32_t key_code) noexcept

    Returns a :ref:`scan code <gum-input-keyboard-scancodes>` from a :ref:`key <gum-input-keyboard-keycodes>`.
.. function:: std::string scan::to_string(uint32_t scan_code) noexcept

    Returns a human readable string representation of a :ref:`key <gum-input-keyboard-keycodes>`.
    See :sdl:`Scancode` for a list of human readable strings.
.. function:: bool scan::is_pressed(uint32_t scan_code) noexcept

    Checks if the :ref:`scan code <gum-input-keyboard-scancodes>` has been pressed.

.. _gum-input-keyboard-mod:

Modifier Keys
-------------------

.. function:: bool is_pressed(uint32_t mod_key) noexcept

    Checks if a :ref:`modifier key <gum-input-keyboard-modifiers>` has been pressed.
