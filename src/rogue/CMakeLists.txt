add_subdirectory(camera)
add_subdirectory(direction)
add_subdirectory(dungeon)
add_subdirectory(objects)
add_subdirectory(vision)

target_sources(rogue PRIVATE rogue_game.cpp)