Overview
=========

``gum`` is currently a result of me experimenting with SDL. It aims to wrap most of the SDL API in an easy to
use C++11 interface. Note that this wrapper is a very thin wrapper. There should be very little differences in terms of
performance between using the wrapper and the API calls directly. Documentation is an on-going thing, as is the actual
interface.

``gum`` is currently header only. So there's no build step. The only thing needed to build at the moment is just SDL2 and
possibly some external libraries. See :ref:`gum-required-libs` for more info. Versions lower than SDL2 are not supported.

Users of the library are encouraged to read the user guide for questions they might have.

Contents:

.. toctree::
   :maxdepth: 3

   User Guide    <user-guide/index>
   API Reference <api/index>


Indices and tables
==================

* :ref:`genindex`
* :ref:`search`

