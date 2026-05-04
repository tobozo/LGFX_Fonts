#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    LGFX_LV_COLOR_FORMAT_UNKNOWN           = 0,

    LGFX_LV_COLOR_FORMAT_RAW               = 0x01,
    LGFX_LV_COLOR_FORMAT_RAW_ALPHA         = 0x02,

    /*<=1 byte (+alpha) formats*/
    LGFX_LV_COLOR_FORMAT_L8                = 0x06,
    LGFX_LV_COLOR_FORMAT_I1                = 0x07,
    LGFX_LV_COLOR_FORMAT_I2                = 0x08,
    LGFX_LV_COLOR_FORMAT_I4                = 0x09,
    LGFX_LV_COLOR_FORMAT_I8                = 0x0A,
    LGFX_LV_COLOR_FORMAT_A8                = 0x0E,

    /*2 byte (+alpha) formats*/
    LGFX_LV_COLOR_FORMAT_RGB565            = 0x12,
    LGFX_LV_COLOR_FORMAT_ARGB8565          = 0x13,   /**< Not supported by sw renderer yet. */
    LGFX_LV_COLOR_FORMAT_RGB565A8          = 0x14,   /**< Color array followed by Alpha array*/
    LGFX_LV_COLOR_FORMAT_AL88              = 0x15,   /**< L8 with alpha >*/

    /*3 byte (+alpha) formats*/
    LGFX_LV_COLOR_FORMAT_RGB888            = 0x0F,
    LGFX_LV_COLOR_FORMAT_ARGB8888          = 0x10,
    LGFX_LV_COLOR_FORMAT_XRGB8888          = 0x11,

    /*Formats not supported by software renderer but kept here so GPU can use it*/
    LGFX_LV_COLOR_FORMAT_A1                = 0x0B,
    LGFX_LV_COLOR_FORMAT_A2                = 0x0C,
    LGFX_LV_COLOR_FORMAT_A4                = 0x0D,
    LGFX_LV_COLOR_FORMAT_ARGB1555          = 0x16,
    LGFX_LV_COLOR_FORMAT_ARGB4444          = 0x17,
    LGFX_LV_COLOR_FORMAT_ARGB2222          = 0X18,

    /* reference to https://wiki.videolan.org/YUV/ */
    /*YUV planar formats*/
    LGFX_LV_COLOR_FORMAT_YUV_START         = 0x20,
    LGFX_LV_COLOR_FORMAT_I420              = LGFX_LV_COLOR_FORMAT_YUV_START,  /*YUV420 planar(3 plane)*/
    LGFX_LV_COLOR_FORMAT_I422              = 0x21,  /*YUV422 planar(3 plane)*/
    LGFX_LV_COLOR_FORMAT_I444              = 0x22,  /*YUV444 planar(3 plane)*/
    LGFX_LV_COLOR_FORMAT_I400              = 0x23,  /*YUV400 no chroma channel*/
    LGFX_LV_COLOR_FORMAT_NV21              = 0x24,  /*YUV420 planar(2 plane), UV plane in 'V, U, V, U'*/
    LGFX_LV_COLOR_FORMAT_NV12              = 0x25,  /*YUV420 planar(2 plane), UV plane in 'U, V, U, V'*/

    /*YUV packed formats*/
    LGFX_LV_COLOR_FORMAT_YUY2              = 0x26,  /*YUV422 packed like 'Y U Y V'*/
    LGFX_LV_COLOR_FORMAT_UYVY              = 0x27,  /*YUV422 packed like 'U Y V Y'*/

    LGFX_LV_COLOR_FORMAT_YUV_END           = LGFX_LV_COLOR_FORMAT_UYVY,

    LGFX_LV_COLOR_FORMAT_PROPRIETARY_START = 0x30,

    LGFX_LV_COLOR_FORMAT_NEMA_TSC_START    = LGFX_LV_COLOR_FORMAT_PROPRIETARY_START,
    LGFX_LV_COLOR_FORMAT_NEMA_TSC4         = LGFX_LV_COLOR_FORMAT_NEMA_TSC_START,
    LGFX_LV_COLOR_FORMAT_NEMA_TSC6         = 0x31,
    LGFX_LV_COLOR_FORMAT_NEMA_TSC6A        = 0x32,
    LGFX_LV_COLOR_FORMAT_NEMA_TSC6AP       = 0x33,
    LGFX_LV_COLOR_FORMAT_NEMA_TSC12        = 0x34,
    LGFX_LV_COLOR_FORMAT_NEMA_TSC12A       = 0x35,
    LGFX_LV_COLOR_FORMAT_NEMA_TSC_END      = LGFX_LV_COLOR_FORMAT_NEMA_TSC12A,

    /*Color formats in which LVGL can render*/
