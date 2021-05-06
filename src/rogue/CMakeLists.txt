add_subdirectory(camera)
add_subdirectory(dungeon)
add_subdirectory(maze)
add_subdirectory(objects)
add_subdirectory(vision)

target_sources(rogue PRIVATE rogue_game.cpp)