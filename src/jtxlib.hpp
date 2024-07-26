#pragma once

#ifdef CUDA_ENABLED
    #include <cuda_runtime.h>
    #define JTX_HOSTDEV __host__ __device__
    #define JTX_DEV __device__
    #define JTX_HOST __host__
    #define JTX_INLINE __forceinline__
#else
    #define JTX_HOSTDEV
    #define JTX_DEV
    #define JTX_HOST
    #define JTX_INLINE inline
#endif