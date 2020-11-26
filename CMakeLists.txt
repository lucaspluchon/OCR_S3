cmake_minimum_required(VERSION 3.17)
project(OCR_S3 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(character_detection)
include_directories(image_system)
include_directories(NeuralNetworks)
include_directories(type)
include_directories(useful)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

add_executable(Main
        character_detection/char_detect.c
        character_detection/char_detect.h
        image_system/color_system.c
        image_system/color_system.h
        image_system/image_manipulation.c
        image_system/image_manipulation.h
        image_system/image_system.c
        image_system/image_system.h
        NeuralNetworks/BackPropagation.c
        NeuralNetworks/BackPropagation.h
        NeuralNetworks/BuiltinsNeuralNetworks.c
        NeuralNetworks/BuiltinsNeuralNetworks.h
        NeuralNetworks/DemoNeuralNetwork.c
        NeuralNetworks/DemoNeuralNetwork.h
        NeuralNetworks/FileManagment.c
        NeuralNetworks/FileManagment.h
        NeuralNetworks/NeuralNetwork.c
        NeuralNetworks/NeuralNetwork.h
        type/pixel.h
        useful/builtin.c
        useful/builtin.h
        useless/demo.c
        useless/demo.h
        main.c)

add_executable(Neural_Test
        character_detection/char_detect.c
        character_detection/char_detect.h
        image_system/color_system.c
        image_system/color_system.h
        image_system/image_manipulation.c
        image_system/image_manipulation.h
        image_system/image_system.c
        image_system/image_system.h
        NeuralNetworks/BackPropagation.c
        NeuralNetworks/BackPropagation.h
        NeuralNetworks/BuiltinsNeuralNetworks.c
        NeuralNetworks/BuiltinsNeuralNetworks.h
        NeuralNetworks/DemoNeuralNetwork.c
        NeuralNetworks/DemoNeuralNetwork.h
        NeuralNetworks/FileManagment.c
        NeuralNetworks/FileManagment.h
        NeuralNetworks/NeuralNetwork.c
        NeuralNetworks/NeuralNetwork.h
        type/pixel.h
        useful/builtin.c
        useful/builtin.h
        neural_main.c)

add_executable(GTK_Test
        character_detection/char_detect.c
        character_detection/char_detect.h
        image_system/color_system.c
        image_system/color_system.h
        image_system/image_manipulation.c
        image_system/image_manipulation.h
        image_system/image_system.c
        image_system/image_system.h
        type/pixel.h
        useful/builtin.c
        useful/builtin.h
        gtk_main.c)

target_link_libraries(Neural_Test ${SDL2_LIBRARIES})
target_link_libraries(Neural_Test -lm ${LIBS})

target_link_libraries(GTK_Test ${SDL2_LIBRARIES})
target_link_libraries(GTK_Test -lm ${LIBS})

target_link_libraries(Main ${SDL2_LIBRARIES})
target_link_libraries(Main -lm ${LIBS})