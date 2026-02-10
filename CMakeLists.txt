cmake_minimum_required(VERSION 3.14)
project(cpp_quest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiler flags
if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Werror)
endif()

# Enable testing
enable_testing()

# Find Catch2
find_package(Catch2 3)

# Add sessions (will be populated incrementally)
file(GLOB SESSION_DIRS "sessions/*")
foreach(SESSION_DIR ${SESSION_DIRS})
    if(IS_DIRECTORY ${SESSION_DIR})
        if(EXISTS "${SESSION_DIR}/CMakeLists.txt")
            add_subdirectory(${SESSION_DIR})
        endif()
    endif()
endforeach()

# Add game_world
add_subdirectory(game_world)
