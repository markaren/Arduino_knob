cmake_minimum_required(VERSION 3.19)
project(arduino_knob)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/resources/knob.svg" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/bin/")

include(FetchContent)
set(THREEPP_BUILD_TESTS OFF)
set(THREEPP_BUILD_EXAMPLES OFF)
FetchContent_Declare(
        threepp
        GIT_REPOSITORY https://github.com/markaren/threepp.git
        GIT_TAG 1dd8c4ae3903bc09bf6923a812e709e79f22528a
)
FetchContent_MakeAvailable(threepp)

set(SERIAL_BUILD_EXAMPLES OFF)
FetchContent_Declare(
        serial
        GIT_REPOSITORY https://github.com/markaren/serial.git
        GIT_TAG d011f55e23acbd5b13c4f7ad5fbe4071f7372fe0
)
FetchContent_MakeAvailable(serial)


add_executable(arduino_knob main.cpp)
target_link_libraries(arduino_knob PRIVATE threepp::threepp serial)
target_include_directories(arduino_knob PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
