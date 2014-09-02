.. default-domain:: cpp
.. highlight:: cpp
.. _gum-video-traits:

Video Type Traits
===================

In order to interact with the ``gum`` API fluently, type traits with `SFINAE <http://en.wikipedia.org/wiki/SFINAE>`_
is used instead of polymorphism and inheritance. This allows you to just use your regular types without relying on
inheritance to meet an interface requirement. Just implement the interfaces required for the traits to get the
behaviour they rely on.

This file can be included through::

    #include <gum/video/traits.hpp>

.. namespace:: sdl

.. class:: is_renderer_drawable<T>

    This trait specifies if a type can be drawn using an ``SDL_Renderer*``. In order to meet the trait
    requirement, you must provide a member function with the following prototype and name:

    .. code-block:: cpp

        void draw(SDL_Renderer*)

    This allows your type to be called with :func:`window::draw`. Minimal example::

        #include <gum/core.hpp>
        #include <gum/video/window.hpp>

        struct my_drawable {
            void draw(SDL_Renderer* render) {
                SDL_SetRenderDrawColor(render, 0x00, 0x00, 0x00, 0x00);
                SDL_RenderDrawPoint(render, 10, 10);
            }
        };

        int main(int, char**) {
            sdl::init sdl(sdl::init::video);
            sdl::window win("Test", sdl::display_mode::closest(100, 100));
            my_drawable point;
            win.clear();
            win.draw(point);
            win.display();
            sdl::delay(1200);
            return 0;
        }
