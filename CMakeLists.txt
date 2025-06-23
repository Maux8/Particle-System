cmake_minimum_required(VERSION 3.5.0)
project(ParticleSystem VERSION 0.1.0 LANGUAGES C CXX)

find_package(SFML 2.6 COMPONENTS system window graphics network audio REQUIRED)

include_directories(Header)
file(GLOB SOURCES "SourceFiles/*.cpp")

add_executable(ParticleSystem ${SOURCES})

target_link_libraries(ParticleSystem sfml-system sfml-window sfml-graphics sfml-network sfml-audio)

include(CTest)
enable_testing()
