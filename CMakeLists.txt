cmake_minimum_required(VERSION 3.0.0)
project(QR_CardGenerator VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CTest)
enable_testing()

set(SOURCES main.cpp stb_image_write.h)

add_executable(QR_CardGenerator ${SOURCES})

find_library(LUNA_SVG lunasvg lib)

target_link_libraries(QR_CardGenerator LINK_PUBLIC ${LUNA_SVG})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)