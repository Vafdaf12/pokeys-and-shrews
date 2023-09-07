cmake_minimum_required(VERSION 3.10)
project(CmakeTemplateSDL VERSION 0.1.0 LANGUAGES C CXX)

set(NAME_EXE CmakeTemplateSDL)

include(FetchContent)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SDL_STATIC ON)
FetchContent_Declare(SDL2 
    GIT_REPOSITORY https://github.com/libsdl-org/SDL
    GIT_TAG release-2.26.2
)
FetchContent_MakeAvailable(SDL2)


file(GLOB SRCFILES
    src/*.cpp
)
add_executable(${NAME_EXE} ${SRCFILES})
target_include_directories(${NAME_EXE}
    PRIVATE src/
)
target_link_libraries(${NAME_EXE} SDL2-static)
