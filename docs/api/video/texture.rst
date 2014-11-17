.. default-domain:: cpp
.. highlight:: cpp
.. namespace:: sdl
.. _gum-video-texture:

Textures
===========

.. |error| replace:: :ref:`gum-core-error`

SDL2 offers an :sdl:`Texture` struct that can be used to create a pixel representation of an image that
is loaded into VRAM. It also offers :sdl:`Surface` which is similar, but loaded into RAM instead. A big issue with
:sdl:`Texture` is that is requires an :sdl:`Renderer`, which in turn needs an ``SDL_Window``. This leads to a really
tightly coupled system where you need to pass around the window (or renderer) to create a texture which eventually
ends up being rendered on the screen.

There are a few ways to fix this issue, with the most prominent one being using an old-style :sdl:`Surface` and then
turn it into a texture through the use of :sdl:`CreateTextureFromSurface`. However, that function still requires the
renderer to be passed around for creation.

To fix this issue, ``gum`` uses the concept of :class:`texture` to refer either a regular software accelerated
:sdl:`Surface` or the hardware accelerated :sdl:`Texture`. The user is then responsible to enable hardware acceleration
through the :func:`texture::hardware_accelerate` member function. Please note that not enabling hardware acceleration
will prove to be difficult. The :class:`window` class expects drawables to conform to the hardware accelerated API.
No internal support for :sdl:`Surface` is given.

This file can be included through::

    #include <gum/video/texture.hpp>

.. class:: texture

    Encapsulates an :sdl:`Surface` or :sdl:`Texture`.

    .. function:: texture() noexcept

        Creates an empty texture.
    .. function:: texture(const std::string& filename)
                  void load_file(const std::string& filename)

        Creates a surface through the filename. At the moment, the only image types supported are BMP.

        If the image could not be loaded, the error handler is called. See |error|. If it is loaded,
        this ends in :func:`is_surface` to return ``true``.
    .. function:: texture(texture&& other) noexcept
                  texture& operator=(texture&& other) noexcept

        Move constructs or assigns a texture. Note that :class:`texture` is a move only type and cannot be copied.
    .. function:: bool is_surface() const noexcept

        Returns ``true`` if the :class:`texture` currently contains a non-null :sdl:`Surface`.
    .. function:: bool is_texture() const noexcept

        Returns ``true`` if the :class:`texture` currently contains a non-null :sdl:`Texture`.
    .. function:: SDL_Texture* data() const noexcept
                  SDL_Surface* surface() const noexcept

        Returns the underlying pointer to the :sdl:`Texture` or :sdl:`Surface` structure.
        Note that you must first check if the :class:`texture` is either a texture or a surface.
        Accessing :func:`data` if :func:`surface` is true, for example, will lead to undefined behaviour.

        .. attention::

            Calling :sdl:`DestroyTexture` or :sdl:`DestroySurface` on the returned pointer will lead to
            a double delete. Do not do it. Setting either to null will leak memory. Only
            use this function if you know what you're doing.

    .. function:: void hardware_accelerate(const Window& window)

        Turns a software accelerated :sdl:`Surface` into a hardware accelerated :sdl:`Texture`.
        After this function is called, :func:`is_texture` will return ``true``, and
        :func:`is_surface` will return ``false``. This function does nothing if :func:`is_surface` is
        false.

        .. note::

            Calling this function is necessary if you plan on using drawable classes that
            meet the requirement of :class:`is_renderer_drawable\<T>`. This doesn't apply
            to drawables that are hardware accelerated shapes such as :class:`rectangle`,
            :class:`point`, etc.

    .. function:: void clear() noexcept

        Releases the :sdl:`Texture` or :sdl:`Surface` being managed.
    .. function:: explicit operator bool() const noexcept

        Checks if an :sdl:`Texture` or :sdl:`Surface` is being managed, and if so,
        checks if it is currently not null.
