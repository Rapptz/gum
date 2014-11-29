.. default-domain:: cpp
.. highlight:: cpp
.. _gum-video-message-box:

Message Boxes
====================

.. |error| replace:: :ref:`gum-core-error`

SDL2 offers a simple cross platform way of creating message boxes. A message box is a modal dialog that pops up to the
user prompting for something or notifying them or something. A big issue with the modal dialogs provided by SDL is that it
seems that the flags specified for different styles are ignored in all operating systems except iOS and OS X (as of 2014).
As a result, the ``gum`` API moves over the flag argument to be the penultimate one.

While there are ways to construct a more elaborate message box with :class:`message_box`, most of the use cases are available
in more simple alternatives through :func:`message_box::simple` and :func:`message_box::confirmation`. So constructing an
instance of a message box is unnecessary.

Due to their design, message boxes are meant to be possible to call before any call for :sdl:`Init` so they are a perfect
candidate for error reporting. It might even be used as the error handler. As a consequence, the error handler is also
never called through these APIs, instead a boolean condition or a constant is returned. See |error| for more information.

This file is included through: ::

    #include <gum/video/message_box.hpp>

.. namespace:: sdl

.. class:: message_box

    Represents a more sophisticated message box.

    .. enum:: anonymous

        An anonymous enum that represents the message box flags, i.e. :sdl:`MessageBoxFlags`.

        .. enumerator:: error

            Equivalent to ``SDL_MESSAGEBOX_ERROR``.
        .. enumerator:: warning

            Equivalent to ``SDL_MESSAGEBOX_WARNING``.
        .. enumerator:: info

            Equivalent to ``SDL_MESSAGEBOX_INFORMATION``.

    .. enum:: colour

        An enum that represents the index of the :sdl:`MessageBoxColorScheme` used in the
        :func:`colour` member function's first parameter, i.e. :sdl:`MessageBoxColorType`.

        .. enumerator:: background

            The index to the background colour.
        .. enumerator:: text

            The index to the text colour.
        .. enumerator:: button_border

            The index to the button border colour.
        .. enumerator:: button_background

            The index to the button background colour.
        .. enumerator:: button_selected

            The index to the colour when the button is selected.

    .. enum:: class button

        An enum that represents the standard buttons used in the :func:`message_box::confirmation` member
        function.

        .. enumerator:: invalid

            Returned when an error occurs.
        .. enumerator:: no

            Represents the "No" button being pressed.
        .. enumerator:: yes

            Represents the "Yes" button being pressed.
        .. enumerator:: cancel

            Represents the "Cancel" button being pressed.

    .. function:: void colour(uint32_t index, SDL_MessageBoxColor colour)

        Edits the colour scheme of the specified index (given through the :enum:`colour` enum) with
        the colour provided. Note that :sdl:`MessageBoxColor` has no alpha component, just RGB.
    .. function:: void add_button(int id, const std::string& text, uint32_t flag = 0)

        Adds a button to the message box with the specified id and the text. Flags can also be specified
        of type :sdl:`MessageBoxFlags` or the :enum:`anonymous` enum. The ID is used as a return value for
        :func:`show`.
    .. function:: int show()

        Shows the message box and returns the ID of the button pressed if available. If an error occurs,
        returns -1 instead of calling the error handler.
    .. function:: void window(SDL_Window* win)

        Specifies the parent window of the message box, if available.
    .. function:: void flags(uint32_t flag)

        Specifies the flags of the message box (see :sdl:`MessageBoxFlags` or :enum:`anonymous`).
    .. function:: void title(const std::string& str)

        Specifies the title of the message box.
    .. function:: void message(const std::string& str)

        Specifies the message body of the message box.
    .. function:: static bool simple(const std::string& title, const std::string& message, uint32_t flag = info, SDL_Window* window = nullptr)

        Shows a simple message box with a title, message and an OK button. Calls :sdl:`ShowSimpleMessageBox` internally.
        Returns ``true`` if no error occurred, ``false`` otherwise.

        :param flag: The flag to create the message box with.
        :param window: The parent window of the message box, if available.
    .. function:: static button confirmation(const std::string& title, const std::string& message, SDL_Window* window = nullptr)

        Shows a simple message box with a title, message, and buttons shown in the :enum:`button` enum. Returns
        the button pressed through the :enum:`button` enum.


