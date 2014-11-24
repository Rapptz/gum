.. default-domain:: cpp
.. highlight:: cpp
.. namespace:: sdl
.. _gum-video-texture:

Textures
===========

.. |error| replace:: :ref:`gum-core-error`
.. |opt| replace:: :ref:`gum-required-libs`

SDL2 offers an :sdl:`Texture` struct that can be used to create a pixel representation of an image that
is loaded into VRAM. It also offers :sdl:`Surface` which is similar, but loaded into RAM instead. A big issue with
:sdl:`Texture` is that is requires an :sdl:`Renderer`, which in turn needs an ``SDL_Window``. This leads to a really
tightly coupled system where you need to pass around the window (or renderer) to create a texture which eventually
ends up being rendered on the screen.

There are a few ways to fix this issue, with the most prominent one being using an old-style :sdl:`Surface` and then
turn it into a texture through the use of :sdl:`CreateTextureFromSurface`. However, that function still requires the
renderer to be passed around for creation.

To fix this issue, ``gum`` separates both :sdl:`Surface` and :sdl:`Texture` into two different classes, :class:`texture`
and :class:`surface` which have their own member functions that are similar to the API provided by SDL2. However, instead of
directly using a :class:`surface` as a middle man, member functions are provided to help alleviate the usage of :sdl:`surface`
to its specialised domain such as :func:`texture::load_file`.

.. note::

    All member functions that take in a ``Window`` template parameter can actually take either a
    :class:`window` or an ``SDL_Renderer*`` that can be received through :func:`window::renderer`.

This file can be included through::

    #include <gum/video/texture.hpp>

.. class:: texture

    Represents pixels in a driver specific representation. Encapsulates an :sdl:`Texture`.

    .. function:: texture() noexcept

        Creates an empty texture.
    .. function:: texture(int width, int height, const Window& win, int access = SDL_TEXTUREACCESS_STATIC)
                  void create(int width, int height, const Window& win, int access = SDL_TEXTUREACCESS_STATIC)

        Creates a texture with the dimensions of ``width`` and ``height`` with a static texture access
        using :sdl:`CreateTexture`. Note that it is created using ``SDL_PIXELFORMAT_RGBA8888`` and there is currently
        no way to change this. If an error occurs, the error handler is called. See |error| for more information.
    .. function:: texture(const std::string& filename, const Window& win)
                  void load_file(const std::string& filename, const Window& win)

        Creates an :sdl:`Surface` given by the file provided at filename. At the moment the file types supported are the ones
        supported by SDL2_image. They are:  ICO(Icon)/CUR(Cursor)/BMP, PNM (PPM/PGM/PBM), XPM,
        LBM(IFF ILBM), PCX, GIF, JPEG, PNG, TGA, TIFF, and XV. Note that TIFF support is disabled
        by default (see :func:`init`). If ``GUM_IMG_DISABLED`` is defined then only BMP is supported.
        See |opt| for more information.

        This surface is then transformed into a texture through the use of :sdl:`CreateTextureFromSurface`. If the image
        could not be loaded or the surface cannot be transformed into a texture then the error handler is called.
        See |error| for more information.
    .. function:: SDL_Texture* data() const noexcept

        Returns a pointer to the internal :sdl:`Texture`.

        .. attention::

            Calling :sdl:`DestroyTexture` on the returned pointer will lead to
            a double delete. Do not do it. Setting it to null will leak memory. Only
            use this function if you know what you're doing (i.e. need SDL interop).

    .. function:: explicit operator bool() const noexcept

        Checks if the texture is valid, i.e. the internal texture is not ``nullptr``. This
        should rarely be called in practice since the error handler is called when one of the
        functions creating a texture returns ``nullptr``.

    .. function:: sdl::colour colour() const
                  void colour(const sdl::colour& c)

        Retrieves or specifies the colour modifier of the texture. The colour modifier is multiplied
        into the standard colours of the pixels when drawing takes place. See :sdl:`SetTextureColorMod`
        and :sdl:`SetTextureAlphaMod`.

        If an error occurs, the error handler is called. See |error| for more information.
