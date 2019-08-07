#ifndef __CORE_HPP_INCLUDED__
#define __CORE_HPP_INCLUDED__


    #ifndef BOX3D_PLATFORM_WINDOWS
    #else
        #error Box3d only supports Windows!
    #endif

    #ifdef BOX3D_DEBUG
        #define BOX3D_ENABLE_ASSERTS
    #endif

    #ifdef BOX3D_ENABLE_ASSERTS
        #define BOX3D_ASSERT(x, ...)      { if(!(x)) { BOX3D_ERROR     ("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
        #define BOX3D_CORE_ASSERT(x, ...) { if(!(x)) { BOX3D_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
    #else
        #define BOX3D_ASSERT     (x, ...)
        #define BOX3D_CORE_ASSERT(x, ...)
    #endif
    
    #define BIT(x) (1 << x)

#define BOX3D_FN_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

#endif // !__CORE_HPP_INCLUDED__
