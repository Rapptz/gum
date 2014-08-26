## SDL++

SDL++ is currently a result of me experimenting with SDL. It aims to wrap most of the SDL API in an easy to
use C++11 interface. Note that this wrapper is a very thin wrapper. There should be very little differences in terms of
performance between using the wrapper and the API calls directly. Documentation is an on-going thing, as is the actual
interface.

SDL++ is currently header only. So there's no build step. The only thing needed to build at the moment is just SDL2. Versions
lower than SDL2 are not explicitly supported.

## License

SDL++ is licensed with the zlib license similar to SDL 2.

## TODO

- Add `renderer`
- Add `display_mode`
- Improve `window`
- Image loading
- Wrap SDL_Rect

... and many more.
