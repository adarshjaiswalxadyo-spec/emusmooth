cmake_minimum_required(VERSION 3.15)

project(Emulator
    VERSION 1.0.0
    LANGUAGES CXX
)

# --------------------------------------------------
# C++ Standard
# --------------------------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --------------------------------------------------
# Default build type
# --------------------------------------------------
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# --------------------------------------------------
# Output directories
# --------------------------------------------------
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# --------------------------------------------------
# Compiler flags
# --------------------------------------------------
if(MSVC)
    add_compile_options(/W4 /permissive-)
    add_compile_options(/O2 /DNDEBUG)
else()
    add_compile_options(-Wall -Wextra -pedantic)
    add_compile_options(-O3 -DNDEBUG)
endif()

# --------------------------------------------------
# SDL2 (NO SDL2main)
# --------------------------------------------------
find_package(SDL2 REQUIRED)

# IMPORTANT: Disable SDL_main
if(WIN32)
    add_compile_definitions(SDL_MAIN_HANDLED)
endif()

# --------------------------------------------------
# nlohmann/json (header-only)
# --------------------------------------------------
include(FetchContent)
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.2
)
FetchContent_MakeAvailable(nlohmann_json)

# --------------------------------------------------
# Source files
# --------------------------------------------------
file(GLOB SRC_FILES src/*.cpp)
file(GLOB HEADER_FILES include/*.h)

# --------------------------------------------------
# Executable
# --------------------------------------------------
add_executable(Emulator
    ${SRC_FILES}
    ${HEADER_FILES}
)

# --------------------------------------------------
# Include directories
# --------------------------------------------------
target_include_directories(Emulator PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

# --------------------------------------------------
# Link libraries (FIXED)
# --------------------------------------------------
target_link_libraries(Emulator PRIVATE
    SDL2::SDL2
    nlohmann_json::nlohmann_json
)

# --------------------------------------------------
# Assets (safe if empty)
# --------------------------------------------------
if(EXISTS "${CMAKE_SOURCE_DIR}/assets")
    file(COPY "${CMAKE_SOURCE_DIR}/assets"
         DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
endif()

# --------------------------------------------------
# Copy SDL2.dll (Windows)
# --------------------------------------------------
if(WIN32)
    find_file(SDL2_DLL
        NAMES SDL2.dll
        PATHS
            ENV PATH
            C:/msys64/mingw64/bin
    )

    if(SDL2_DLL)
        add_custom_command(TARGET Emulator POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${SDL2_DLL}
            $<TARGET_FILE_DIR:Emulator>
            COMMENT "Copying SDL2.dll"
        )
    endif()
endif()

# --------------------------------------------------
# Install
# --------------------------------------------------
install(TARGETS Emulator DESTINATION bin)

if(EXISTS "${CMAKE_SOURCE_DIR}/assets")
    install(DIRECTORY assets DESTINATION .)
endif()



