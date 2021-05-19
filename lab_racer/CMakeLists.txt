cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
project(lab_racer CXX)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_COMPILER /usr/local/opt/llvm/bin/clang++)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -fopenmp")
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${pjbullethell_SOURCE_DIR}/cmake")


INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

include_directories(${SDL2_INCLUDE_DIRS}  ${SDL2IMAGE_INCLUDE_DIRS})
include_directories("${PROJECT_SOURCE_DIR}/src")
include_directories("/usr/local/include" "/usr/local/opt/llvm/include")
link_directories("/usr/local/lib" "/usr/local/opt/llvm/lib")

file(GLOB_RECURSE lab_2_SOURCES "src/*.cpp")

add_executable(lab_racer ${lab_2_SOURCES} src/utils/general.h src/utils/my_math.h src/utils/MyText.h src/utils/MyText.cpp)
target_link_libraries(lab_racer ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} SDL2_ttf)

add_custom_command(TARGET lab_racer PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/data $<TARGET_FILE_DIR:lab_racer>/data)
