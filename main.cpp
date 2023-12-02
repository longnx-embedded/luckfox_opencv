#include "rkvio.hpp"
#include <iostream>
#include <opencv2/core/types.hpp>
#include <opencv2/imgproc.hpp>

int main() {
  VideoCapture cap(0, 0);
  cv::Mat yuv = cap.read();
  cv::Mat img;
  cv::cvtColor(yuv, img, cv::COLOR_YUV420sp2GRAY);
  std::cout << img(cv::Rect(500, 500, 50, 50));
  cv::imwrite("/tmp/output.png", img(cv::Rect(500, 500, 500, 500)));

}