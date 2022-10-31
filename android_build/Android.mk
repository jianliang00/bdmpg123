# Copyright 2022 ByteDance Ltd. and/or its affiliates. SPDX license identifier: LGPL-2.1-or-later"

LOCAL_PATH := $(call my-dir)
 
include $(CLEAR_VARS)

LOCAL_C_INCLUDES += $(PROJECT_PATH)../src $(PROJECT_PATH)../src/compat $(PROJECT_PATH)../src/libmpg123

MPG123_CFLAGS   :=  -Wall -D__ANDROID__ -I . -I libmpg123 \
    -DACCURATE_ROUNDING\
    -flto  -fomit-frame-pointer -fno-sanitize=safe-stack -fvisibility=hidden -fvisibility-inlines-hidden -fno-short-enums -Wall -fno-strict-aliasing \

MPG123_CFLAGS_ARMv7 := -Oz \
    -DANDROID_ABI=armeabi-v7a \
    -DOPT_ARM \
    -DREAL_IS_FIXED \
    -DASMALIGN_EXP \
    -DNO_REAL \
    -DNO_32BIT

MPG123_CFLAGS_ARMv8 := -Oz \
    -DANDROID_ABI=arm64-v8a \
    -DOPT_GENERIC \
    -DREAL_IS_FIXED \
    -DASMALIGN_EXP \
    -DNO_REAL \
    -DNO_32BIT

MPG123_CFLAGS_x85 :=  -DOPT_GENERIC \
    -DASMALIGN_BYTE -DOPT_SSE

MPG123_SRC_FILES_x86 := \
    ../src/libmpg123/synth_sse_accurate.S\
    ../src/libmpg123/synth_stereo_sse_accurate.S\
    ../src/libmpg123/synth_stereo_sse_float.S\
    ../src/libmpg123/synth_stereo_sse_s32.S\
    ../src/libmpg123/synth_sse_s32.S\
    ../src/libmpg123/synth_sse_float.S\
    ../src/libmpg123/synth_sse.S\
    ../src/libmpg123/synth_s32.c\
    ../src/libmpg123/synth_real.c\
    ../src/libmpg123/tabinit_mmx.S\
    ../src/libmpg123/dct64_i386.c\
    ../src/libmpg123/dct64_sse_float.S\
    ../src/libmpg123/dct64_sse.S\

MPG123_SRC_FILES_ARMv7 := \
    ../src/libmpg123/synth_arm.S\
	../src/libmpg123/synth_arm_accurate.S

MPG123_SRC_FILES := \
    ./bdmpg123.c \
    ../src/compat/compat.c \
    ../src/compat/compat_str.c \
    ../src/libmpg123/frame.c \
    ../src/libmpg123/id3.c \
    ../src/libmpg123/format.c \
    ../src/libmpg123/stringbuf.c \
    ../src/libmpg123/libmpg123.c\
    ../src/libmpg123/readers.c\
    ../src/libmpg123/icy.c\
	../src/libmpg123/icy2utf8.c\
    ../src/libmpg123/index.c\
    ../src/libmpg123/layer1.c\
    ../src/libmpg123/layer2.c\
    ../src/libmpg123/layer3.c\
    ../src/libmpg123/parse.c\
 	../src/libmpg123/optimize.c\
  	../src/libmpg123/synth.c\
  	../src/libmpg123/synth_8bit.c\
    ../src/libmpg123/ntom.c\
    ../src/libmpg123/dct64.c\
    ../src/libmpg123/equalizer.c\
   	../src/libmpg123/dither.c\
    ../src/libmpg123/tabinit.c\
    ../src/libmpg123/feature.c

ifeq ($(TARGET_ARCH),x86)
  MPG123_SRC_FILES :=  $(MPG123_SRC_FILES) \
  $(MPG123_SRC_FILES_x86)
  MPG123_CFLAGS :=  $(MPG123_CFLAGS) \
  $(MPG123_CFLAGS_x85)
endif
ifeq ($(TARGET_ARCH),arm)
    MPG123_SRC_FILES :=  $(MPG123_SRC_FILES) \
      $(MPG123_SRC_FILES_ARMv7)
    MPG123_CFLAGS :=  $(MPG123_CFLAGS) \
      $(MPG123_CFLAGS_ARMv7)
endif
ifeq ($(TARGET_ARCH),arm64)
    MPG123_SRC_FILES :=  $(MPG123_SRC_FILES) \
      $(MPG123_SRC_FILES_ARMv8)
    MPG123_CFLAGS :=  $(MPG123_CFLAGS) \
      $(MPG123_CFLAGS_ARMv8)
endif

# Here we give our module name and source file(s)
LOCAL_MODULE := bdmpg123
ifeq ($(TARGET_ARCH),arm)
    LOCAL_ARM_MODE := arm
endif

$(warning $(MPG123_CFLAGS))

LOCAL_CFLAGS    := $(MPG123_CFLAGS)
LOCAL_SRC_FILES := $(MPG123_SRC_FILES)
LOCAL_LDLIBS    := -llog -fuse-ld=lld -O2 -flto -Wl,--icf=all  -Wl,--exclude-libs,ALL,--gc-sections
 
include $(BUILD_SHARED_LIBRARY)
