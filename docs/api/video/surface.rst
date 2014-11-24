.. default-domain:: cpp
.. highlight:: cpp
.. namespace:: sdl
.. _gum-video-surface:

Surfaces and Images
========================

.. |error| replace:: :ref:`gum-core-error`
.. |opt| replace:: :ref:`gum-required-libs`

An :sdl:`Surface` is a representation of raw pixel data stored in main memory (i.e. RAM). This is useful if you want to
manipulate images or when you don't want to load an image in VRAM. ``gum`` wraps this abstraction into one that more
closely fits the object oriented paradigm.

This file can be included through::

    #include <gum/video/surface.hpp>

.. class:: surface

    Represents a collection of pixels in RAM.


    .. member:: static constexpr uint32_t red
                static constexpr uint32_t green
                static constexpr uint32_t blue
                static constexpr uint32_t alpha

        The RGBA mask used throughout the creation of surfaces. The value depends on whether
        the system is big endian or little endian.
    .. function:: surface()

        Default constructor. Equivalent to calling :func:`create` with ``create(1, 1, 32)``.
    .. function:: surface(int width, int height, int depth = 32)
                  void create(int width, int height, int depth = 32)

        Creates an RGBA surface using :sdl:`CreateRGBSurface`. Essentially this function creates
        an array of pixels with a length of ``width * height``. If an error occurs, the error handler
        is called. See |error| for more info.
    .. function:: surface(const std::string& filename)
                  void load_file(const std::string& filename)

        Creates a surface given by the image located at filename. At the moment the file types supported are the ones
        supported by SDL2_image. They are:  ICO(Icon)/CUR(Cursor)/BMP, PNM (PPM/PGM/PBM), XPM,
        LBM(IFF ILBM), PCX, GIF, JPEG, PNG, TGA, TIFF, and XV. Note that TIFF support is disabled
        by default. If ``GUM_IMG_DISABLED`` is defined then only BMP is supported.
        See |opt| for more information.

        If the image could not be loaded, the error handler is called. See |error| for more information.
    .. function:: SDL_Surface* data() const noexcept

        Returns a pointer to the internal :sdl:`Surface`.

        .. attention::

            Calling :sdl:`FreeSurface` on the returned pointer will lead to
            a double delete. Do not do it. Setting it to null will leak memory. Only
            use this function if you know what you're doing (i.e. need SDL interop).

    .. function:: explicit operator bool() const noexcept

        Checks if the surface is valid, i.e. the internal surface is not ``nullptr``. This
        should rarely be called in practice since the error handler is called when one of the
        functions creating a surface returns ``nullptr``.
    .. function:: rect clip() const noexcept
                  bool clip(const rect& area) noexcept

        Retrieves or specifies the clipping rectangle of the surface. The clipping rectangle
        is the area that is rendered when drawn. When specifying the clipping rectangle
        a boolean is returned indicating if the clipping rectangle intersects with the surface.
    .. function:: sdl::colour colour() const
                  void colour(const sdl::colour& c)

        Retrieves or specifies the colour modifier of the surface. The colour modifier is multiplied
        into the standard colours of the pixels when drawing takes place. See :sdl:`SetSurfaceColorMod`
        and :sdl:`SetSurfaceAlphaMod`.

        If an error occurs, the error handler is called. See |error| for more information.
    .. function:: SDL_Point size() const noexcept

        Returns the size of the surface. The ``x`` value represents the width of the surface, while the
        ``y`` value represents the height of the surface.
    .. function:: int length() const noexcept

        Returns the length of the array returned by :func:`pixels`.
    .. function:: bool must_lock() const noexcept

        Checks if locking is required to modify the pixels returned through :func:`pixels`.
    .. function:: void lock()

        Locks the surface to allow modifying of the pixel data. If an error occurs, then the
        error handler is called. See |error| for more information.
    .. function:: void unlock() noexcept

        Unlocks the surface, dictating that modifying of the pixel data has ended.
    .. function:: uint32_t* pixels() const noexcept

        Returns a contiguous array that contains the pixel data. To modify this data, locking
        might be necessary through the use of :func:`lock`. You can check if it's required through
        the use of :func:`must_lock`.

        An example is given below: ::

            sdl::surface surf("test.png");
            uint32_t* pixels = surf.pixels();
            for(int i = 0; i < surf.length(); ++i) {
                std::cout << "Pixel at " << i << " has colour #" << std::hex << pixels[i] << '\n';
            }
