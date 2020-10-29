# Define the project name
project(ocr)

cmake_minimum_required(VERSION 3.5.1)

# Add SDL2 CMake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

# Sources files
set(SRCS
    character_detection/char_detect.c
	image_system/color_system.c
	image_system/image_manipulation.c
	image_system/image_system.c
	NeuralNetworks/BackPropagation.c
	NeuralNetworks/BuiltinsNeuralNetworks.c
	NeuralNetworks/DemoNeuralNetwork.c
	NeuralNetworks/FileManagment.c
	NeuralNetworks/NeuralNetwork.c
	useful/builtin.c
	main.c
	demo.c
    )
    
# Headers files
set(HEADERS
	character_detection/char_detect.h
	image_system/color_system.h
	image_system/image_manipulation.h
	image_system/image_system.h
	NeuralNetworks/BackPropagation.h
	NeuralNetworks/BuiltinsNeuralNetworks.h
	NeuralNetworks/DemoNeuralNetwork.h
	NeuralNetworks/FileManagment.h
	NeuralNetworks/NeuralNetwork.h
	useful/builtin.h
	demo.h
    )
	
# Add SDL2.dll
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Debug)
configure_file(C:/SDL2-VC/lib/x64/SDL2.dll ${CMAKE_CURRENT_SOURCE_DIR}/Debug/SDL2.dll COPYONLY)

add_executable(${PROJECT_NAME} ${SRCS} ${HEADERS})



# Add SDL2 library
find_package(SDL2 REQUIRED)
target_link_libraries(${PROJECT_NAME} SDL2::Main)
