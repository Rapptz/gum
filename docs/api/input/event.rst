.. default-domain:: cpp
.. highlight:: cpp
.. namespace:: sdl
.. _gum-input-event:

Event Handling
==================

SDL provides a powerful event mechanism that is better left untouched. ``gum`` merely provides convenience wrappers
around it with a few renames for consistency and idiomatic approach.

This file can be included through::

    #include <gum/input/event.hpp>


.. _gum-input-event-structures:

Renamed Event Structures
---------------------------

The following SDL structures have been renamed using a ``using`` statement:

+---------------------------+-------------------------+
| Original SDL Type         |  Gum Type               |
+---------------------------+-------------------------+
| SDL_ControllerAxisEvent   | controller_axis_event   |
+---------------------------+-------------------------+
| SDL_ControllerButtonEvent | controller_button_event |
+---------------------------+-------------------------+
| SDL_ControllerDeviceEvent | controller_device_event |
+---------------------------+-------------------------+
| SDL_DollarGestureEvent    | dollar_gesture_event    |
+---------------------------+-------------------------+
| SDL_DropEvent             | drop_event              |
+---------------------------+-------------------------+
| SDL_Finger                | finger                  |
+---------------------------+-------------------------+
| SDL_JoyAxisEvent          | joy_axis_event          |
+---------------------------+-------------------------+
| SDL_JoyBallEvent          | joy_ball_event          |
+---------------------------+-------------------------+
| SDL_JoyButtonEvent        | joy_button_event        |
+---------------------------+-------------------------+
| SDL_JoyDeviceEvent        | joy_device_event        |
+---------------------------+-------------------------+
| SDL_JoyHatEvent           | joy_hat_event           |
+---------------------------+-------------------------+
| SDL_KeyboardEvent         | keyboard_event          |
+---------------------------+-------------------------+
| SDL_MouseButtonEvent      | mouse_button_event      |
+---------------------------+-------------------------+
| SDL_MouseMotionEvent      | mouse_motion_event      |
+---------------------------+-------------------------+
| SDL_MouseWheelEvent       | mouse_wheel_event       |
+---------------------------+-------------------------+
| SDL_MultiGestureEvent     | multi_gesture_event     |
+---------------------------+-------------------------+
| SDL_QuitEvent             | quit_event              |
+---------------------------+-------------------------+
| SDL_SysWMEvent            | syswm_event             |
+---------------------------+-------------------------+
| SDL_TextEditingEvent      | text_editing_event      |
+---------------------------+-------------------------+
| SDL_TextInputEvent        | text_input_event        |
+---------------------------+-------------------------+
| SDL_TouchFingerEvent      | touch_finger_event      |
+---------------------------+-------------------------+
| SDL_UserEvent             | user_event              |
+---------------------------+-------------------------+
| SDL_WindowEvent           | window_event            |
+---------------------------+-------------------------+

.. _gum-input-window-events:

Window Events
----------------

The following window events have been renamed.

+-------------------------------+---------------------------------+
| Original SDL_WINDOWEVENT      |  Gum equivalent                 |
+-------------------------------+---------------------------------+
| SDL_WINDOWEVENT_SHOWN         | window_event_id\:\:shown        |
+-------------------------------+---------------------------------+
| SDL_WINDOWEVENT_HIDDEN        | window_event_id\:\:hidden       |
+-------------------------------+---------------------------------+
| SDL_WINDOWEVENT_EXPOSED       | window_event_id\:\:exposed      |
+-------------------------------+---------------------------------+
| SDL_WINDOWEVENT_MOVED         | window_event_id\:\:moved        |
+-------------------------------+---------------------------------+
| SDL_WINDOWEVENT_RESIZED       | window_event_id\:\:resized      |
+-------------------------------+---------------------------------+
| SDL_WINDOWEVENT_SIZE_CHANGED  | window_event_id\:\:size_changed |
+-------------------------------+---------------------------------+
| SDL_WINDOWEVENT_MINIMIZED     | window_event_id\:\:minimised    |
+-------------------------------+---------------------------------+
| SDL_WINDOWEVENT_MAXIMIZED     | window_event_id\:\:maximised    |
+-------------------------------+---------------------------------+
| SDL_WINDOWEVENT_RESTORED      | window_event_id\:\:restored     |
+-------------------------------+---------------------------------+
| SDL_WINDOWEVENT_ENTER         | window_event_id\:\:enter        |
+-------------------------------+---------------------------------+
| SDL_WINDOWEVENT_LEAVE         | window_event_id\:\:leave        |
+-------------------------------+---------------------------------+
| SDL_WINDOWEVENT_FOCUS_GAINED  | window_event_id\:\:focus_gained |
+-------------------------------+---------------------------------+
| SDL_WINDOWEVENT_FOCUS_LOST    | window_event_id\:\:focus_lost   |
+-------------------------------+---------------------------------+
| SDL_WINDOWEVENT_CLOSE         | window_event_id\:\:close        |
+-------------------------------+---------------------------------+

