include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(CURSES_NEED_WIDE TRUE)
find_package(Curses REQUIRED)

include_directories(${CURSES_INCLUDE_DIR})

add_executable(rogue main.cpp)
target_link_libraries(rogue ${CURSES_LIBRARIES})

add_subdirectory(application)
add_subdirectory(rogue)