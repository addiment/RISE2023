if(NOT DEFINED BUILD_ARCH)
    set(BUILD_ARCH "x86")
endif()

if(NOT DEFINED STEAMWORKS_VERSION)
    set(STEAMWORKS_VERSION "157")
endif()

if(NOT DEFINED STEAMWORKS_ROOT)
    set(STEAMWORKS_ROOT "${PROJECT_SOURCE_DIR}/steamworks_sdk_${STEAMWORKS_VERSION}/sdk")
endif()

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