.. _gum-input-regular-events:

Events
-----------

The following events have also been renamed.

+-------------------------------+-------------------------------------+
| Original Event                |  Gum equivalent                     |
+-------------------------------+-------------------------------------+
| SDL_FIRSTEVENT                | events\:\:first_event               |
+-------------------------------+-------------------------------------+
| SDL_QUIT                      | events\:\:quit                      |
+-------------------------------+-------------------------------------+
| SDL_APP_TERMINATING           | events\:\:app_terminating           |
+-------------------------------+-------------------------------------+
| SDL_APP_LOWMEMORY             | events\:\:app_low_memory            |
+-------------------------------+-------------------------------------+
| SDL_APP_WILLENTERBACKGROUND   | events\:\:app_will_enter_background |
+-------------------------------+-------------------------------------+
| SDL_APP_DIDENTERBACKGROUND    | events\:\:app_did_enter_background  |
+-------------------------------+-------------------------------------+
| SDL_APP_WILLENTERFOREGROUND   | events\:\:app_will_enter_foreground |
+-------------------------------+-------------------------------------+
| SDL_APP_DIDENTERFOREGROUND    | events\:\:app_did_enter_foreground  |
+-------------------------------+-------------------------------------+
| SDL_WINDOWEVENT               | events\:\:window                    |
+-------------------------------+-------------------------------------+
| SDL_SYSWMEVENT                | events\:\:syswm                     |
+-------------------------------+-------------------------------------+
| SDL_KEYDOWN                   | events\:\:key_down                  |
+-------------------------------+-------------------------------------+
| SDL_KEYUP                     | events\:\:key_up                    |
+-------------------------------+-------------------------------------+
| SDL_TEXTEDITING               | events\:\:text_editing              |
+-------------------------------+-------------------------------------+
| SDL_TEXTINPUT                 | events\:\:text_input                |
+-------------------------------+-------------------------------------+
| SDL_MOUSEMOTION               | events\:\:mouse_motion              |
+-------------------------------+-------------------------------------+
| SDL_MOUSEBUTTONDOWN           | events\:\:mouse_button_down         |
+-------------------------------+-------------------------------------+
| SDL_MOUSEBUTTONUP             | events\:\:mouse_button_up           |
+-------------------------------+-------------------------------------+
| SDL_MOUSEWHEEL                | events\:\:mouse_wheel               |
+-------------------------------+-------------------------------------+
| SDL_JOYAXISMOTION             | events\:\:joy_axis_motion           |
+-------------------------------+-------------------------------------+
| SDL_JOYBALLMOTION             | events\:\:joy_ball_motion           |
+-------------------------------+-------------------------------------+
| SDL_JOYHATMOTION              | events\:\:joy_hat_motion            |
+-------------------------------+-------------------------------------+
| SDL_JOYBUTTONDOWN             | events\:\:joy_button_down           |
+-------------------------------+-------------------------------------+
| SDL_JOYBUTTONUP               | events\:\:joy_button_up             |
+-------------------------------+-------------------------------------+
| SDL_JOYDEVICEADDED            | events\:\:joy_device_added          |
+-------------------------------+-------------------------------------+
| SDL_JOYDEVICEREMOVED          | events\:\:joy_device_removed        |
+-------------------------------+-------------------------------------+
| SDL_CONTROLLERAXISMOTION      | events\:\:controller_axis_motion    |
+-------------------------------+-------------------------------------+
| SDL_CONTROLLERBUTTONDOWN      | events\:\:controller_button_down    |
+-------------------------------+-------------------------------------+
| SDL_CONTROLLERBUTTONUP        | events\:\:controller_button_up      |
+-------------------------------+-------------------------------------+
| SDL_CONTROLLERDEVICEADDED     | events\:\:controller_device_added   |
+-------------------------------+-------------------------------------+
| SDL_CONTROLLERDEVICEREMOVED   | events\:\:controller_device_removed |
+-------------------------------+-------------------------------------+
| SDL_CONTROLLERDEVICEREMAPPED  | events\:\:controller_device_remapped|
+-------------------------------+-------------------------------------+
| SDL_FINGERDOWN                | events\:\:finger_down               |
+-------------------------------+-------------------------------------+
| SDL_FINGERUP                  | events\:\:finger_up                 |
+-------------------------------+-------------------------------------+
| SDL_FINGERMOTION              | events\:\:finger_motion             |
+-------------------------------+-------------------------------------+
| SDL_DOLLARGESTURE             | events\:\:dollar_gesture            |
+-------------------------------+-------------------------------------+
| SDL_DOLLARRECORD              | events\:\:dollar_record             |
+-------------------------------+-------------------------------------+
| SDL_MULTIGESTURE              | events\:\:multi_gesture             |
+-------------------------------+-------------------------------------+
| SDL_CLIPBOARDUPDATE           | events\:\:clipboard_update          |
+-------------------------------+-------------------------------------+
| SDL_DROPFILE                  | events\:\:drop_file                 |
+-------------------------------+-------------------------------------+
| SDL_RENDER_TARGETS_RESET      | events\:\:render_targets_reset      |
+-------------------------------+-------------------------------------+
| SDL_USEREVENT                 | events\:\:user                      |
+-------------------------------+-------------------------------------+
| SDL_LASTEVENT                 | events\:\:last                      |
+-------------------------------+-------------------------------------+


