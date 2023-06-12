cmake_minimum_required(VERSION 3.18)
project(RISE)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_SYSTEM_NAME Generic)

include_directories(src include)

# use -DBUILD_ARCH x64 or x86
set(BUILD_ARCH "x64")
set(STEAMWORKS_VERSION "157")

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${PROJECT_SOURCE_DIR}/cmake")

include(FindPkgConfig)

find_package(SDL2 REQUIRED)
pkg_search_module(SDL2_IMAGE REQUIRED SDL2_image>=2.0.0)
pkg_search_module(SDL2_MIXER REQUIRED SDL2_mixer>=2.0.0)
find_package(Steamworks REQUIRED)

add_compile_options(-Wall -O2)
add_link_options(-O2) # add flto if lld

if(DEFINED WIN32)
    add_compile_options(-mconsole)
    add_link_options(-mconsole)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DCMAKE_BUILD_DEBUG") # some #ifdef directives in the code use CMAKE_BUILD_DEBUG
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DCMAKE_BUILD_RELEASE") # some #ifdef directives in the code use CMAKE_BUILD_DEBUG

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS} ${STEAMWORKS_INCLUDE_DIRS})

set_source_files_properties(res/toolkit.rc PROPERTIES CMAKE_CONFIGURE_DEPENDS res/icon.ico )

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
    include/components/Sprite.hpp include/SpriteSheet.h src/SpriteSheet.cpp src/Camera.cpp include/EzSoundSys.h src/EzSoundSys.cpp include/components/UserInterface.h include/components/PlayerHUD.h)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_MIXER_LIBRARIES} ${STEAMWORKS_LIBRARIES})