// #if LV_COLOR_DEPTH == 1
//     LV_COLOR_FORMAT_NATIVE            = LV_COLOR_FORMAT_I1,
//     LV_COLOR_FORMAT_NATIVE_WITH_ALPHA = LV_COLOR_FORMAT_I1,
// #elif LV_COLOR_DEPTH == 8
//     LV_COLOR_FORMAT_NATIVE            = LV_COLOR_FORMAT_L8,
//     LV_COLOR_FORMAT_NATIVE_WITH_ALPHA = LV_COLOR_FORMAT_AL88,
// #elif LV_COLOR_DEPTH == 16
    LGFX_LV_COLOR_FORMAT_NATIVE            = LGFX_LV_COLOR_FORMAT_RGB565,
    LGFX_LV_COLOR_FORMAT_NATIVE_WITH_ALPHA = LGFX_LV_COLOR_FORMAT_RGB565A8,
// #elif LV_COLOR_DEPTH == 24
//     LV_COLOR_FORMAT_NATIVE            = LV_COLOR_FORMAT_RGB888,
//     LV_COLOR_FORMAT_NATIVE_WITH_ALPHA = LV_COLOR_FORMAT_ARGB8888,
// #elif LV_COLOR_DEPTH == 32
//     LV_COLOR_FORMAT_NATIVE            = LV_COLOR_FORMAT_XRGB8888,
//     LV_COLOR_FORMAT_NATIVE_WITH_ALPHA = LV_COLOR_FORMAT_ARGB8888,
// #else
//   #error "LV_COLOR_DEPTH should be 1, 8, 16, 24 or 32"
// #endif

} lgfx_lv_color_format_t;


/** The bitmaps might be upscaled by 3 to achieve subpixel rendering.*/
typedef enum {
    LGFX_LV_FONT_SUBPX_NONE,
    LGFX_LV_FONT_SUBPX_HOR,
    LGFX_LV_FONT_SUBPX_VER,
    LGFX_LV_FONT_SUBPX_BOTH,
} lgfx_lv_font_subpx_t;

/** Adjust letter spacing for specific character pairs.*/
typedef enum {
    LGFX_LV_FONT_KERNING_NORMAL,
    LGFX_LV_FONT_KERNING_NONE,
} lgfx_lv_font_kerning_t;


/** Format of font character map.*/
typedef enum {
    LGFX_LV_FONT_FMT_TXT_CMAP_FORMAT0_FULL,
    LGFX_LV_FONT_FMT_TXT_CMAP_SPARSE_FULL,
    LGFX_LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY,
    LGFX_LV_FONT_FMT_TXT_CMAP_SPARSE_TINY,
} lgfx_lv_font_fmt_txt_cmap_type_t;

/** The font format.*/
typedef enum {
    LGFX_LV_FONT_GLYPH_FORMAT_NONE   = 0, /**< Maybe not visible*/

    /**< Legacy simple formats with no byte padding at end of the lines*/
    LGFX_LV_FONT_GLYPH_FORMAT_A1     = 0x01, /**< 1 bit per pixel*/
    LGFX_LV_FONT_GLYPH_FORMAT_A2     = 0x02, /**< 2 bit per pixel*/
    LGFX_LV_FONT_GLYPH_FORMAT_A3     = 0x03, /**< 3 bit per pixel*/
    LGFX_LV_FONT_GLYPH_FORMAT_A4     = 0x04, /**< 4 bit per pixel*/
    LGFX_LV_FONT_GLYPH_FORMAT_A8     = 0x08, /**< 8 bit per pixel*/

    /**< Legacy simple formats with byte padding at end of the lines*/
    LGFX_LV_FONT_GLYPH_FORMAT_A1_ALIGNED = 0x011, /**< 1 bit per pixel*/
    LGFX_LV_FONT_GLYPH_FORMAT_A2_ALIGNED = 0x012, /**< 2 bit per pixel*/
    LGFX_LV_FONT_GLYPH_FORMAT_A4_ALIGNED = 0x014, /**< 4 bit per pixel*/
    LGFX_LV_FONT_GLYPH_FORMAT_A8_ALIGNED = 0x018, /**< 8 bit per pixel*/

    LGFX_LV_FONT_GLYPH_FORMAT_IMAGE  = 0x19, /**< Image format*/

    /**< Advanced formats*/
    LGFX_LV_FONT_GLYPH_FORMAT_VECTOR = 0x1A, /**< Vectorial format*/
    LGFX_LV_FONT_GLYPH_FORMAT_SVG    = 0x1B, /**< SVG format*/
    LGFX_LV_FONT_GLYPH_FORMAT_CUSTOM = 0xFF, /**< Custom format*/
} lgfx_lv_font_glyph_format_t;


/** Bitmap formats*/
typedef enum {
    LGFX_LV_FONT_FMT_TXT_PLAIN      = 0,
    LGFX_LV_FONT_FMT_TXT_COMPRESSED = 1,
    LGFX_LV_FONT_FMT_TXT_COMPRESSED_NO_PREFILTER = 2,
    LGFX_LV_FONT_FMT_PLAIN_ALIGNED      = 3,
} lgfx_lv_font_fmt_txt_bitmap_format_t;


#ifdef __cplusplus
}
#endif
