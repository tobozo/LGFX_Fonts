#pragma once

#ifdef __cplusplus
extern "C" {
#endif


#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "./lvgl_font_enums.h"
#include "./lvgl_font_structs.h"


/**
 * Used as `get_glyph_bitmap` callback in lvgl's native font format if the font is uncompressed.
 * @param g_dsc         the glyph descriptor including which font to use, which supply the glyph_index and format.
 * @param draw_buf      a draw buffer that can be used to store the bitmap of the glyph, it's OK not to use it.
 * @return pointer to an A8 bitmap (not necessarily bitmap_out) or NULL if `unicode_letter` not found
 */
const void * lgfx_lv_font_get_bitmap_fmt_txt(lgfx_lv_font_glyph_dsc_t * g_dsc, lgfx_lv_draw_buf_t * draw_buf);

/**
 * Used as `get_glyph_dsc` callback in lvgl's native font format if the font is uncompressed.
 * @param font pointer to font
 * @param dsc_out store the result descriptor here
 * @param unicode_letter a UNICODE letter code
 * @param unicode_letter_next the unicode letter succeeding the letter under test
 * @return true: descriptor is successfully loaded into `dsc_out`.
 *         false: the letter was not found, no data is loaded to `dsc_out`
 */
bool lgfx_lv_font_get_glyph_dsc_fmt_txt(const lgfx_lv_font_t * font, lgfx_lv_font_glyph_dsc_t * dsc_out, uint32_t unicode_letter,
                                   uint32_t unicode_letter_next);


extern const lgfx_lv_font_t lgfx_lv_font_montserrat_8;
extern const lgfx_lv_font_t lgfx_lv_font_montserrat_10;
extern const lgfx_lv_font_t lgfx_lv_font_montserrat_12;
extern const lgfx_lv_font_t lgfx_lv_font_montserrat_14;
extern const lgfx_lv_font_t lgfx_lv_font_montserrat_16;
extern const lgfx_lv_font_t lgfx_lv_font_montserrat_18;
extern const lgfx_lv_font_t lgfx_lv_font_montserrat_20;
extern const lgfx_lv_font_t lgfx_lv_font_montserrat_22;
extern const lgfx_lv_font_t lgfx_lv_font_montserrat_24;
extern const lgfx_lv_font_t lgfx_lv_font_montserrat_26;
extern const lgfx_lv_font_t lgfx_lv_font_montserrat_28;
extern const lgfx_lv_font_t lgfx_lv_font_montserrat_30;
extern const lgfx_lv_font_t lgfx_lv_font_montserrat_32;
extern const lgfx_lv_font_t lgfx_lv_font_montserrat_34;
extern const lgfx_lv_font_t lgfx_lv_font_montserrat_36;
extern const lgfx_lv_font_t lgfx_lv_font_montserrat_38;
extern const lgfx_lv_font_t lgfx_lv_font_montserrat_40;
extern const lgfx_lv_font_t lgfx_lv_font_montserrat_42;
extern const lgfx_lv_font_t lgfx_lv_font_montserrat_44;
extern const lgfx_lv_font_t lgfx_lv_font_montserrat_46;
extern const lgfx_lv_font_t lgfx_lv_font_montserrat_48;
extern const lgfx_lv_font_t lgfx_lv_font_simsun_14_cjk;
extern const lgfx_lv_font_t lgfx_lv_font_simsun_16_cjk;
extern const lgfx_lv_font_t lgfx_lv_font_unscii_8;
extern const lgfx_lv_font_t lgfx_lv_font_unscii_16;

#ifdef __cplusplus
}
#endif
