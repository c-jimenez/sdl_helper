
# Examples
add_executable(example_sdl example_sdl.cpp)
target_link_libraries(example_sdl sdl)

add_executable(example_widgets example_widgets.cpp)
target_link_libraries(example_widgets game)
