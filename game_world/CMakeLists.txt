cmake_minimum_required(VERSION 3.15)

# Auto-discover available sessions
set(AVAILABLE_SESSIONS "")
set(SESSION_DEFINES "")

# Check which session directories exist
foreach(SESSION_NUM RANGE 1 13)
    # Format session number with leading zero
    if(SESSION_NUM LESS 10)
        set(SESSION_DIR "0${SESSION_NUM}")
    else()
        set(SESSION_DIR "${SESSION_NUM}")
    endif()
    
    # Check if session directory exists
    file(GLOB SESSION_PATH "${CMAKE_SOURCE_DIR}/sessions/${SESSION_DIR}_*")
    
    if(SESSION_PATH)
        list(APPEND AVAILABLE_SESSIONS ${SESSION_NUM})
        list(APPEND SESSION_DEFINES "SESSION_${SESSION_DIR}_AVAILABLE")
        message(STATUS "Found Session ${SESSION_NUM}: ${SESSION_PATH}")
    endif()
endforeach()

# Allow manual override via environment or CMake variable
if(DEFINED ENV{CPP_QUEST_SESSIONS})
    set(CPP_QUEST_SESSIONS $ENV{CPP_QUEST_SESSIONS})
    message(STATUS "Using sessions from environment: ${CPP_QUEST_SESSIONS}")
elseif(DEFINED CPP_QUEST_SESSIONS)
    message(STATUS "Using sessions from CMake variable: ${CPP_QUEST_SESSIONS}")
endif()

# If manual override, filter available sessions
if(DEFINED CPP_QUEST_SESSIONS)
    set(FILTERED_SESSIONS "")
    set(FILTERED_DEFINES "")
    
    string(REPLACE "," ";" SESSION_LIST ${CPP_QUEST_SESSIONS})
    foreach(SESSION_NUM ${SESSION_LIST})
        if(${SESSION_NUM} IN_LIST AVAILABLE_SESSIONS)
            list(APPEND FILTERED_SESSIONS ${SESSION_NUM})
            
            if(SESSION_NUM LESS 10)
                list(APPEND FILTERED_DEFINES "SESSION_0${SESSION_NUM}_AVAILABLE")
            else()
                list(APPEND FILTERED_DEFINES "SESSION_${SESSION_NUM}_AVAILABLE")
            endif()
        endif()
    endforeach()
    
    set(AVAILABLE_SESSIONS ${FILTERED_SESSIONS})
    set(SESSION_DEFINES ${FILTERED_DEFINES})
endif()

message(STATUS "Game World will integrate sessions: ${AVAILABLE_SESSIONS}")

# Create game_world executable
add_executable(game_world
    main.cpp
    game_engine.cpp
)

# Add session-specific defines
foreach(DEFINE ${SESSION_DEFINES})
    target_compile_definitions(game_world PRIVATE ${DEFINE})
endforeach()

# Set C++ standard
target_compile_features(game_world PRIVATE cxx_std_20)

# Compiler warnings
target_compile_options(game_world PRIVATE
    -Wall -Wextra -Wpedantic
    $<$<CONFIG:Debug>:-g>
    $<$<CONFIG:Release>:-O2>
)

# Include directories
target_include_directories(game_world PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/sessions
)

# Generate session config header
string(REPLACE ";" ", " AVAILABLE_SESSIONS_STR "${AVAILABLE_SESSIONS}")
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/session_config.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/session_config.h
)

target_include_directories(game_world PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

# Count sessions
list(LENGTH AVAILABLE_SESSIONS SESSION_COUNT)
message(STATUS "Game World configured with ${SESSION_COUNT} sessions")
