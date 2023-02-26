
# SDL library
add_library(sdl
  sdl.cpp
  sdl_font.cpp
  sdl_renderer.cpp
  sdl_surface.cpp
  sdl_texture.cpp
  sdl_window.cpp
)
target_include_directories(sdl PUBLIC .)
