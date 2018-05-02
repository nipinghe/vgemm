#ifndef __vgemm_h__
#define __vgemm_h__

#if defined(_MSC_VER)&&defined(_WIN64)
  #ifdef _DLL
    #define vgemmApiEntry __declspec(dllexport)
  #else
    #define vgemmApiEntry __declspec(dllimport)
  #endif
#else
  #define vgemmApiEntry
#endif

#ifndef __APPLE__
  #include<CL/cl.h>
#else
  #include<OpenCL/cl.h>
#endif

typedef enum{
    vgemm_success=0           ,
    vgemm_error_invalid_device,
    vgemm_error_invalid_size  ,
    vgemm_error_invalid_binary,
    vgemm_error_out_of_memory ,
    vgemm_error_out_of_maxdim ,
    vgemm_error_out_of_maxsize
} vgemm_status_t;

typedef enum{
    scr128x128=0,
    scc128x128=1,
    xcr64x64  =2,
    xcc64x64  =3,
    xcr128x128=4,
    hcr64x64  =5,
    hcr128x128=6,
    hcc128x128=7
} vgemm_routine_t;

typedef struct __vgemmCtx *vgemmCtx;
typedef struct __vgemmOp  *vgemmOp;

#ifdef __cplusplus
extern "C"
{
#endif

vgemmApiEntry vgemm_status_t vgemm_createCtx( vgemmCtx*, cl_context );
vgemmApiEntry unsigned int   vgemm_get_optimal_leading_size( unsigned int );
vgemmApiEntry vgemm_status_t vgemm_createOp( vgemmOp*, vgemmCtx, vgemm_routine_t );
vgemmApiEntry vgemm_status_t vgemm_launch( cl_command_queue, vgemmOp, cl_mem, cl_mem, cl_mem, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, float, cl_uint, const cl_event*, cl_event* );
vgemmApiEntry vgemm_status_t vgemm_releaseOp( vgemmOp );
vgemmApiEntry vgemm_status_t vgemm_releaseCtx( vgemmCtx );

#ifdef __cplusplus
}
#endif

#endif