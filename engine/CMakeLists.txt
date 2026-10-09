cmake_minimum_required(VERSION 3.15)
project(GameEngine LANGUAGES CXX C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
option(ENABLE_WARNINGS "Enable warning flags" ON)
option(ENABLE_SANITIZERS "Enable ASan and UBSan" OFF)
option(ENABLE_ASSERTIONS "Enable assertions" OFF)

if (ENABLE_SANITIZERS)
    add_library(sanitizer_flags INTERFACE)
    target_compile_options(sanitizer_flags INTERFACE
            $<$<CXX_COMPILER_ID:GNU,Clang>:-fsanitize=address,undefined -fno-omit-frame-pointer>
            $<$<CXX_COMPILER_ID:MSVC>:/fsanitize=address>
    )
    target_link_options(sanitizer_flags INTERFACE
            $<$<CXX_COMPILER_ID:GNU,Clang>:-fsanitize=address,undefined>
            $<$<CXX_COMPILER_ID:MSVC>:/INCREMENTAL:NO>
    )
endif ()

find_program(CCACHE_PROGRAM ccache)
if (CCACHE_PROGRAM)
    set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
endif ()

find_package(OpenGL REQUIRED)

include(cmake/LinkSDL.cmake)
add_subdirectory(thirdparty)
add_subdirectory(src)
