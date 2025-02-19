cmake_minimum_required(VERSION 3.5.0)
project(ParticleSystem VERSION 0.1.0 LANGUAGES C CXX)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

add_executable(ParticleSystem main.cpp particle.cpp particleManager.cpp)

target_link_libraries(ParticleSystem sfml-system sfml-window sfml-graphics sfml-network sfml-audio)

include(CTest myMath.h)
enable_testing()

