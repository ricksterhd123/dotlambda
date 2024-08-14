cmake_minimum_required(VERSION 3.0)
project(dotlambda C CXX)

configure_file(file.scm file.scm COPYONLY)

set(CMAKE_CXX_STANDARD 17)
find_package(raylib CONFIG REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp src/lib/rscript.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC raylib chibi-scheme)
target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/")
