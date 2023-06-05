#pragma once
#ifndef TOOLKITENGINEV3_MISC_H
#define TOOLKITENGINEV3_MISC_H

#include <iostream>
#include <filesystem>
#include <initializer_list>
#include <exception>
#include <stdexcept>
#include <type_traits>
#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include <GL/glew.h>

#define DEBUG_LINECHECK SDL_Log("%s line %d", __FILE_NAME__, __LINE__);

typedef struct FVec2 {
    FVec2(float px, float py) : x(px), y(py) {};
    float x = 0.0, y = 0.0;
} FVec2;

typedef struct FVec3 {
    FVec3(float px, float py, float pz) : x(px), y(py), z(pz) {};
    float x = 0.0, y = 0.0, z = 0.0;
} FVec3;

typedef struct FVec4 {
    FVec4(float px, float py, float pz, float pa) : x(px), y(py), z(pz), a(pa) {};
    float x, y, z, a;
} FVec4;

typedef struct IVec2 {
    int x = 0, y = 0;
} IVec2;

typedef struct IVec3 {
    int x = 0, y = 0, z = 0;
} IVec3;

typedef struct UVec2 {
    unsigned int x = 0, y = 0;
} UVec2;

typedef struct UVec3 {
    unsigned int x = 0, y = 0, z = 0;
} UVec3;

typedef union SizeVec2 {
    struct { size_t x = 0, y = 0; };
    struct { size_t w, h; };
} SizeVec2;

typedef struct Transform {
    FVec2 pos;
    FVec2 scale;
    float rot;
} Transform;

enum class Filter {
    FILTER_NEAREST = GL_NEAREST,
    FILTER_LINEAR = GL_LINEAR,
    FILTER_NEAREST_MIP_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
    FILTER_LINEAR_MIP_NEAREST = GL_LINEAR_MIPMAP_NEAREST,
    FILTER_NEAREST_MIP_LINEAR = GL_NEAREST_MIPMAP_LINEAR,
    FILTER_LINEAR_MIP_LINEAR = GL_LINEAR_MIPMAP_LINEAR,
};

template <typename T>
constexpr bool is_lvalue(T&) { return true; }

template <typename T>
constexpr bool is_lvalue(T&&) { return false; }

#endif // TOOLKITENGINEV3_MISC_H
