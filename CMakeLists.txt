cmake_minimum_required(VERSION 3.24)
project(RISE)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_SYSTEM_NAME Generic)

add_subdirectory(smog)

include_directories(src include)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

add_compile_options(-Wall -O2)
add_link_options(-O2) # add flto if lld

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DCMAKE_BUILD_DEBUG")

# use -DBUILD_ARCH with x64 or x86
if(NOT DEFINED BUILD_ARCH)
    set(BUILD_ARCH "x64")
endif()

# BEGIN STEAMWORKS STUFF

if(NOT DEFINED STEAMWORKS_VERSION)
    set(STEAMWORKS_VERSION "157")
endif()
set(STEAMWORKS_ROOT "${PROJECT_SOURCE_DIR}/steamworks_sdk_${STEAMWORKS_VERSION}/sdk")
set(STEAMWORKS_INCLUDE_DIRS "${STEAMWORKS_ROOT}/public")

if (NOT ((BUILD_ARCH STREQUAL "x86") OR (BUILD_ARCH STREQUAL "x64")))
    message(FATAL_ERROR "Unsupported Steamworks architecture (only supports x86 and x64 targets)")
endif()

if (APPLE)
    #    wait it's actually not???
    #    if (BUILD_ARCH STREQUAL "x86")
    #        message(FATAL_ERROR "Trying to compile an x86 Apple target, unsupported")
    #    endif()
    set(STEAMWORKS_LIBRARIES "${STEAMWORKS_ROOT}/redistributable_bin/osx/libsteam_api.dylib")
    set(STEAMWORKS_STATIC_LIBRARIES ${STEAMWORKS_LIBRARIES})
    set(STEAMWORKS_SHARED_LIBRARIES ${STEAMWORKS_LIBRARIES})
elseif(WIN32)
    if (BUILD_ARCH STREQUAL "x86")
        set(STEAMWORKS_STATIC_LIBRARIES "${STEAMWORKS_ROOT}/redistributable_bin/steam_api.lib")
        set(STEAMWORKS_SHARED_LIBRARIES "${STEAMWORKS_ROOT}/redistributable_bin/steam_api.dll")
    elseif(BUILD_ARCH STREQUAL "x64")
        set(STEAMWORKS_STATIC_LIBRARIES "${STEAMWORKS_ROOT}/redistributable_bin/win64/steam_api64.lib")
        set(STEAMWORKS_SHARED_LIBRARIES "${STEAMWORKS_ROOT}/redistributable_bin/win64/steam_api64.dll")
    endif()
    set(STEAMWORKS_LIBRARIES ${STEAMWORKS_STATIC_LIBRARIES} ${STEAMWORKS_SHARED_LIBRARIES})
elseif(UNIX)
    if (BUILD_ARCH STREQUAL "x86")
        set(STEAMWORKS_LIBRARIES "${STEAMWORKS_ROOT}/redistributable_bin/linux32/libsteam_api.so")
    elseif(BUILD_ARCH STREQUAL "x64")
        set(STEAMWORKS_LIBRARIES "${STEAMWORKS_ROOT}/redistributable_bin/linux64/libsteam_api.so")
    endif()
    set(STEAMWORKS_STATIC_LIBRARIES ${STEAMWORKS_LIBRARIES})
    set(STEAMWORKS_SHARED_LIBRARIES ${STEAMWORKS_LIBRARIES})
else()
    message(FATAL_ERROR "Unsupported Steamworks platform")
endif()

# END STEAMWORKS STUFF

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