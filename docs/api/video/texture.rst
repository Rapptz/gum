.. default-domain:: cpp
.. highlight:: cpp
.. _gum-video-texture:

Textures
===========

.. |error| replace:: :ref:`gum-core-error`

SDL2 offers an ``SDL_Texture`` struct that can be used to create a hardware accelerated texture. A big issue with
this struct is that is requires an ``SDL_Renderer``, which in turn needs an ``SDL_Window``. This leads to a really
tightly coupled system where you need to pass around the window (or renderer) to create a texture which eventually
ends up being rendered on the screen.

There are a few ways to fix this issue, with the most prominent one being using an old-style ``SDL_Surface`` and then
turn it into a texture through the use of ``SDL_CreateTextureFromSurface``. However, that function still requires the
renderer to be passed around for creation.

To fix this issue, ``gum`` uses the concept of :class:`texture` to refer either a regular software accelerated
``SDL_Surface`` or ``SDL_Texture``. The user is then responsible to enable hardware acceleration through the
:class:`window`.

This file can be included through::

    #include <gum/video/texture.hpp>

.. namespace:: sdl

.. class:: texture

    Encapsulates an ``SDL_Surface`` or ``SDL_Texture``.

    .. function:: texture() noexcept

        Creates an empty texture.
    .. function:: texture(const std::string& filename)
    .. function:: void load_file(const std::string& filename)

        Creates a surface through the filename. At the moment, the only image types supported are BMP.

        If the image could not be loaded, the error handler is called. See |error|. If it is loaded,
        this ends in :function:`is_surface` to return ``true``.
    .. function:: bool is_surface() const noexcept

        Returns ``true`` if the :class:`texture` currently contains a non-null ``SDL_Surface``.
    .. function:: bool is_texture() const noexcept

        Returns ``true`` if the :class:`texture` currently contains a non-null ``SDL_Texture``.
    .. function:: SDL_Texture* data() const noexcept
                  SDL_Surface* surface() const noexcept

        Returns the underlying pointer to the ``SDL_Texture`` or ``SDL_Surface`` structure.

        .. attention::

            Calling ``SDL_DestroyTexture`` or ``SDL_DestroySurface`` on the returned pointer will lead to
            a double delete. Do not do it. Setting either to null will leak memory. Only
            use this function if you know what you're doing.
