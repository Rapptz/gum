.. default-domain:: cpp
.. highlight:: cpp
.. _gum-core-init:

Initialisation
===============

.. |init| replace:: :class:`init`
.. |error| replace:: :ref:`gum-core-error`

As many are aware, SDL requires initialisation of its internal subsystems. Mainly, you
initialise the subsystems you need, and then at the end of the program you call :sdl:`Quit`.
``gum`` provides a RAII wrapper for SDL initialisation in the form of the |init| class.

It also defines all the ``SDL_INIT_*`` flags through a nested enum in the class to be more 'C++-like'.
Just like :sdl:`Init`, it should only be called once.

.. warning::

    Since this is a class and not a function an unnamed object such as
    ``sdl::init(sdl::init::audio)`` will quit the subsystem immediately.
    Instead, ``sdl::init x(sdl::init::audio)`` or similar should be used.

This file can be included through::

    #include <gum/core/init.hpp>

.. namespace:: sdl

.. function:: void quit() noexcept

    Calls :sdl:`Quit`. Provided for consistency.

.. class:: init

    .. type:: enum flags

        Flags that specify what subsystem to initialise.
        Just like the regular ``SDL_INIT_*`` flags, these can
        be OR'd together to initialise multiple subsystems.

        .. c:var:: timer

            Initialises the timer subsystem.
        .. c:var:: audio

            Initialises the audio subsystem.
        .. c:var:: video

            Initialises the video subsystem.
        .. c:var:: joystick

            Initialises the joystick subsystem.
        .. c:var:: haptic

            Initialises the force feedback subsystem.
        .. c:var:: game_controller

            Initialises the game controller subsystem.
        .. c:var:: events

            Initialises the events subsystem.
        .. c:var:: everything

            Initialises every subsystem.

    .. function:: init(const init&)
                  init(init&&)
                  init& operator=(const init&)
                  init& operator=(init&&)

        These functions are deleted as |init| is a non-movable and
        non-copyable type.
    .. function:: init(uint32_t subsystems = flags::video)

        Initialises SDL with the flags given. By default,
        it just initialises the video subsystem though you
        should specify whichever you want.

        If :sdl:`Init` returns a value less than zero, the error handler is invoked.
        See |error|.
    .. function:: ~init()

        Calls :sdl:`Quit` to quit all the initialised subsystems.
    .. function:: void quit() noexcept
                  void quit(uint32_t subsystem) noexcept

        Quits a specified subsystem. If no subsystem is specified, it quits all subsystems.
        The subsystem should be one of the initialisation enum values.
    .. function:: void start(uint32_t subsystem) const

        Initialises a subsystem by the given flag.

        If :sdl:`InitSubSystem` returns a value less than zero, the error handler is invoked.
        See |error|.
    .. function:: bool was_initialised(uint32_t subsystem = flags::video) const noexcept

        Checks if a subsystem is initialised. Delegates the work over to :sdl:`WasInit`.
