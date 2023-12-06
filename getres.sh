adb push build/build_linux_arm/opencv_rkisp /tmp/build
adb shell /tmp/build
adb pull /tmp/output.png .
