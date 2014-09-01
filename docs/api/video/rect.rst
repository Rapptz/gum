.. default-domain:: cpp
.. highlight:: cpp
.. namespace:: sdl
.. _gum-video-rect:

Rectangles, Points, and Vectors
=================================

.. |rect| replace:: :class:`rect`
.. |vector| replace:: :class:`vector`

SDL offers ways to create simple rectangles and points. ``gum`` extends this by giving rectangles a more object
oriented API, and extending points to be full basic two-dimensional vector types. Through the |vector| class,
you will be able to interact with the ``gum`` API more fluidly.

These files can be included through::

    // for rect
    #include <gum/video/rect.hpp>

    // for vector
    #include <gum/video/vector.hpp>

.. class:: rect

    :inherits: SDL_Rect

    Extends the basic ``SDL_Rect`` class to have a more object oriented API.
    By taking its address, it can be converted into ``SDL_Rect*``.

    .. member:: int x

        The x coordinate of the rectangle.
    .. member:: int y

        The y coordinate of the rectangle.
    .. member:: int w

        The width of the rectangle.
    .. member:: int h

        The height of the rectangle.
    .. function:: constexpr rect() noexcept

        Creates an empty rectangle (a rectangle at (0, 0) with an area of 0).
    .. function:: constexpr rect(int x, int y, int w, int h) noexcept

        Creates a rectangle based on the information given.
    .. function:: bool intersects(const rect& other) const noexcept

        Checks if one rectangle intersects with the other.
    .. function:: bool empty() const noexcept

        Checks if the area of the rectangle is zero. This function uses
        ``SDL_RectEmpty`` internally.

    .. function:: rect union_with(const rect& other) const noexcept

        Returns the union of two rectangles. The union is computed
        by calling ``SDL_UnionRect``. The union of two rectangles
        is equal to a rectangle that can encompass both rectangles.

.. function:: constexpr bool operator==(const rect& lhs, const rect& rhs)
              constexpr bool operator!=(const rect& lhs, const rect& rhs)

    Checks if two rectangles are equal or not equal.

.. function:: constexpr bool operator<(const rect& lhs, const rect& rhs)
              constexpr bool operator>(const rect& lhs, const rect& rhs)
              constexpr bool operator<=(const rect& lhs, const rect& rhs)
              constexpr bool operator>=(const rect& lhs, const rect& rhs)

    Lexicographically compares two rectangles. Lexicographical comparison
    is done through the ``x`` member first, then ``y``, then ``w``, then ``h``.

.. class:: vector

    :inherits: SDL_Point

    Extends ``SDL_Point`` to have full vector semantics with helper
    functions that aid in vector operations. By taking its address, you can get the original
    ``SDL_Point*``.

    .. function:: constexpr vector() noexcept

        Creates a vector at (0, 0).
    .. function:: constexpr vector(int x, int y) noexcept

        Creates a vector at (x, y).
    .. function:: constexpr int length_squared() const noexcept

        Returns the squared length (or magnitude) of the vector. This
        is retrieved by doing :math:`x^2 + y^2`.
    .. function:: double length() const noexcept

        Returns the length (or magnitude) of the vector. This is the same as :func:`length_squared` except
        passed through the ``sqrt`` function.
    .. function:: constexpr bool is_unit() const noexcept

        Checks if the vector is a unit vector. A unit vector        is a vector whose length is 1.
    .. function:: void normalise()

        Normalises the vector. A vector that is normalised is
        made into a unit vector.
    .. function:: vector normalised() const noexcept

        Returns the normalised vector. This is equivalent to making a copy of the vector and normalising it.
    .. function:: vector& operator+=(const vector& rhs) noexcept
                  vector& operator-=(const vector& rhs) noexcept
                  vector& operator*=(const vector& rhs) noexcept
                  vector& operator/=(const vector& rhs) noexcept

        Implements member-wise mathematical operations. For example, ``a += b`` is equivalent to ``a.x += b.x; a.y += b.y;``.

        The behaviour is undefined if the operation overflows.
    .. function:: vector& operator*=(int scalar) noexcept

        Implements member-wise scalar multiplication with a vector. For example, ``a += 4`` is equivalent to ``a.x *= 4; a.y *= 4;``.

        The behaviour is undefined if the operation overflows.

.. function:: constexpr vector operator+(const vector& lhs, const vector& rhs) noexcept
              constexpr vector operator-(const vector& lhs, const vector& rhs) noexcept
              constexpr vector operator/(const vector& lhs, const vector& rhs) noexcept
              constexpr vector operator*(const vector& lhs, const vector& rhs) noexcept
              constexpr vector operator*(int lhs, const vector& rhs) noexcept
              constexpr vector operator*(const vector& lhs, int rhs) noexcept

    Implements free form member-wise mathematical operations and scalar multiplication with a vector.
.. function:: constexpr bool operator==(const vector& lhs, const vector& rhs) noexcept
              constexpr bool operator!=(const vector& lhs, const vector& rhs) noexcept

    Checks strict equality of two vectors. A vector is considered equal if they
    have the same length and the same (x, y) values.
.. function:: constexpr int dot(const vector& lhs, const vector& rhs) noexcept

    Implements vector dot product for two vectors.
.. function:: constexpr int determinant(const vector& a, const vector& b) noexcept

    Returns the determinant of the two vectors. The equations for this calculation
    are given below.

    .. math::
        :nowrap:

        \begin{align*}
        \text{Matrix Input} & =  \begin{bmatrix} \vec{a}_x & \vec{a}_y \\ \vec{b}_x & \vec{b}_y \end{bmatrix} \\
        \text{Result} & = \vec{a}_x \times \vec{b}_y - \vec{a}_y \times \vec{b}_x
        \end{align*}

.. function:: int distance_squared(const vector& a, const vector& b) noexcept

    Returns the squared distance between the two vectors. Calculated through
    :math:`(\vec{a}_x - \vec{b}_x)^2 + (\vec{a}_y - \vec{b}_y)^2`
.. function:: double distance(const vector& a, const vector& b) noexcept

    Returns the distance between two vectors. Calculated through
    :math:`\sqrt{(\vec{a}_x - \vec{b}_x)^2 + (\vec{a}_y - \vec{b}_y)^2}`
.. function:: double angle_between(const vector& a, const vector& b) noexcept

    Returns the angle between two vectors. The result is in radians. Calculated through the equation below.

    .. math::

        \arccos \left(\frac{\vec{a} \cdot \vec{b}}{\| \vec{a} \| \times \| \vec{b} \|}\right)
.. function:: double direction(const vector& a, const vector& b) noexcept

    Calculates the direction of the vector. The direction is given by the angle it makes
    with a horizontal line. It is calculated with the following equation:

    .. math::

        \arctan \left( \frac{\vec{b}_y - \vec{a}_y}{\vec{b}_x - \vec{a}_x} \right)
