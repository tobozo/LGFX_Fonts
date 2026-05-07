/*\
 *
  LGFX_Fonts - External fonts support for LovyanGFX/M5GFX

  Original Source:
  https://github.com/tobozo/LGFX_Fonts

  Licence:
  [Multiple](https://github.com/tobozo/LGFX_Fonts/blob/master/LICENSE.txt)

  Author:
  [tobozo](https://github.com/tobozo)

  Contributors:
  [ciniml](https://github.com/ciniml)
  [mongonta0716](https://github.com/mongonta0716)
  [lovyan03](https://twitter.com/lovyan03)

\*/

#include "./lgfx_lvgl_fonts.hpp"



namespace lgfx
{
 inline namespace v1
 {

//----------------------------------------------------------------------------


#if !defined M5GFX_LVGL_INTERNAL_H

  void LVGLfont::getDefaultMetric(FontMetrics *metrics) const
  {
    if (_font == nullptr)
    {
      metrics->width = 0;
      metrics->x_advance = 0;
      metrics->x_offset = 0;
      metrics->height = 0;
      metrics->y_advance = 0;
      metrics->y_offset = 0;
      metrics->baseline = 0;
      return;
    }

    metrics->height = _font->line_height;
    metrics->y_advance = _font->line_height;
    metrics->baseline = _font->line_height - _font->base_line;
    metrics->y_offset = -metrics->baseline;
    metrics->width = (_font->line_height * 5) >> 3;
    metrics->x_advance = metrics->width;
    metrics->x_offset = 0;
  }

  bool LVGLfont::updateFontMetric(FontMetrics *metrics, uint16_t uniCode) const
  {
    if (_font == nullptr || _font->get_glyph_dsc == nullptr)
    {
      metrics->x_offset = 0;
      metrics->width = metrics->x_advance = 0;
      return false;
    }

    lgfx_lv_font_glyph_dsc_t gd;
    if (!lgfx_lv_font_get_glyph_dsc_fmt_txt(_font, &gd, uniCode, 0))
    {
      metrics->x_offset = 0;
      metrics->width = metrics->x_advance = (metrics->height * 5) >> 3;
      return false;
    }

    metrics->x_offset = gd.ofs_x;
    metrics->width = gd.box_w;
    metrics->x_advance = gd.adv_w;
    return true;
  }

  static size_t draw_alpha_bitmap_common(
      LGFXBase* gfx,
      int32_t x,
      int32_t y,
      const TextStyle* style,
      FontMetrics* metrics,
      int32_t& filled_x,
      int32_t xAdvance,
      int32_t xoffset,
      int32_t yoffset,
      uint32_t box_w,
      uint32_t box_h,
      const uint8_t* bitmap,
      uint32_t glyph_stride,
      uint32_t alpha_max)
  {
    int32_t sy = 65536 * style->size_y;
    int32_t sx = 65536 * style->size_x;

    auto cc = gfx->getColorConverter();
    uint32_t col_back = cc->convert(style->back_rgb888);
    uint32_t col_fore = cc->convert(style->fore_rgb888);
    bool fillbg = (style->back_rgb888 != style->fore_rgb888);
    int32_t glyph_w_scaled = (box_w * sx) >> 16;

    int32_t left = 0;
    int32_t right = 0;
    if (fillbg)
    {
      left  = std::max<int>(filled_x, x + (xoffset < 0 ? xoffset : 0));
      right = x + std::max<int>(glyph_w_scaled + xoffset, xAdvance);
      filled_x = right;
    }

    int32_t draw_x = x + xoffset;

    uint32_t back_rgb = fillbg ? style->back_rgb888 : gfx->getBaseColor();
    int32_t fore_r = (style->fore_rgb888 >> 16) & 0xFF;
    int32_t fore_g = (style->fore_rgb888 >> 8) & 0xFF;
    int32_t fore_b = style->fore_rgb888 & 0xFF;
    int32_t back_r = (back_rgb >> 16) & 0xFF;
    int32_t back_g = (back_rgb >> 8) & 0xFF;
    int32_t back_b = back_rgb & 0xFF;

    gfx->startWrite();

    if (fillbg && left < right)
    {
      gfx->setRawColor(col_back);
      if (yoffset > 0)
      {
        gfx->writeFillRect(left, y, right - left, (yoffset * sy) >> 16);
      }
      int32_t y0 = ((yoffset + (int32_t)box_h) * sy) >> 16;
      int32_t y1 = (metrics->height * sy) >> 16;
      if (y0 < y1)
      {
        gfx->writeFillRect(left, y + y0, right - left, y1 - y0);
      }
    }

    if (bitmap != nullptr && box_w && box_h)
    {
      for (uint32_t py = 0; py < box_h; ++py)
      {
        int32_t y0 = ((yoffset + (int32_t)py) * sy) >> 16;
        int32_t y1 = ((yoffset + (int32_t)py + 1) * sy) >> 16;
        if (y1 <= y0)
        {
          continue;
        }

        if (fillbg && left < right)
        {
          gfx->setRawColor(col_back);
          if (left < draw_x)
          {
            gfx->writeFillRect(left, y + y0, draw_x - left, y1 - y0);
          }
          int32_t draw_right = draw_x + glyph_w_scaled;
          if (draw_right < right)
          {
            gfx->writeFillRect(draw_right, y + y0, right - draw_right, y1 - y0);
          }
        }

        for (uint32_t px = 0; px < box_w; ++px)
        {
          uint32_t alpha = bitmap[py * glyph_stride + px];

          if (!fillbg && alpha == 0)
          {
            continue;
          }

          int32_t x0 = ((int32_t)px * sx) >> 16;
          int32_t x1 = (((int32_t)px + 1) * sx) >> 16;
          if (x1 <= x0)
          {
            continue;
          }

          uint32_t raw;
          if (alpha == 0)
          {
            raw = col_back;
          }
          else if (alpha >= alpha_max)
          {
            raw = col_fore;
          }
          else
          {
            int32_t r = back_r + ((fore_r - back_r) * (int32_t)alpha + (int32_t)(alpha_max >> 1)) / (int32_t)alpha_max;
            int32_t g = back_g + ((fore_g - back_g) * (int32_t)alpha + (int32_t)(alpha_max >> 1)) / (int32_t)alpha_max;
            int32_t b = back_b + ((fore_b - back_b) * (int32_t)alpha + (int32_t)(alpha_max >> 1)) / (int32_t)alpha_max;
            raw = cc->convert(((uint32_t)r << 16) | ((uint32_t)g << 8) | (uint32_t)b);
          }
          gfx->setRawColor(raw);
          gfx->writeFillRect(draw_x + x0, y + y0, x1 - x0, y1 - y0);
        }
      }
    }

    gfx->endWrite();
    return xAdvance;
  }

  size_t LVGLfont::drawChar(LGFXBase* gfx, int32_t x, int32_t y, uint16_t uniCode, const TextStyle* style, FontMetrics* metrics, int32_t& filled_x) const
  {
    if (_font == nullptr || _font->get_glyph_dsc == nullptr || _font->get_glyph_bitmap == nullptr)
    {
      return drawCharDummy(gfx, x, y, metrics->x_advance, metrics->height, style, filled_x);
    }

    int32_t sy = 65536 * style->size_y;
    int32_t sx = 65536 * style->size_x;
    y += (metrics->y_offset * sy) >> 16;

    lgfx_lv_font_glyph_dsc_t gd;
    if (!lgfx_lv_font_get_glyph_dsc_fmt_txt(_font, &gd, uniCode, 0))
    {
      return drawCharDummy(gfx, x, y, metrics->x_advance, metrics->height, style, filled_x);
    }

    int32_t adv_px = gd.adv_w;
    int32_t xAdvance = (adv_px * sx) >> 16;
    int32_t xoffset = (gd.ofs_x * sx) >> 16;

    /*
     * Space-like glyphs can have valid metrics but no bitmap payload.
     * Do not fallback to drawCharDummy, keep LVGL-like spacing behavior.
     */
    if (gd.box_w == 0 || gd.box_h == 0)
    {
      bool fillbg = (style->back_rgb888 != style->fore_rgb888);
      if (fillbg)
      {
        int32_t left  = std::max<int>(filled_x, x);
        int32_t right = x + xAdvance;
        if (left < right)
        {
          uint32_t col_back = gfx->getColorConverter()->convert(style->back_rgb888);
          gfx->startWrite();
          gfx->setRawColor(col_back);
          gfx->writeFillRect(left, y, right - left, (metrics->height * sy) >> 16);
          gfx->endWrite();
        }
        filled_x = right;
      }
      return xAdvance;
    }

    gd.req_raw_bitmap = 0;
    gd.resolved_font = _font;
    uint32_t glyph_stride = gd.box_w;
    uint32_t glyph_stride_alloc = ((gd.box_w + 63U) / 64U) * 64U;
    if (glyph_stride_alloc < gd.box_w) glyph_stride_alloc = gd.box_w;
    const uint8_t stride_sentinel = 0xA5;
    std::vector<uint8_t> glyph_buf(glyph_stride_alloc * gd.box_h, stride_sentinel);
    lgfx_lv_draw_buf_t draw_buf{};
    draw_buf.data = glyph_buf.data();
    const void* bmp_res = lgfx_lv_font_get_bitmap_fmt_txt(&gd, &draw_buf);
    const uint8_t* bitmap = draw_buf.data;
    if (bmp_res == nullptr || bitmap == nullptr)
    {
      return drawCharDummy(gfx, x, y, metrics->x_advance, metrics->height, style, filled_x);
    }

    uint8_t glyph_bpp = 8;
    // NOTE: LV_FONT_GLYPH_FORMAT_* are enum values (see lv_font/font.h),
    //       not preprocessor macros, so they cannot be #ifdef'd.
    switch (gd.format)
    {
      case LGFX_LV_FONT_GLYPH_FORMAT_A1:
      case LGFX_LV_FONT_GLYPH_FORMAT_A1_ALIGNED:
        glyph_bpp = 1;
        break;
      case LGFX_LV_FONT_GLYPH_FORMAT_A2:
      case LGFX_LV_FONT_GLYPH_FORMAT_A2_ALIGNED:
        glyph_bpp = 2;
        break;
      case LGFX_LV_FONT_GLYPH_FORMAT_A4:
      case LGFX_LV_FONT_GLYPH_FORMAT_A4_ALIGNED:
        glyph_bpp = 4;
        break;
      default:
        glyph_bpp = 8;
        break;
    }

    if (gd.box_w > 0 && gd.box_h > 0)
    {
      auto is_quantized_alpha = [glyph_bpp](uint8_t a) -> bool {
        if (glyph_bpp >= 8) return true;
        if (glyph_bpp == 1) return (a == 0 || a == 255);
        if (glyph_bpp == 2) return (a == 0 || a == 85 || a == 170 || a == 255);
        return ((a % 17) == 0);
      };

      auto score_stride = [&](uint32_t test_stride) -> uint32_t {
        if (test_stride < gd.box_w || test_stride > glyph_stride_alloc) return 0;

        uint32_t q_score = 0;
        uint32_t payload_written = 0;
        uint32_t pad_untouched = 0;
        uint32_t payload_total = gd.box_w * gd.box_h;
        uint32_t pad_total = (test_stride - gd.box_w) * gd.box_h;

        for (uint32_t py = 0; py < gd.box_h; ++py)
        {
          const uint8_t* row = bitmap + py * test_stride;
          for (uint32_t px = 0; px < gd.box_w; ++px)
          {
            uint8_t v = row[px];
            if (is_quantized_alpha(v)) ++q_score;
            if (v != stride_sentinel) ++payload_written;
          }
          for (uint32_t px = gd.box_w; px < test_stride; ++px)
          {
            if (row[px] == stride_sentinel) ++pad_untouched;
          }
        }

        /*
         * Score terms (ratio-based to avoid bias to larger stride):
         * 1) payload_written ratio: should be high for the true stride
         * 2) padding_untouched ratio: should be high only when row step is correct
         * 3) quantized alpha count: tie breaker for low-bpp fonts
         */
        uint32_t payload_score = payload_total ? (payload_written * 1024U / payload_total) : 0;
        uint32_t pad_score = pad_total ? (pad_untouched * 1024U / pad_total) : 1024U;
        return (payload_score << 12) + (pad_score << 2) + q_score;
      };

      const uint32_t candidates[] = {
        gd.box_w,
        (uint32_t)((gd.box_w + 1U) & ~1U),
        (uint32_t)((gd.box_w + 3U) & ~3U),
        (uint32_t)((gd.box_w + 7U) & ~7U),
        (uint32_t)((gd.box_w + 15U) & ~15U),
        (uint32_t)((gd.box_w + 31U) & ~31U),
        (uint32_t)((gd.box_w + 63U) & ~63U)
      };

      uint32_t best_stride = gd.box_w;
      uint32_t best_score = score_stride(best_stride);
      for (size_t ci = 0; ci < sizeof(candidates) / sizeof(candidates[0]); ++ci)
      {
        uint32_t s = candidates[ci];
        if (s == best_stride) continue;
        uint32_t sc = score_stride(s);
        if (sc > best_score)
        {
          best_score = sc;
          best_stride = s;
        }
      }
      glyph_stride = best_stride;
    }

    int32_t yoffset = metrics->baseline - (gd.ofs_y + gd.box_h);
    return draw_alpha_bitmap_common(
        gfx,
        x,
        y,
        style,
        metrics,
        filled_x,
        xAdvance,
        xoffset,
        yoffset,
        gd.box_w,
        gd.box_h,
        bitmap,
        glyph_stride,
        255U);
  }


//----------------------------------------------------------------------------
  namespace fonts
  {
    using namespace lgfx;

    const LVGLfont lvFontMontserrat10 = {&lgfx_lv_font_montserrat_10};
    const LVGLfont lvFontMontserrat12 = {&lgfx_lv_font_montserrat_12};
    const LVGLfont lvFontMontserrat14 = {&lgfx_lv_font_montserrat_14};
    const LVGLfont lvFontMontserrat16 = {&lgfx_lv_font_montserrat_16};
    const LVGLfont lvFontMontserrat18 = {&lgfx_lv_font_montserrat_18};
    const LVGLfont lvFontMontserrat20 = {&lgfx_lv_font_montserrat_20};
    const LVGLfont lvFontMontserrat22 = {&lgfx_lv_font_montserrat_22};
    const LVGLfont lvFontMontserrat24 = {&lgfx_lv_font_montserrat_24};
    const LVGLfont lvFontMontserrat26 = {&lgfx_lv_font_montserrat_26};
    const LVGLfont lvFontMontserrat28 = {&lgfx_lv_font_montserrat_28};
    const LVGLfont lvFontMontserrat30 = {&lgfx_lv_font_montserrat_30};
    const LVGLfont lvFontMontserrat32 = {&lgfx_lv_font_montserrat_32};
    const LVGLfont lvFontMontserrat34 = {&lgfx_lv_font_montserrat_34};
    const LVGLfont lvFontMontserrat36 = {&lgfx_lv_font_montserrat_36};
    const LVGLfont lvFontMontserrat38 = {&lgfx_lv_font_montserrat_38};
    const LVGLfont lvFontMontserrat40 = {&lgfx_lv_font_montserrat_40};
    const LVGLfont lvFontMontserrat42 = {&lgfx_lv_font_montserrat_42};
    const LVGLfont lvFontMontserrat44 = {&lgfx_lv_font_montserrat_44};
    const LVGLfont lvFontMontserrat46 = {&lgfx_lv_font_montserrat_46};
    const LVGLfont lvFontMontserrat48 = {&lgfx_lv_font_montserrat_48};
    const LVGLfont lvFontMontserrat8  = {&lgfx_lv_font_montserrat_8};
    const LVGLfont lvFontSimsun14Cjk  = {&lgfx_lv_font_simsun_14_cjk};
    const LVGLfont lvFontSimsun16Cjk  = {&lgfx_lv_font_simsun_16_cjk};
    const LVGLfont lvFontUnscii16     = {&lgfx_lv_font_unscii_16};
    const LVGLfont lvFontUnscii8      = {&lgfx_lv_font_unscii_8};
  }

#endif

 }
}


