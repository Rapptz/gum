.. _gum-installation-guide:

Installation
=============

``gum`` is header only, and as a result of that installation is incredibly easy. In fact, there is no need to explicitly
install anything. The installation step mainly involves putting the files in the default search paths of the compiler
which would allow you to write ``<include>`` instead of ``"include"`` without having to specify to the compiler where they
are. If you don't want this, you're free to skip the last few sections.


.. _gum-required-libs:

Required Libraries
-----------------------

``gum`` uses certain libraries to get the dependencies needed to have a nicer API. Since sometimes these libraries
are not provided by the user, you can retroactively disable them through the use of preprocessor macros. Make sure to
define these macros before including the file or they won't work.

+------------+------------------+
|  Library   | Macro to disable |
+------------+------------------+
| SDL2       | None. Obviously. |
+------------+------------------+
| SDL2_image | GUM_IMG_DISABLED |
+------------+------------------+

Note that by using these preprocessor macros then certain parts will obviously not work (e.g. .png loading).

Another macro could be provided to disable all external 3rd dependencies, ``GUM_RAW_SDL``.

.. _gum-supported-compilers:

Supported Compilers
--------------------

Due to the C++11 nature of ``gum``, a more modern compiler is needed to compile code that
includes ``gum``. At the moment, the officially supported compilers are:

* GCC 4.8.1 and higher
* Clang 3.3 and higher

If you'd like to know if your compiler supports ``gum``, an extensive list of C++11 features used
are given below:

* ``=default``, ``=delete`` for functions and constructors
* r-value references, ``std::forward``, ``std::move``, etc.
* ``constexpr`` and ``noexcept`` keywords.
* ``std::unique_ptr`` for smart pointer ownership.
* ``decltype`` and ``auto`` for type inference.
* universal initialisation, e.g. ``x = { 1, 2 };`` for non-aggregates.
* ``using`` aliases (also known as 'template typedefs').
* non-static member initialisation. This is the feature allowing you to assign members
  a value without a constructor.
* Setting the underlying type of the enum. e.g. ``enum test : char``.


Of course, the easiest way to see if your compiler supports ``gum`` is to compile a test file yourself and see.

.. _gum-windows-install:

Installation on Windows
------------------------

Installation on windows depends on the compiler being used. On Visual Studio, this step is typically unwarranted since the
way to handle includes is on a per project basis and relatively simple.

On GCC however, the situation is different. Since the search paths for the different MinGW distributions vary wildly,
the only sane and portable way to 'install' the library into the default search paths would be to use the environment
variables recognised by GCC. These environment variables are ``CPATH``, ``CPLUS_INCLUDE_PATH``, and ``C_INCLUDE_PATH``.
The one to choose depends on what you want.

The differences are as follows:

All of them are as if passing ``-I path`` to the compiler.

* ``CPATH`` is used regardless of language.
* ``CPLUS_INCLUDE_PATH`` is used for C++ only, through invokation of ``g++``.
* ``C_INCLUDE_PATH`` is used for C only, through invokation of ``gcc``.

Installation through the GUI involves a few steps. For the following examples, the path
C:\\gum is used as the path containing the headers. Be sure to change it appropriately.

1. Go to 'My Computer' by using WinKey + E.
2. Right click an empty area and go to 'Properties'.
3. Click 'Advanced System Settings'.
4. Click 'Environment Variables'
5. Under 'System Variables' press 'New...'
6. Input the appropriate variable name and for the value input the proper path.
7. Press the 'OK' and 'Apply' buttons.

After that, the 'installation' should be over.

Doing these steps through the command line are as follows::

    $ setx CPATH C:\gum;%CPATH%

Note that the ``setx`` command is only available for Windows Vista and higher.

.. _gum-linux-install:

Installation on Linux or Mac OS
--------------------------------

On Linux and Mac OS, installation is relatively simple. Rather than fiddling around with environment variables,
many compilers (GCC, Clang, etc) tend to have /usr/include and /usr/local/include as the default
include search paths. You can do this as follows (assuming it's installed in ~/gum)::

    $ cd ~/gum
    $ cp -r gum /usr/local/include
