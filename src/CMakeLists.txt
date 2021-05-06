include_directories(${CMAKE_CURRENT_SOURCE_DIR})

find_package(Curses REQUIRED)

include_directories(${CURSES_INCLUDE_DIR})

set(CMAKE_CXX_FLAGS "-g")

add_executable(rogue ${SRC_FILES} main.cpp)
target_link_libraries(rogue ${CURSES_LIBRARIES})

add_subdirectory(application)
add_subdirectory(rogue)