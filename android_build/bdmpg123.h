/*
 * Copyright 2022 ByteDance Ltd. and/or its affiliates.
 * SPDX license identifier: LGPL-2.1-or-later"
 */

#ifndef BD_MPG123_H
#define BD_MPG123_H

#include <stdlib.h>
#include <sys/types.h>

#define BD_MPG123_EXPORT  extern __attribute__((visibility("default")))

#ifdef __cplusplus
extern "C" {
#endif

enum bd_mpg123_errors {
	BD_MPG123_DONE=-12,	/**< Message: Track ended. Stop decoding. */
	BD_MPG123_NEW_FORMAT=-11,	/**< Message: Output format will be different on next call. Note that some libmpg123 versions between 1.4.3 and 1.8.0 insist on you calling mpg123_getformat() after getting this message code. Newer verisons behave like advertised: You have the chance to call mpg123_getformat(), but you can also just continue decoding and get your data. */
	BD_MPG123_NEED_MORE=-10,	/**< Message: For feed reader: "Feed me more!" (call mpg123_feed() or mpg123_decode() with some new input data). */
	BD_MPG123_ERR=-1,			/**< Generic Error */
	BD_MPG123_OK=0, 			/**< Success */
};

enum bd_mpg123_enc_enum {
/* 0000 0000 0000 1111 Some 8 bit  integer encoding. */
	BD_MPG123_ENC_8      = 0x00f
/* 0000 0000 0100 0000 Some 16 bit integer encoding. */
,	BD_MPG123_ENC_16     = 0x040
/* 0100 0000 0000 0000 Some 24 bit integer encoding. */
,	BD_MPG123_ENC_24     = 0x4000 
/* 0000 0001 0000 0000 Some 32 bit integer encoding. */
,	BD_MPG123_ENC_32     = 0x100  
/* 0000 0000 1000 0000 Some signed integer encoding. */
,	BD_MPG123_ENC_SIGNED = 0x080  
/* 0000 1110 0000 0000 Some float encoding. */
,	BD_MPG123_ENC_FLOAT  = 0xe00  
/* 0000 0000 1101 0000 signed 16 bit */
,	BD_MPG123_ENC_SIGNED_16   = (BD_MPG123_ENC_16|BD_MPG123_ENC_SIGNED|0x10)
/* 0000 0000 0110 0000 unsigned 16 bit */
,	BD_MPG123_ENC_UNSIGNED_16 = (BD_MPG123_ENC_16|0x20)
/* 0000 0000 0000 0001 unsigned 8 bit */
,	BD_MPG123_ENC_UNSIGNED_8  = 0x01
/* 0000 0000 1000 0010 signed 8 bit */
,	BD_MPG123_ENC_SIGNED_8    = (BD_MPG123_ENC_SIGNED|0x02)
/* 0000 0000 0000 0100 ulaw 8 bit */
,	BD_MPG123_ENC_ULAW_8      = 0x04
/* 0000 0000 0000 1000 alaw 8 bit */
,	BD_MPG123_ENC_ALAW_8      = 0x08
/* 0001 0001 1000 0000 signed 32 bit */
,	BD_MPG123_ENC_SIGNED_32   = BD_MPG123_ENC_32|BD_MPG123_ENC_SIGNED|0x1000
/* 0010 0001 0000 0000 unsigned 32 bit */
,	BD_MPG123_ENC_UNSIGNED_32 = BD_MPG123_ENC_32|0x2000
/* 0101 0000 1000 0000 signed 24 bit */
,	BD_MPG123_ENC_SIGNED_24   = BD_MPG123_ENC_24|BD_MPG123_ENC_SIGNED|0x1000
/* 0110 0000 0000 0000 unsigned 24 bit */
,	BD_MPG123_ENC_UNSIGNED_24 = BD_MPG123_ENC_24|0x2000
/* 0000 0010 0000 0000 32bit float */
,	BD_MPG123_ENC_FLOAT_32    = 0x200
/* 0000 0100 0000 0000 64bit float */
,	BD_MPG123_ENC_FLOAT_64    = 0x400
};

typedef void* bd_mpg123_handle;

BD_MPG123_EXPORT int bd_mpg123_init(void);

BD_MPG123_EXPORT bd_mpg123_handle bd_mpg123_new(const char* decoder, int *error);

BD_MPG123_EXPORT void bd_mpg123_delete(bd_mpg123_handle mh);

BD_MPG123_EXPORT int bd_mpg123_getformat(bd_mpg123_handle mh, long *rate, int *channels, int *encoding);

BD_MPG123_EXPORT int bd_mpg123_open_feed(bd_mpg123_handle mh);

BD_MPG123_EXPORT int bd_mpg123_close(bd_mpg123_handle mh);

BD_MPG123_EXPORT int bd_mpg123_feed(bd_mpg123_handle mh, const unsigned char *in, size_t size);

BD_MPG123_EXPORT int bd_mpg123_decode_frame( bd_mpg123_handle mh, off_t *num, unsigned char **audio, size_t *bytes);

BD_MPG123_EXPORT off_t bd_mpg123_feedseek( bd_mpg123_handle mh, off_t sampleoff, int whence, off_t *input_offset );

BD_MPG123_EXPORT off_t bd_mpg123_length(bd_mpg123_handle mh);

#ifdef __cplusplus
}
#endif

#endif
