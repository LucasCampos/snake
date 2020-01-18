cmake_minimum_required(VERSION 3.5)
include(ExternalProject)
set( CMAKE_EXPORT_COMPILE_COMMANDS 1 )
set( CMAKE_EXPORT_LINKAGE_COMMANDS 1 )


# Set the name of the project and target:
set(TARGET "Snake")
project(${TARGET} CXX)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(TARGET_SRC
    ${TARGET_SRC} src/board.cpp src/main.cpp src/snake.cpp src/snake_brain.cpp src/common.cpp src/generation.cpp
  )
add_executable(${TARGET} ${TARGET_SRC})
include_directories(inc)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -march=native")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")

add_custom_target(debug
COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Debug ${CMAKE_SOURCE_DIR}
COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target all
COMMENT "Switch CMAKE_BUILD_TYPE to Debug"
)

add_custom_target(release
COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Release ${CMAKE_SOURCE_DIR}
COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target all
COMMENT "Switch CMAKE_BUILD_TYPE to Release"
)

target_link_libraries(${TARGET} ${CONAN_LIBS})
set_property(TARGET ${TARGET} PROPERTY CXX_STANDARD 17)
