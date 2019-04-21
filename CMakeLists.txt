cmake_minimum_required(VERSION 3.13)
project(3DFieldImaging)

# include headers
include_directories(${PROJECT_SOURCE_DIR}/include)

# include sources
file(GLOB_RECURSE INCLUDE_SOURCES include/*.cpp)

# source files
file(GLOB_RECURSE SOURCES src/*.cpp)

add_compile_options(-m64)
add_link_options(-static-libgcc -static-libstdc++)

# global compiler flags
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-g -Wall -Wextra -Wshadow -pedantic -Weffc++)
else()
    add_compile_options(-O2)
endif()

# don't use -Weffc++ and -Werror for include sources
set_source_files_properties(${INCLUDE_SOURCES} PROPERTIES COMPILE_FLAGS -Wno-effc++)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} ${SOURCES} ${INCLUDE_SOURCES})