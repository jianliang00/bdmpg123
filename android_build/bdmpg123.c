/*
 * Copyright 2022 ByteDance Ltd. and/or its affiliates.
 * SPDX license identifier: LGPL-2.1-or-later"
 */

#include "bdmpg123.h"
#include "mpg123.h"

bd_mpg123_handle bd_mpg123_new(const char* decoder, int *error) {
    return mpg123_new(decoder, error);
}

int bd_mpg123_init(void) {
    return mpg123_init();
}

void bd_mpg123_delete(bd_mpg123_handle mh) {
    return mpg123_delete((mpg123_handle*)mh);
}

int bd_mpg123_getformat(bd_mpg123_handle mh, long *rate, int *channels, int *encoding) {
    return mpg123_getformat((mpg123_handle*)mh, rate, channels, encoding);
}

int bd_mpg123_open_feed(bd_mpg123_handle mh) {
    return mpg123_open_feed((mpg123_handle*)mh);
}

int bd_mpg123_close(bd_mpg123_handle mh) {
    return mpg123_close((mpg123_handle*)mh);
}

int bd_mpg123_feed(bd_mpg123_handle mh, const unsigned char *in, size_t size) {
    return mpg123_feed((mpg123_handle*)mh, in, size);
}

int bd_mpg123_decode_frame(bd_mpg123_handle mh, off_t *num, unsigned char **audio, size_t *bytes) {
    return mpg123_decode_frame((mpg123_handle*)mh, num, audio, bytes);
}

off_t bd_mpg123_feedseek(bd_mpg123_handle mh, off_t sampleoff, int whence, off_t *input_offset) {
    return mpg123_feedseek((mpg123_handle*)mh, sampleoff, whence, input_offset);
}

off_t bd_mpg123_length(bd_mpg123_handle mh) {
    return mpg123_length((mpg123_handle*)mh);
}

