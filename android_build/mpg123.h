/*
 * Copyright 2022 ByteDance Ltd. and/or its affiliates.
 * SPDX license identifier: LGPL-2.1-or-later"
 */

#ifndef MPG123_ANDROID_H
#define MPG123_ANDROID_H

#include <stdlib.h>
#include <sys/types.h>

#define MPG123_NO_CONFIGURE
#include "../src/libmpg123/mpg123.h.in" /* Yes, .h.in; we include the configure template! */

#endif
