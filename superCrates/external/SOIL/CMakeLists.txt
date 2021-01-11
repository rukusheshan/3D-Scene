cmake_minimum_required(VERSION 3.6)
project(SOIL)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Release)

set(SOURCE_FILES
    src/image_DXT.c
    src/image_DXT.h
    src/image_helper.c
    src/image_helper.h
    src/SOIL.c
    src/SOIL.h
    src/stb_image_aug.c
    src/stb_image_aug.h
    src/stbi_DDS_aug.h
    src/stbi_DDS_aug_c.h
    src/test_SOIL.cpp)


add_library(SOIL ${SOURCE_FILES})

target_link_libraries(SOIL m opengl32 gdi32
        )