As an extension, :sdl:`Event` is aliased to ``sdl::event``. Along with that, some
free functions are defined for consistency and idiomatic approach.

.. function:: bool poll_event(event& e) noexcept

    Retrieves an event from the event queue using :sdl:`PollEvent`. Returns ``true`` if there are more events
    on the queue, ``false`` otherwise. This function is non-blocking. If there are no events, it returns
    immediately. If you want blocking behaviour, use :func:`wait_event` or :func:`wait_event_for`.
.. function:: bool wait_event(event& e) noexcept

    Waits indefinitely for an event to be in the wait queue using :sdl:`WaitEvent`. Returns ``true`` if an event
    was received, or ``false`` in case of an error. The user is responsible for checking this error. This function
    is blocking. If you want non-blocking behaviour, use :func:`poll_event`.
.. function:: bool wait_event_for(event& e, int ms) noexcept
              bool wait_event_for(event& e, const std::chrono::duration<Rep, Period>& time) noexcept

    Waits until the specified millisecond time for an event. This function is implemented through
    :sdl:`WaitEventTimeout`. The ``std::chrono`` overload allows you to specify a time duration
    with a different tick and period. For example, ``std::chrono::seconds(1)`` to specify a time
    to wait for 1 second. Behaves similar to :func:`wait_event` otherwise.

Along with the functions above, the following functions are defined under the subnamespace ``sdl::event_queue``. This
clearly shows the intent that the user is operating on SDL's event queue.

.. function:: void clear(uint32_t type, Args) noexcept

    Removes specific events from the queue as if calling :sdl:`FlushEvent` on every
    argument provided. The type must be one of the :ref:`event types <gum-input-regular-events>`.
.. function:: void clear_range(uint32_t min, uint32_t max) noexcept

    Removes a range of events from the queue as if calling :sdl:`FlushEvents`.
.. function:: void pump() noexcept

    Pumps the event queue using :sdl:`PumpEvents`. This is typically not used since
    :func:`event::poll`, :func:`event::wait`, and :func:`event::wait_for` implicitly pump the event queue.
.. function:: bool has(uint32_t type, Args) noexcept

    Checks if the specific events from the queue exist as if calling :sdl:`HasEvent` on every
    argument provided. The type must be one of the :ref:`event types <gum-input-regular-events>`.
    Returns ``true`` if **all** events provided are inside the queue, ``false`` otherwise.
.. function:: void clear_range(uint32_t min, uint32_t max) noexcept

    Checks if a range of events exist in the queue as if calling :sdl:`HasEvents`.

