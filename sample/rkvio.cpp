#include "rkvio.hpp"
#include "rk_mpi_sys.h"
#include "sample_comm.h"
#include <cstdlib>
#include <cstring>

VideoCapture::VideoCapture(int Camid, int Chnid) {
  vi = (SAMPLE_VI_CTX_S *)malloc(sizeof(SAMPLE_VI_CTX_S));
  memset(vi, 0, sizeof(SAMPLE_VI_CTX_S));
  RK_S32 s32Ret = RK_FAILURE;
  int video_width = 1920;
  int video_height = 1080;

  PIXEL_FORMAT_E PixelFormat = RK_FMT_YUV420SP;
  COMPRESS_MODE_E CompressMode = COMPRESS_MODE_NONE;

   // Init VI
  vi->u32Width = video_width;       // 1080
  vi->u32Height = video_height;     // 1920
  vi->s32DevId = Camid;          // 0
  vi->u32PipeId = Camid; // 0
  vi->s32ChnId = Chnid;          // 0
  vi->stChnAttr.stIspOpt.u32BufCount = 2;
  vi->stChnAttr.stIspOpt.enMemoryType = VI_V4L2_MEMORY_TYPE_DMABUF;
  vi->stChnAttr.u32Depth = 1;
  vi->stChnAttr.enPixelFormat = PixelFormat; // YUV420SP
  vi->stChnAttr.enCompressMode = CompressMode;
  vi->stChnAttr.stFrameRate.s32SrcFrameRate = -1;
  vi->stChnAttr.stFrameRate.s32DstFrameRate = -1;


  RK_MPI_SYS_Init();
  SAMPLE_COMM_VI_CreateChn(vi);
}

VideoCapture::~VideoCapture() {
  SAMPLE_COMM_VI_DestroyChn(vi);
  RK_MPI_SYS_Exit();  
}

cv::Mat VideoCapture::read() {
  void * pData  = 0;
  SAMPLE_COMM_VI_GetChnFrame(vi, &pData);
  cv::Mat yuv(vi->u32Height*3/2, vi->u32Width, CV_8UC1, pData);

  return yuv;
}