cmake_minimum_required(VERSION 3.17)
project(OCR_S3 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(character_detection)
include_directories(spell_checker)
include_directories(NeuralNetwork)
include_directories(image_preprocessing)
include_directories(type)
include_directories(useful)
include_directories(ui)

if(UNIX AND NOT APPLE)
    INCLUDE(FindPkgConfig)

    PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
    PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
    PKG_SEARCH_MODULE(GTK3 REQUIRED gtk+-3.0)

    INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${GTK3_INCLUDE_DIRS})

    link_directories(${GTK3_LIBRARY_DIRS})
endif()

if (APPLE)
    INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
    find_package (pkgconfig)
    pkg_check_modules (GTK3 REQUIRED gtk+-3.0)
    include_directories (${gtk3_include_dirs})
    link_directories (${GTK3_LIBRARY_DIRS})
    add_definitions (${gtk3_cflags_other})
endif()

file(GLOB src_type src/type/*.c)
file(GLOB src_seg src/character_detection/*.c)
file(GLOB src_image src/image_preprocessing/*.c)
file(GLOB src_useful src/useful/*.c)
file(GLOB src_ui src/ui/*.c)
file(GLOB src_spell src/spell_checker/*.c)
file(GLOB src_neural src/NeuralNetwork/*.c)

add_executable(OCR_S3 src/main.c ${src_type} ${src_seg} ${src_image} ${src_useful} ${src_ui} ${src_spell} ${src_neural})

TARGET_LINK_LIBRARIES(OCR_S3 ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${GTK3_LIBRARIES} -lm ${LIBS})
