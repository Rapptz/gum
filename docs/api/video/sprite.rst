.. default-domain:: cpp
.. highlight:: cpp
.. namespace:: sdl
.. _gum-video-sprite:

Sprites
=============

.. |error| replace:: :ref:`gum-core-error`
.. |opt| replace:: :ref:`gum-required-libs`

A sprite is a drawable representation of a :class:`texture` with an origin, position, angle, etc. The :class:`sprite`
class allows you to draw a texture (or a portion of it) into the renderer maintained by the :class:`window`. One should
note that :class:`sprite` does not use :class:`surface` and that it maintains a pointer to the :class:`texture`. As a
consequence this means that the :class:`texture` must outlive the :class:`sprite`. If the texture doesn't outlive the
sprite then the behaviour is undefined.

Usage example: ::

    // load a texture
    sdl::texture my_texture("spritesheet.png", win);

    // create a sprite
    sdl::sprite player(my_texture);
    player.subtexture({ 64, 0, 32, 32 }); // draw a 32x32 sprite at location (64, 0)
    player.position(100, 100); // move it to (100, 100);

    // draw it
    win.draw(player);

This file can be included through: ::

    #include <gum/video/sprite.hpp>



.. enum:: class flip : int

    An enumerator is defined for the flipping aspect of a sprite.

    .. enumerator:: none

        Equivalent to ``SDL_FLIP_NONE``.
    .. enumerator:: vertical

        Equivalent to ``SDL_FLIP_VERTICAL``.
    .. enumerator:: horizontal

        Equivalent to ``SDL_FLIP_HORIZONTAL``.
    .. enumerator:: diagonal

        Equivalent to ``SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL``.

.. class:: sprite

    Represents a drawable (portion of a) :class:`texture`.

    .. function:: sprite() noexcept

        The default constructor. No texture is given to the sprite, so drawing this would not draw
        anything.
    .. function:: sprite(const texture& tex)
                  void texture(const texture& tex, bool recalculate = true)

        Creates a sprite with the :class:`texture` provided. The :func:`subtexture` is re-calculated
        when this function is called to fit the entire texture if ``recalculate`` is true. The
        constructor will always recalculate the :func:`subtexture`.

        .. warning::

            The sprite only keeps a pointer to the texture, not a copy. As a result this means that
            the :class:`texture` has to outlive the sprite. So, for example, you can't have a function
            with a local texture and then assign it to the sprite and return the sprite.

    .. function:: sprite(const texture& tex, const rect& area)

        Creates a sprite with the texture being represented by ``tex`` and the ``area`` representing the :func:`subtexture`.
        This is as if calling :func:`texture` and then :func:`subtexture`.

    .. function:: const sdl::texture* texture() const noexcept

        Returns a pointer to the internal texture used.

    .. function:: void subtexture(const rect& area) noexcept
                  rect subtexture() const noexcept

        Retrieves or specifies the subtexture of the sprite. A subtexture is the portion of the texture
        that is going to be rendered.
    .. function:: void position(int x, int y) noexcept
                  void position(const vector& pos) noexcept
                  vector position() const noexcept

        Retrieves or specifies the position of the sprite. The position of the sprite is the location
        of the sprite where it will be drawn in the renderer. The position of (0, 0) is the default position
        and also in the top left instead of the bottom left.
    .. function:: void move(int x, int y) noexcept
                  void move(const vector& pos) noexcept

        Moves a sprite by the given offset. Equivalent to calling: ::

            sprite.position(sprite.position() + pos);

    .. function:: void rotation(double degrees) noexcept
                  double rotation() const noexcept

        Retrieves or specifies the rotation of the sprite in degrees (not radians).  The default
        rotation of a sprite is 0 degrees. If you want to "flip" a sprite, see :func:`flip` instead.
    .. function:: void rotate(double degrees) noexcept

        Rotates a sprite by the given offset in degrees. Equivalent to calling: ::

            sprite.rotation(sprite.rotation() + degrees);

    .. function:: void origin(int x, int y) noexcept
                  void origin(const vector& center) noexcept
                  vector origin() const noexcept

        Retrieves or specifies the origin of the sprite. The origin of the sprite is where all the
        transformations take place. In other words, a sprite is rotated along its own origin. The
        default origin is (0, 0).
    .. function:: void flip(sdl::flip f) noexcept
                  sdl::flip flip() const noexcept

        Retrieves or specifies the flip of the sprite.
    .. function:: void draw(SDL_Renderer* render) const

        Draws the sprite with all the transformations applied to it. Internally, it calls
        :sdl:`RenderCopyEx`. This allows the sprite to meet the requirements of :class:`is_renderer_drawable\<T>`.
