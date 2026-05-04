#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "./lvgl_font_enums.h"

// forward declarations
typedef struct _lgfx_lv_font_t lgfx_lv_font_t;
typedef struct _lgfx_lv_draw_buf_handlers_t lgfx_lv_draw_buf_handlers_t;
typedef struct _lgfx_lv_draw_buf_t lgfx_lv_draw_buf_t;

/** Represents an area of the screen.*/
typedef struct {
    int32_t x1;
    int32_t y1;
    int32_t x2;
    int32_t y2;
} lgfx_lv_area_t;


#ifdef ARCH_CPU_BIG_ENDIAN
  typedef struct {
      uint32_t reserved_2: 16;    /**< Reserved to be used later*/
      uint32_t stride: 16;        /**< Number of bytes in a row*/
      uint32_t h: 16;
      uint32_t w: 16;
      uint32_t flags: 16;         /**< Image flags, see `lgfx_lv_image_flags_t`*/
      uint32_t cf : 8;            /**< Color format: See `lgfx_lv_color_format_t`*/
      uint32_t magic: 8;          /**< Magic number. Must be LV_IMAGE_HEADER_MAGIC*/
  } lgfx_lv_image_header_t;
#else
  typedef struct {
      uint32_t magic: 8;          /**< Magic number. Must be LV_IMAGE_HEADER_MAGIC*/
      uint32_t cf : 8;            /**< Color format: See `lgfx_lv_color_format_t`*/
      uint32_t flags: 16;         /**< Image flags, see `lgfx_lv_image_flags_t`*/

      uint32_t w: 16;
      uint32_t h: 16;
      uint32_t stride: 16;        /**< Number of bytes in a row*/
      uint32_t reserved_2: 16;    /**< Reserved to be used later*/
  } lgfx_lv_image_header_t;
#endif

struct _lgfx_lv_draw_buf_t {
    lgfx_lv_image_header_t header;
    uint32_t data_size;       /**< Total buf size in bytes */
    uint8_t * data;
    void * unaligned_data;    /**< Unaligned address of `data`, used internally by lvgl */
    const lgfx_lv_draw_buf_handlers_t * handlers; /**< draw buffer alloc/free ops. */
};

/** This describes a glyph.*/
typedef struct {
//#if LV_FONT_FMT_TXT_LARGE == 0
    uint32_t bitmap_index : 20;     /**< Start index of the bitmap. A font can be max 1 MB.*/
    uint32_t adv_w : 12;            /**< Draw the next glyph after this width. 8.4 format (real_value * 16 is stored).*/
    uint8_t box_w;                  /**< Width of the glyph's bounding box*/
    uint8_t box_h;                  /**< Height of the glyph's bounding box*/
    int8_t ofs_x;                   /**< x offset of the bounding box*/
    int8_t ofs_y;                   /**< y offset of the bounding box. Measured from the top of the line*/
// #else
//     uint32_t bitmap_index;          /**< Start index of the bitmap. A font can be max 4 GB.*/
//     uint32_t adv_w;                 /**< Draw the next glyph after this width. 28.4 format (real_value * 16 is stored).*/
//     uint16_t box_w;                 /**< Width of the glyph's bounding box*/
//     uint16_t box_h;                 /**< Height of the glyph's bounding box*/
//     int16_t ofs_x;                  /**< x offset of the bounding box*/
//     int16_t ofs_y;                  /**< y offset of the bounding box. Measured from the top of the line*/
// #endif
} lgfx_lv_font_fmt_txt_glyph_dsc_t;




