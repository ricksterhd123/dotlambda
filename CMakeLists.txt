cmake_minimum_required(VERSION 3.30)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(dotlambda C CXX)

include(FetchContent)

FetchContent_Declare(
        JoltPhysics
        GIT_REPOSITORY "https://github.com/jrouwe/JoltPhysics"
        GIT_TAG "v5.1.0"
		SOURCE_SUBDIR "Build"
)
FetchContent_MakeAvailable(JoltPhysics)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
# don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) 
# don't build the supplied example games

FetchContent_Declare(
    raylib
    GIT_REPOSITORY "https://github.com/raysan5/raylib"
    GIT_TAG "5.0"
)
FetchContent_MakeAvailable(raylib)

FetchContent_Declare(
    raylib-cpp
    GIT_REPOSITORY "https://github.com/RobLoach/raylib-cpp"
    GIT_TAG "v5.0.2"
)
FetchContent_MakeAvailable(raylib-cpp)


file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp")
set(PROJECT_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/src/")

include_directories(${raylib-cpp_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_INCLUDE})

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
target_link_libraries(${PROJECT_NAME} PRIVATE Jolt)

target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/")
