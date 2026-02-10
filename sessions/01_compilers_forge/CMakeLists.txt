# Session 1: The Compiler's Forge

# Executable for character display
add_executable(character_display
    starter/main.cpp
    starter/display.cpp
)

# Tests
find_package(Catch2 QUIET)

if(Catch2_FOUND)
    add_executable(test_session01
        tests/test_session01.cpp
    )
    target_link_libraries(test_session01 PRIVATE Catch2::Catch2WithMain)
    
    add_test(NAME Session01_Tests COMMAND test_session01)
else()
    message(STATUS "Catch2 not found - tests for Session 1 will be skipped")
    message(STATUS "Install Catch2 to enable automated testing")
endif()
