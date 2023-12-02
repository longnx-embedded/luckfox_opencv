#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <getopt.h>
#include <pthread.h>
#include <signal.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/prctl.h>
#include <time.h>
#include <unistd.h>

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "sample_comm.h"

class VideoCapture {
  public:
  VideoCapture(int Camid, int Chnid);
  ~VideoCapture();
  cv::Mat read();
  SAMPLE_VI_CTX_S * vi;

};