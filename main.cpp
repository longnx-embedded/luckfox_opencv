#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <getopt.h>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <pthread.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/prctl.h>
#include <time.h>
#include <unistd.h>


#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "sample_comm.h"

typedef struct _rkMpiCtx {
  SAMPLE_VI_CTX_S vi;
} SAMPLE_MPI_CTX_S;

static bool quit = false;

int main() {
  RK_S32 s32Ret = RK_FAILURE;
  SAMPLE_MPI_CTX_S *ctx;
  int video_width = 1920;
  int video_height = 1080;
  RK_CHAR *pOutPath = NULL;
  RK_CHAR *pDeviceName = NULL;
  RK_S32 i;
  RK_S32 s32CamId = 0;
  RK_S32 s32ChnId = 0;
  RK_S32 s32loopCnt = -1;
  PIXEL_FORMAT_E PixelFormat = RK_FMT_YUV420SP;
  COMPRESS_MODE_E CompressMode = COMPRESS_MODE_NONE;
  // rk_aiq_working_mode_t hdr_mode = RK_AIQ_WORKING_MODE_NORMAL;
  MPP_CHN_S stSrcChn, stDestChn;
  pthread_t vi_thread_id;

  ctx = (SAMPLE_MPI_CTX_S *)(malloc(sizeof(SAMPLE_MPI_CTX_S)));
  memset(ctx, 0, sizeof(SAMPLE_MPI_CTX_S));

  // signal(SIGINT, sigterm_handler);

  RK_MPI_SYS_Init();

  // Init VI
  ctx->vi.u32Width = video_width;       // 1080
  ctx->vi.u32Height = video_height;     // 1920
  ctx->vi.s32DevId = s32CamId;          // 0
  ctx->vi.u32PipeId = ctx->vi.s32DevId; // 0
  ctx->vi.s32ChnId = s32ChnId;          // 0
  ctx->vi.stChnAttr.stIspOpt.u32BufCount = 2;
  ctx->vi.stChnAttr.stIspOpt.enMemoryType = VI_V4L2_MEMORY_TYPE_DMABUF;
  ctx->vi.stChnAttr.u32Depth = 1;
  ctx->vi.stChnAttr.enPixelFormat = PixelFormat; // YUV420SP
  ctx->vi.stChnAttr.enCompressMode = CompressMode;
  ctx->vi.stChnAttr.stFrameRate.s32SrcFrameRate = -1;
  ctx->vi.stChnAttr.stFrameRate.s32DstFrameRate = -1;
  // deprected
  ctx->vi.dstFilePath = pOutPath;
  ctx->vi.s32loopCount = s32loopCnt;

  SAMPLE_COMM_VI_CreateChn(&ctx->vi);

  // pthread_create(&vi_thread_id, 0, vi_get_stream, (void *)(&ctx->vi));

  // init finish
  char name[256] = {0};
  void *pData = RK_NULL;

  s32Ret = SAMPLE_COMM_VI_GetChnFrame(&ctx->vi, &pData);
  // pData is image yuv420sp
  // std::cout << ctx->vi.stViFrame.stVFrame.pMbBlk << std::endl;
  // FILE *fp = fopen("./frame.bin", "wb");
  // fwrite(pData, 1, ctx->vi.stViFrame.stVFrame.u64PrivateData, fp);
  // fclose(fp);

  // cv::Mat srcMat(ctx->vi.u32Height, ctx->vi.u32Width, CV_8UC3, pData);

  // cv::Mat outMat;
  // cv::cvtColor(srcMat, outMat, cv::COLOR_YUV2BGR_NV12);

  // cv::imwrite("A.png", outMat);
  // vi_get_stream(&ctx->vi);
  // Destroy VI

  cv::Mat yuv;
  cv::Mat m_color;

  std::cout << ctx->vi.stViFrame.stVFrame.u64PrivateData << std::endl;
  std::cout << ctx->vi.u32Height << std::endl;
  std::cout << ctx->vi.u32Width << std::endl;


  yuv.create(ctx->vi.u32Height * 3 / 2, ctx->vi.u32Width, CV_8UC1);
  std::cout << "yuv create done" << std::endl;
  memcpy(yuv.data, pData, ctx->vi.u32Height * ctx->vi.u32Width * 3 / 2);
  std::cout << "yuv copy done" << std::endl;
  free(pData);
  std::cout << "free done" << std::endl;
  cv::cvtColor(yuv, m_color, cv::COLOR_YUV2RGB_I420);
  std::cout << "cvtColor done" << std::endl;
  yuv.deallocate();
  cv::imwrite("./output.png", m_color);

  SAMPLE_COMM_VI_DestroyChn(&ctx->vi);

  RK_MPI_SYS_Exit();
}
