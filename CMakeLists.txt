cmake_minimum_required(VERSION 3.17)
project(OCR_S3 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(character_detection)
include_directories(image_preprocessing)
include_directories(type)
include_directories(useful)
include_directories(ui)

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(GTK3 REQUIRED gtk+-3.0)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${GTK3_INCLUDE_DIRS})

link_directories(${GTK3_LIBRARY_DIRS})

add_executable(Main
                main.c
                )

add_executable(Neural_Test
                neural_main.c
                )

add_executable(GTK_Test
                character_detection/block.c
                character_detection/char.c
                character_detection/line.c
                character_detection/rlsa.c
                image_preprocessing/binarization.c
                image_preprocessing/convolution.c
                image_preprocessing/grayscale.c
                image_preprocessing/image_tools.c
                image_preprocessing/median.c
                image_preprocessing/pixel_operations.c
                image_preprocessing/preprocessing.c
                image_preprocessing/rotation.c
                ui/ui.c
                useful/builtin.c
                gtk_main.c
        character_detection/segmentation.c type/data.h type/pixel.c character_detection/correction.c character_detection/line_analyser.c)

TARGET_LINK_LIBRARIES(GTK_Test ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${GTK3_LIBRARIES} -lm ${LIBS})