adb push build/opencv_rkisp /tmp/build
adb shell /tmp/build
adb pull /tmp/output.png .