/** Describes the properties of a glyph.*/
typedef struct {
    const lgfx_lv_font_t *
    resolved_font;  /**< Pointer to a font where the glyph was actually found after handling fallbacks*/
    uint16_t adv_w; /**< The glyph needs this space. Draw the next glyph after this width.*/
    uint16_t box_w; /**< Width of the glyph's bounding box*/
    uint16_t box_h; /**< Height of the glyph's bounding box*/
    int16_t ofs_x;  /**< x offset of the bounding box*/
    int16_t ofs_y;  /**< y offset of the bounding box*/
    lgfx_lv_font_glyph_format_t format;  /**< Font format of the glyph see lgfx_lv_font_glyph_format_t */
    uint8_t is_placeholder: 1;      /**< Glyph is missing. But placeholder will still be displayed*/

    /** 0: Get bitmap should return an A8 or ARGB8888 image.
     * 1: return the bitmap as it is (Maybe A1/2/4 or any proprietary formats). */
    uint8_t req_raw_bitmap: 1;

    union {
        uint32_t index;       /**< Unicode code point*/
        const void * src;     /**< Pointer to the source data used by image fonts*/
    } gid;                    /**< The index of the glyph in the font file. Used by the font cache*/
    void * entry; //lgfx_lv_cache_entry_t * entry; /**< The cache entry of the glyph draw data. Used by the font cache*/
    uint8_t bpp;
} lgfx_lv_font_glyph_dsc_t;



/** Describe the properties of a font*/
struct _lgfx_lv_font_t {
    /** Get a glyph's descriptor from a font*/
    bool (*get_glyph_dsc)(const lgfx_lv_font_t * font, lgfx_lv_font_glyph_dsc_t * dsc_out, uint32_t unicode_letter, uint32_t unicode_letter_next);

    /** Get a glyph's bitmap from a font*/
    const void * (*get_glyph_bitmap)(lgfx_lv_font_glyph_dsc_t * g_dsc, lgfx_lv_draw_buf_t * draw_buf);

    /** Release a glyph*/
    void (*release_glyph)(const lgfx_lv_font_t *, lgfx_lv_font_glyph_dsc_t *);

    /*Pointer to the font in a font pack (must have the same line height)*/
    int32_t line_height;         /**< The real line height where any text fits*/
    int32_t base_line;           /**< Base line measured from the bottom of the line_height*/
    uint8_t subpx   : 2;            /**< An element of `lgfx_lv_font_subpx_t`*/
    uint8_t kerning : 1;            /**< An element of `lgfx_lv_font_kerning_t`*/

    int8_t underline_position;      /**< Distance between the top of the underline and base line (< 0 means below the base line)*/
    int8_t underline_thickness;     /**< Thickness of the underline*/

    const void * dsc;               /**< Store implementation specific or run_time data or caching here*/
    const lgfx_lv_font_t * fallback;   /**< Fallback font for missing glyph. Resolved recursively */
    void * user_data;               /**< Custom user data for font.*/
};



/**
 * Map codepoints to a `glyph_dsc`s
 * Several formats are supported to optimize memory usage
 * See https://github.com/lvgl/lgfx_lv_font_conv/blob/master/doc/font_spec.md
 */
typedef struct {
    /** First Unicode character for this range*/
    uint32_t range_start;

    /** Number of Unicode characters related to this range.
     * Last Unicode character = range_start + range_length - 1*/
    uint16_t range_length;

    /** First glyph ID (array index of `glyph_dsc`) for this range*/
    uint16_t glyph_id_start;

    /*
    According the specification there are 4 formats:
        https://github.com/lvgl/lgfx_lv_font_conv/blob/master/doc/font_spec.md

    For simplicity introduce "relative code point":
        rcp = codepoint - range_start

    and a search function:
        search a "value" in an "array" and returns the index of "value".

    Format 0 tiny
        unicode_list == NULL && glyph_id_ofs_list == NULL
        glyph_id = glyph_id_start + rcp

    Format 0 full
        unicode_list == NULL && glyph_id_ofs_list != NULL
        glyph_id = glyph_id_start + glyph_id_ofs_list[rcp]

    Sparse tiny
        unicode_list != NULL && glyph_id_ofs_list == NULL
        glyph_id = glyph_id_start + search(unicode_list, rcp)

    Sparse full
        unicode_list != NULL && glyph_id_ofs_list != NULL
        glyph_id = glyph_id_start + glyph_id_ofs_list[search(unicode_list, rcp)]
    */

    const uint16_t * unicode_list;

    /** if(type == LV_FONT_FMT_TXT_CMAP_FORMAT0_...) it's `uint8_t *`
     * if(type == LV_FONT_FMT_TXT_CMAP_SPARSE_...)  it's `uint16_t *`
     */
    const void * glyph_id_ofs_list;

    /** Length of `unicode_list` and/or `glyph_id_ofs_list`*/
    uint16_t list_length;

    /** Type of this character map*/
    lgfx_lv_font_fmt_txt_cmap_type_t type;
} lgfx_lv_font_fmt_txt_cmap_t;

