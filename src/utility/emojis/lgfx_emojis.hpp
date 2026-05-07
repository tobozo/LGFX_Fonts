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

#include "../../Fonts/emojis/emojis.h"


namespace lgfx
{
 inline namespace v1
 {
  namespace emojis
  {

    // emoji data description for gfx rendering
    struct emoji_desc_t
    {
      uint32_t code = 0;
      uint8_t* data = nullptr;
      uint32_t len = 0;
      int16_t png_w = 0;
      int16_t png_h = 0; // 0 = file missing / invalid
    };


    class LGFX_Emojis
    {
      public:

        LGFX_Emojis() {}

        template<std::size_t count>
        static bool loadEmojis(LGFXBase* gfx, const emoji_png_t (&emojis)[count]) // emoji set
        {
          if( LGFX_Emojis::_loaded || !gfx || !emojis || count==0)
            return false;
          LGFX_Emojis::_gfx = gfx;
          LGFX_Emojis::emojisPtr   = (emoji_png_t*)emojis;
          LGFX_Emojis::emojisCount = count;
          // Serial.printf("%d emojis\n", LGFX_Emojis::emojisCount);
          gfx->setEmojiCallback( LGFX_Emojis::_draw_cb );
          return true;
        }


        template<std::size_t count>
        static bool loadEmojis(LGFXBase* gfx, const emoji_png_set_t (&emojis_sets)[count]) // emoji sets
        {
          if( LGFX_Emojis::_loaded || !gfx || count==0)
            return false;
          LGFX_Emojis::_gfx = gfx;
          const emoji_png_group_t groups[] = {{ emojis_sets, count }};
          if( LGFX_Emojis::_create_list_from_groups(groups) )
          {
            gfx->setEmojiCallback( LGFX_Emojis::_draw_cb );
            return true;
          }
          return false;
        }

        template<std::size_t count>
        static bool loadEmojis(LGFXBase* gfx, const emoji_png_group_t (&emojis_groups)[count]) // groups sets
        {
          if( LGFX_Emojis::_loaded || !gfx || count==0)
            return false;
          LGFX_Emojis::_gfx = gfx;
          if( LGFX_Emojis::_create_list_from_groups(emojis_groups) )
          {
            gfx->setEmojiCallback( LGFX_Emojis::_draw_cb );
            return true;
          }
          return false;
        }

        static const emoji_png_t* emojis()
        {
          return LGFX_Emojis::emojisPtr;
        }
        static size_t count()
        {
          return LGFX_Emojis::emojisCount;
        }


      private:

        static const emoji_desc_t* _lookup(uint32_t code);
        static int32_t _draw_cb(lgfx::LGFXBase* gfx, int32_t x, int32_t y, uint32_t code, int32_t font_height);

        static bool _create_list_from_groups(const emoji_png_group_t* emojis_groups, size_t groups_count);

        template<std::size_t groups_count>
        static bool _create_list_from_groups(const emoji_png_group_t (&emojis_groups)[groups_count])
        {
          return LGFX_Emojis::_create_list_from_groups(emojis_groups, groups_count);
        }

        static const emoji_png_t* emojisPtr;
        static size_t emojisCount;
        static LGFXBase* _gfx;

        static bool _alloc;
        static bool _loaded;


    };




  } // namespace emojis

  using namespace emojis;

  //inline static LGFX_Emojis emojisLoader;

 } // namespave v1
} // namespace lgfx
