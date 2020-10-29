# Define the project name
project(ocr)

cmake_minimum_required(VERSION 3.5.1)

# Add SDL2 CMake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

# Add all c source files under the src directory
set(SRCS
    character_detection/char_detect.c
	image_system/color_system.c
	image_system/image_manipulation.c
	image_system/image_system.c
	useful/builtin.c
	main.c
	demo.c
    )
    
# Fichier headers
set(HEADERS
	character_detection/char_detect.h
	image_system/color_system.h
	image_system/image_manipulation.h
	image_system/image_system.h
	useful/builtin.h
	demo.h
    )
	
add_executable(${PROJECT_NAME} ${SRCS} ${HEADERS})



# Add SDL2 library
find_package(SDL2 REQUIRED)
target_link_libraries(${PROJECT_NAME} SDL2::Main)