/** A simple mapping of kern values from pairs*/
typedef struct {
    /*To get a kern value of two code points:
       1. Get the `glyph_id_left` and `glyph_id_right` from `lgfx_lv_font_fmt_txt_cmap_t
       2. for(i = 0; i < pair_cnt * 2; i += 2)
             if(glyph_ids[i] == glyph_id_left &&
                glyph_ids[i+1] == glyph_id_right)
                 return values[i / 2];
     */
    const void * glyph_ids;
    const int8_t * values;
    uint32_t pair_cnt   : 30;
    uint32_t glyph_ids_size : 2;    /**< 0: `glyph_ids` is stored as `uint8_t`; 1: as `uint16_t` */
} lgfx_lv_font_fmt_txt_kern_pair_t;

/** More complex but more optimal class based kern value storage*/
typedef struct {
    /*To get a kern value of two code points:
          1. Get the `glyph_id_left` and `glyph_id_right` from `lgfx_lv_font_fmt_txt_cmap_t
          2. Get the class of the left and right glyphs as `left_class` and `right_class`
              left_class = left_class_mapping[glyph_id_left];
              right_class = right_class_mapping[glyph_id_right];
          3. value = class_pair_values[(left_class-1)*right_class_cnt + (right_class-1)]
        */

    const int8_t * class_pair_values;     /**< left_class_cnt * right_class_cnt value */
    const uint8_t * left_class_mapping;   /**< Map the glyph_ids to classes: index -> glyph_id -> class_id */
    const uint8_t * right_class_mapping;  /**< Map the glyph_ids to classes: index -> glyph_id -> class_id */
    uint8_t left_class_cnt;
    uint8_t right_class_cnt;
} lgfx_lv_font_fmt_txt_kern_classes_t;



/** Describe store for additional data for fonts */
typedef struct {
    /** The bitmaps of all glyphs */
    const uint8_t * glyph_bitmap;

    /** Describe the glyphs */
    const lgfx_lv_font_fmt_txt_glyph_dsc_t * glyph_dsc;

    /** Map the glyphs to Unicode characters.
     *Array of `lgfx_lv_font_cmap_fmt_txt_t` variables */
    const lgfx_lv_font_fmt_txt_cmap_t * cmaps;

    /**
     * Store kerning values.
     * Can be `lgfx_lv_font_fmt_txt_kern_pair_t *  or `lgfx_lv_font_kern_classes_fmt_txt_t *`
     * depending on `kern_classes`
     */
    const void * kern_dsc;

    /** Scale kern values in 12.4 format */
    uint16_t kern_scale;

    /** Number of cmap tables */
    uint16_t cmap_num       : 9;

    /** Bit per pixel: 1, 2, 3, 4, 8 */
    uint16_t bpp            : 4;

    /** Type of `kern_dsc` */
    uint16_t kern_classes   : 1;

    /**
     * storage format of the bitmap
     * from `lgfx_lv_font_fmt_txt_bitmap_format_t`
     */
    uint16_t bitmap_format  : 2;
} lgfx_lv_font_fmt_txt_dsc_t;


#ifdef __cplusplus
}
#endif
