.. _gum-usage:

Using Gum
=============

``gum`` is a header only library, so its usage is pretty simple. Just plop in the headers and play.
Since there are no dependencies outside of SDL (and some of its external libraries) there isn't much
to discuss in terms of actual usage that could be detailed here. Rather, this section will go over the
layout of the library and its versioning scheme.

.. _gum-include-layout:

Include Layout
-----------------

``gum`` includes the SDL dependencies through the usage of angle brackets, e.g. ``#include <SDL_rect.h>``. In theory,
it is up to the implementation what this means. In practice, this means that the header has to be found either by
specifying it to the compiler, or it's found through the default include paths. Internally, ``gum`` includes its other
components through the same manner.

``gum`` headers can be found in the ``gum`` subdirectory. Since ``gum`` is split into 'modules', there will be some
subdirectories that you'd need to access to get to the meat of the library. The modules provided by ``gum`` are as follows:

- :ref:`gum-core`
- :ref:`gum-video`

Each module also contains a master file that includes the entire contents of the module. Some examples below.

.. code-block:: cpp

    // includes all of 'core' module
    #include <gum/core.hpp>

    // includes just the 'color' struct of the 'video' module
    #include <gum/video/color.hpp>

    // includes just 'init' of the 'core' module
    #include <gum/core/init.hpp>

All the headers and structs can be found in the API reference section.

.. _gum-namespace:

Namespace
-----------

``gum`` uses the ``sdl`` namespace. There are a few subnamespaces such as ``sdl::renderer`` and ``sdl::mouse``.

.. _gum-versioning:

Versioning
-----------

``gum`` uses `Semantic Versioning 2.0 <http://semver.org/spec/v2.0.0.html>`_ as its versioning scheme.
The only caveat is that prior to ``gum`` version 1.0.0, the API is entirely unstable and considered in development.
