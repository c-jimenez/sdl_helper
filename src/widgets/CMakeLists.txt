
# Widgets library
add_library(widgets
  animation.cpp
  image.cpp
  label.cpp
  sprite.cpp
  transform.cpp
  widget.cpp
)
target_include_directories(widgets PUBLIC .)
target_link_libraries(widgets
  sdl
)
