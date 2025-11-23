#pragma once
#include <type_traits>

namespace Rendering {

enum class PrimitiveType {
    Points,
    Lines,
    Triangles,
    TriangleStrip
};

enum class BufferUsage {
    Static,
    Dynamic,
    Stream
};

enum class RenderState {
    None = 0,
    DepthTest = 1 << 0,
    Blending = 1 << 1,
    FaceCulling = 1 << 2,
    Wireframe = 1 << 3
};

enum class ClearFlags {
    None = 0,
    Color = 1 << 0,
    Depth = 1 << 1,
    Stencil = 1 << 2
};

constexpr ClearFlags operator|(ClearFlags a, ClearFlags b) {
    using T = typename std::underlying_type<ClearFlags>::type;
    return static_cast<ClearFlags>(static_cast<T>(a) | static_cast<T>(b));
}

constexpr ClearFlags operator&(ClearFlags a, ClearFlags b) {
    using T = typename std::underlying_type<ClearFlags>::type;
    return static_cast<ClearFlags>(static_cast<T>(a) & static_cast<T>(b));
}

constexpr RenderState operator|(RenderState a, RenderState b) {
    using T = typename std::underlying_type<RenderState>::type;
    return static_cast<RenderState>(static_cast<T>(a) | static_cast<T>(b));
}

constexpr RenderState operator&(RenderState a, RenderState b) {
    using T = typename std::underlying_type<RenderState>::type;
    return static_cast<RenderState>(static_cast<T>(a) & static_cast<T>(b));
}

constexpr RenderState operator~(RenderState a) {
    using T = typename std::underlying_type<RenderState>::type;
    return static_cast<RenderState>(~static_cast<T>(a));
}

inline bool HasFlag(ClearFlags flags, ClearFlags flag) {
    return (flags & flag) != ClearFlags::None;
}

inline bool HasFlag(RenderState flags, RenderState flag) {
    return (flags & flag) != RenderState::None;
}

struct Color {
    float r, g, b, a;
    
    Color(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f)
        : r(r), g(g), b(b), a(a) {}
    
    static Color Black() { return Color(0.0f, 0.0f, 0.0f, 1.0f); }
    static Color White() { return Color(1.0f, 1.0f, 1.0f, 1.0f); }
    static Color Red() { return Color(1.0f, 0.0f, 0.0f, 1.0f); }
    static Color Green() { return Color(0.0f, 1.0f, 0.0f, 1.0f); }
    static Color Blue() { return Color(0.0f, 0.0f, 1.0f, 1.0f); }
};

}
