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

#pragma once

#if __has_include(<LovyanGFX.hpp>)
  #include <LovyanGFX.hpp>
#elif __has_include(<M5GFX.h>)
  #include <M5GFX.h>
#else
  #error "Include LovyanGFX or M5FX first!"
#endif

#include "./lvgl_font_support.h"

#if __has_include(<lvgl.h>)
  #include <lvgl.h>
#endif

namespace lgfx
{
 inline namespace v1
 {

//----------------------------------------------------------------------------
// LVGL font wrapper

#if !defined M5GFX_LVGL_INTERNAL_H

  struct LVGLfont : public IFont
  {
    constexpr LVGLfont(const lgfx_lv_font_t* font = nullptr) : _font(font) {}

    font_type_t getType(void) const override { return ft_lvgl; }
    void getDefaultMetric(FontMetrics *metrics) const override;
    bool updateFontMetric(FontMetrics *metrics, uint16_t uniCode) const override;
    size_t drawChar(LGFXBase* gfx, int32_t x, int32_t y, uint16_t c, const TextStyle* style, FontMetrics* metrics, int32_t& filled_x) const override;

    const lgfx_lv_font_t* _font;
  };


//----------------------------------------------------------------------------

  namespace fonts
  {
    extern const lgfx::LVGLfont lvFontMontserrat10;
    extern const lgfx::LVGLfont lvFontMontserrat12;
    extern const lgfx::LVGLfont lvFontMontserrat14;
    extern const lgfx::LVGLfont lvFontMontserrat16;
    extern const lgfx::LVGLfont lvFontMontserrat18;
    extern const lgfx::LVGLfont lvFontMontserrat20;
    extern const lgfx::LVGLfont lvFontMontserrat22;
    extern const lgfx::LVGLfont lvFontMontserrat24;
    extern const lgfx::LVGLfont lvFontMontserrat26;
    extern const lgfx::LVGLfont lvFontMontserrat28;
    extern const lgfx::LVGLfont lvFontMontserrat30;
    extern const lgfx::LVGLfont lvFontMontserrat32;
    extern const lgfx::LVGLfont lvFontMontserrat34;
    extern const lgfx::LVGLfont lvFontMontserrat36;
    extern const lgfx::LVGLfont lvFontMontserrat38;
    extern const lgfx::LVGLfont lvFontMontserrat40;
    extern const lgfx::LVGLfont lvFontMontserrat42;
    extern const lgfx::LVGLfont lvFontMontserrat44;
    extern const lgfx::LVGLfont lvFontMontserrat46;
    extern const lgfx::LVGLfont lvFontMontserrat48;
    extern const lgfx::LVGLfont lvFontMontserrat8;
    extern const lgfx::LVGLfont lvFontSimsun14Cjk;
    extern const lgfx::LVGLfont lvFontSimsun16Cjk;
    extern const lgfx::LVGLfont lvFontUnscii16;
    extern const lgfx::LVGLfont lvFontUnscii8;
  }

#endif

 }
}
