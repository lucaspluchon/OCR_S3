cmake_minimum_required(VERSION 3.17)
project(OCR_S3 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(character_detection)
include_directories(image_preprocessing)
include_directories(type)
include_directories(useful)
include_directories(ui)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
include_directories(${GTK3_INCLUDE_DIRS})
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
        character_detection/segmentation.c type/data.h type/pixel.c)

target_link_libraries(GTK_Test ${SDL2_LIBRARIES})
TARGET_LINK_LIBRARIES(GTK_Test ${GTK3_LIBRARIES})
target_link_libraries(GTK_Test -lm ${LIBS})
