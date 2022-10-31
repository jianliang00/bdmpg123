bdmpg123
==============

Customized development for android based on mpg123 ( http://www.mpg123.de/ ). 

## Contents

### Build

Run "make" to compile dynamic link library for the Android platform with mpg123 code download from web.

You may change NDK_BUILD in Makefile to the correct local path. On error "Unknown host CPU architecture: arm64" (maybe Apple M1 Max etc), please copy android_build/ndk-build-for-m1 to your ndk path and use it.

