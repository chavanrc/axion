cmake_minimum_required(VERSION 3.17)

project(tests)

set(CMAKE_CXX_STANDARD 20)

file(GLOB SOURCE_FILES *.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE ../external/Catch2/single_include
        ../problem/include)

target_link_libraries(${PROJECT_NAME} balancing_scale)