#ifndef __CORE_HPP_INCLUDED__
#define __CORE_HPP_INCLUDED__


    #ifndef BOX3D_PLATFORM_WINDOWS
    #else
        #error Box3d only supports Windows!
    #endif

    #define BIT(x) (1 << x)

#endif // !__CORE_HPP_INCLUDED__