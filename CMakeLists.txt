cmake_minimum_required(VERSION 3.10)
project(PokeysAndShrews VERSION 0.1.0 LANGUAGES C CXX)

set(NAME_EXE PokeysAndShrews)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

# Export compile_commands.json for clangd support
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Tells all dependencies to compile statically
set(BUILD_SHARED_LIBS OFF)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the supplied example games


FetchContent_Declare(raylib 
    GIT_REPOSITORY https://github.com/raysan5/raylib
    GIT_TAG 4.5.0
)
FetchContent_Declare(tweeny
    GIT_REPOSITORY https://github.com/mobius3/tweeny
    GIT_TAG v3
)
FetchContent_MakeAvailable(raylib tweeny)

file(GLOB SRCFILES
    src/*.cpp
    src/**/*.cpp
)

# Add executable
add_executable(${NAME_EXE} ${SRCFILES} ${RESFILES})
target_include_directories(${NAME_EXE}
    PRIVATE src/
)
target_link_libraries(${NAME_EXE} raylib tweeny)

# Copy resource files to build directory
add_custom_command(
        TARGET ${NAME_EXE} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_SOURCE_DIR}/res
                ${CMAKE_CURRENT_BINARY_DIR}/res)