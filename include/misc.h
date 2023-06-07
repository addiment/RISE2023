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
//#include <GL/glew.h>

#define DEBUG_LINECHECK SDL_Log("%s line %d", __FILE_NAME__, __LINE__);

#define USE_STEAM

#ifndef PI
#define PI 3.14159265358979323846
#endif // PI

// The return value of this function may be a nullptr- don't dereference without validating.
#define RETURN_MAY_BE_NULL
// nullptr is a legal argument for this parameter/argument
#define ARGUMENT_MAY_BE_NULL

namespace Alib {
    template<typename T, typename... TAs>
    using Function = T (*)(TAs...);
    using Callback = void (*)();
}

template <typename E, typename T>
class EnumArray {
public:
    explicit EnumArray(const size_t enumSize) { array = new T[enumSize](); }
    ~EnumArray() { delete array; }
    T& operator[](E index) { return array[(size_t)index]; }
protected:
    T* array = nullptr;
    const size_t length = 1;
};

typedef class FVec2 {
public:
    FVec2() = default;
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

typedef class Transform {
public:
    Transform() = default;
    explicit Transform(FVec2 p = { 0, 0 }, FVec2 s = { 1, 1 }, float r = 0) : pos(p), scale(s), rot(r) { }
    FVec2 pos = { 0, 0 };
    FVec2 scale = { 1, 1 };
    // rot is in RADIANS 99% of the time!
    float rot = 0;
    Transform operator+(Transform t) const {
        return Transform{
            { pos.x     + t.pos.x   , pos.y     + t.pos.y   },
            { scale.x   + t.scale.x , scale.y   + t.scale.y },
            rot + t.rot
        };
    }
} Transform;

//enum class Filter {
//    FILTER_NEAREST = GL_NEAREST,
//    FILTER_LINEAR = GL_LINEAR,
//    FILTER_NEAREST_MIP_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
//    FILTER_LINEAR_MIP_NEAREST = GL_LINEAR_MIPMAP_NEAREST,
//    FILTER_NEAREST_MIP_LINEAR = GL_NEAREST_MIPMAP_LINEAR,
//    FILTER_LINEAR_MIP_LINEAR = GL_LINEAR_MIPMAP_LINEAR,
//};

template <typename T>
constexpr bool is_lvalue(T&) { return true; }

template <typename T>
constexpr bool is_lvalue(T&&) { return false; }

#endif // TOOLKITENGINEV3_MISC_H
