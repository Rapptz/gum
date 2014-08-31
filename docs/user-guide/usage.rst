.. _sdlpp-usage:

Using SDL++
=============

SDL++ is a header only library, so its usage is pretty simple. Just plop in the headers and play.
Since there are no dependencies outside of SDL (and some of its external libraries) there isn't much
to discuss in terms of actual usage that could be detailed here. Rather, this section will go over the
layout of the library and its versioning scheme.

.. _sdlpp-include-layout:

Include Layout
-----------------

SDL++ includes the SDL dependencies through the usage of angle brackets, e.g. ``#include <SDL_rect.h>``. In theory,
it is up to the implementation what this means. In practice, this means that the header has to be found either by
specifying it to the compiler, or it's found through the default include paths.

Internally, SDL++ includes its other components through the use of quotations, e.g. ``#include "../core/version.hpp"``.
As a consequence of this, the internal directory structure should **not** be touched or messed around with. It will only
cause pain.

SDL++ headers can be found in the ``sdlpp`` subdirectory. Since SDL++ is split into 'modules', there will be some
subdirectories that you'd need to access to get to the meat of the library. The modules provided by SDL++ are as follows:

- :ref:`sdlpp-core`
- :ref:`sdlpp-video`

Each module also contains a master file that includes the entire contents of the module. Some examples below.

.. code-block:: cpp

    // includes all of 'core' module
    #include <sdl++/core.hpp>

    // includes just the 'color' struct of the 'video' module
    #include <sdl++/video/color.hpp>

    // includes just 'init' of the 'core' module
    #include <sdl++/core/init.hpp>

All the headers and structs can be found in the API reference section.

.. _sdlpp-namespace:

Namespace
-----------

SDL++ uses the ``sdl`` namespace for all its structs, functions, etc. There are currently no subnamespaces.

.. _sdlpp-versioning:

Versioning
-----------

SDL++ uses `Semantic Versioning 2.0 <http://semver.org/spec/v2.0.0.html>`_ as its versioning scheme.
The only caveat is that prior to SDL++ version 1.0.0, the API is entirely unstable and considered in development.
