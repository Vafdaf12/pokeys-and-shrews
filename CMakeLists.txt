cmake_minimum_required(VERSION 3.10)
project(PokeysAndShrews VERSION 0.1.0 LANGUAGES C CXX)

set(NAME_EXE PokeysAndShrews)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

# Export compile_commands.json for clangd support
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Tells all dependencies to compile statically
set(BUILD_SHARED_LIBS OFF)

# SDL2 Configuration
set(SDL2_MAIN_LIBRARY SDL2)
set(SDL2_DISABLE_INSTALL ON)
set(SDL2IMAGE_INSTALL OFF)

FetchContent_Declare(SDL2 
    GIT_REPOSITORY https://github.com/libsdl-org/SDL
    GIT_TAG release-2.26.2
)
FetchContent_MakeAvailable(SDL2)

FetchContent_Declare(SDL2_image
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_image
    GIT_TAG release-2.6.3
)
FetchContent_MakeAvailable(SDL2_image)

file(GLOB SRCFILES
    src/*.cpp
    src/**/*.cpp
)

# Add executable
add_executable(${NAME_EXE} ${SRCFILES} ${RESFILES})
target_include_directories(${NAME_EXE}
    PRIVATE src/
)
target_link_libraries(${NAME_EXE} SDL2-static SDL2_image)

# Copy resource files to build directory
add_custom_command(
        TARGET ${NAME_EXE} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_SOURCE_DIR}/res
                ${CMAKE_CURRENT_BINARY_DIR}/res)