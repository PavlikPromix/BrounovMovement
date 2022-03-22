# CMakeList.txt : CMake project for BrounovMovement, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project (BrounovMovement)

find_package(SFML 2.5 REQUIRED COMPONENTS network audio graphics window system)

add_executable (main "main.cpp" "Particle.cpp" "Particle.h" "Canvas.cpp" "Canvas.h")


target_link_libraries(main PRIVATE Freetype OpenAL OpenGL Vorbis sfml-graphics sfml-main sfml-system sfml-window)

