cmake_minimum_required(VERSION 3.15)
project(Emulator VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Build configuration
if(CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE Release)
endif()

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Compiler flags
if(MSVC)
    add_compile_options(/W4 /permissive-)
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        add_compile_options(/O2 /DNDEBUG)
    endif()
else()
    add_compile_options(-Wall -Wextra -pedantic)
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        add_compile_options(-O3 -DNDEBUG)
    else()
        add_compile_options(-g)
    endif()
endif()

# Find SDL2
find_package(SDL2 REQUIRED)
if(NOT SDL2_FOUND)
    message(FATAL_ERROR "SDL2 not found. Please install SDL2 development libraries.")
endif()

# Use modern SDL2 targets if available
if(TARGET SDL2::SDL2)
    set(SDL2_TARGET SDL2::SDL2)
else()
    # Fallback for older SDL2 installations
    set(SDL2_TARGET ${SDL2_LIBRARIES})
endif()

# JSON library - header-only (nlohmann/json)
include(FetchContent)
FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.2
)
FetchContent_MakeAvailable(json)

# Include directories (for non-modern SDL2)
if(NOT TARGET SDL2::SDL2)
    include_directories(
        ${CMAKE_SOURCE_DIR}/include
        ${SDL2_INCLUDE_DIRS}
    )
endif()

# Source files
set(SOURCES
    src/main.cpp
    src/Emulator.cpp
    src/ConfigManager.cpp
    src/KeyMapper.cpp
    src/APKManager.cpp
    src/UI.cpp
)

# Header files
set(HEADERS
    include/Emulator.h
    include/ConfigManager.h
    include/KeyMapper.h
    include/APKManager.h
    include/UI.h
)

# Create executable (target name: Emulator)
add_executable(Emulator ${SOURCES} ${HEADERS})

# Link libraries
if(TARGET SDL2::SDL2)
    target_link_libraries(Emulator 
        SDL2::SDL2
        SDL2::SDL2main
        nlohmann_json::nlohmann_json
    )
else()
    target_link_libraries(Emulator 
        ${SDL2_LIBRARIES}
        nlohmann_json::nlohmann_json
    )
    target_include_directories(Emulator PRIVATE ${SDL2_INCLUDE_DIRS})
endif()

# Include directories for JSON
target_include_directories(Emulator PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    $<IF:$<BOOL:${json_SOURCE_DIR}>,${json_SOURCE_DIR}/include,>
)

# Copy assets to build directory
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

# Copy DLLs on Windows
if(WIN32)
    # For modern SDL2 targets, get DLL from the target
    if(TARGET SDL2::SDL2)
        # Get the DLL location from SDL2 target
        get_target_property(SDL2_DLL_LOCATION SDL2::SDL2 LOCATION)
        if(SDL2_DLL_LOCATION)
            get_filename_component(SDL2_DLL_DIR ${SDL2_DLL_LOCATION} DIRECTORY)
            find_file(SDL2_DLL 
                NAMES SDL2.dll
                PATHS ${SDL2_DLL_DIR}
                NO_DEFAULT_PATH
            )
            if(SDL2_DLL)
                add_custom_command(TARGET Emulator POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    ${SDL2_DLL} $<TARGET_FILE_DIR:Emulator>
                    COMMENT "Copying SDL2.dll to output directory")
            endif()
        endif()
    endif()
    
    # Fallback: Try to find SDL2 DLL in common locations
    if(NOT SDL2_DLL)
        find_file(SDL2_DLL 
            NAMES SDL2.dll
            PATHS
                ${SDL2_LIBRARY_DIR}
                ${CMAKE_SOURCE_DIR}/lib
                ENV PATH
            PATH_SUFFIXES lib bin
        )
        
        if(SDL2_DLL)
            add_custom_command(TARGET Emulator POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${SDL2_DLL} $<TARGET_FILE_DIR:Emulator>
                COMMENT "Copying SDL2.dll to output directory")
        endif()
    endif()
endif()

# Installation
install(TARGETS Emulator DESTINATION bin)
install(DIRECTORY assets DESTINATION .)
