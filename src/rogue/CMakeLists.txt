add_subdirectory(camera)
add_subdirectory(dungeon)
add_subdirectory(maze)
add_subdirectory(objects)

target_sources(rogue PRIVATE rogue_game.cpp)