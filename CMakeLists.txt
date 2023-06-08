cmake_minimum_required(VERSION 3.24)
project(RISE)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_SYSTEM_NAME Generic)

add_subdirectory(smog)

include_directories(src include)

# use -DBUILD_ARCH x64 or x86
set(BUILD_ARCH "x64")
set(STEAMWORKS_VERSION "157")

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer >= 2.0.0 REQUIRED)
find_package(Steamworks REQUIRED)

add_compile_options(-Wall -O2)
add_link_options(-O2) # add flto if lld
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DCMAKE_BUILD_DEBUG") # some #ifdef directives in the code use CMAKE_BUILD_DEBUG


include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${STEAMWORKS_INCLUDE_DIRS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mconsole -Wall")
# -O2
add_executable(${PROJECT_NAME}
    res/toolkit.rc

    src/main.cpp
    src/Nickable.cpp
    src/Nickable.cpp
    src/aces.cpp
    src/Scene.cpp
    src/Manager.cpp
    src/EzInputSys.cpp

    include/actors/Player.hpp

    include/tkev3.h
    include/Nickable.h
    include/misc.h
    include/aces.h
    include/Camera.h
    include/Manager.h
    include/Scene.h
    include/scenes/TestScene.hpp
    include/EzInputSys.h
    include/components/Sprite.hpp include/SpriteSheet.h src/SpriteSheet.cpp src/Camera.cpp)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${STEAMWORKS_LIBRARIES} SMOG)