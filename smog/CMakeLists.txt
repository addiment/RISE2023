cmake_minimum_required(VERSION 3.24)
project(SMOG)

set(CMAKE_SYSTEM_NAME Generic)

if(DEFINED WIN32)
    set(CMAKE_C_COMPILER "C:/Program Files/LLVM/bin/clang.exe")
    set(CMAKE_CXX_COMPILER "C:/Program Files/LLVM/bin/clang++.exe")
endif()

if(NOT DEFINED BUILD_ARCH)
    set(BUILD_ARCH "x64")
endif()
if(NOT DEFINED STEAMWORKS_VERSION)
    set(STEAMWORKS_VERSION "157")
endif()

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${PROJECT_SOURCE_DIR}/../cmake")

set(STEAMWORKS_ROOT "${PROJECT_SOURCE_DIR}/../steamworks_sdk_${STEAMWORKS_VERSION}/sdk")

find_package(Steamworks REQUIRED)

include_directories(${STEAMWORKS_INCLUDE_DIRS})

add_compile_options(-O3)
add_link_options(-O3)


#add_library(${PROJECT_NAME} SHARED smog.cpp)
add_library(${PROJECT_NAME} STATIC smog.cpp)
target_link_libraries(${PROJECT_NAME} ${STEAMWORKS_LIBRARIES})

# END STEAMWORKS STUFF