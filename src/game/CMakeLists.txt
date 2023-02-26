
# Game library
add_library(game
  fonts_db.cpp
  sprites_db.cpp
  scene.cpp
)
target_include_directories(game PUBLIC .)
target_link_libraries(game
  widgets
)
