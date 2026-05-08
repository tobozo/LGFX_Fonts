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

#include <vector>
#include <map>


namespace lgfx
{
 inline namespace v1
 {
  namespace emojis
  {

// ========================================================================================

    // A vector will be filled with these, sorted by code
    struct emoji_code_ptr_t
    {
      uint32_t code;
      const emoji_png_t* ptr;
    };

    // Code ranges used for faster lookups
    struct emoji_block_range_t
    {
      uint32_t start;
      uint32_t end;
      uint32_t idx_start;
      uint32_t idx_end;
    };

    // Emoji data description for gfx rendering
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
          if( _loaded || !gfx || !emojis || count==0)
            return false;
          _gfx = gfx;
          _gfx->setEmojiCallback( _draw_cb );
          return true;
        }


        template<std::size_t count>
        static bool loadEmojis(LGFXBase* gfx, const emoji_png_set_t (&emojis_sets)[count]) // emoji sets
        {
          if( _loaded || !gfx || count==0)
            return false;
          _gfx = gfx;
          const emoji_png_group_t groups[] = {{ emojis_sets, count }};
          if( _create_list_from_groups(groups) )
          {
            _gfx->setEmojiCallback( _draw_cb );
            return true;
          }
          return false;
        }

        template<std::size_t count>
        static bool loadEmojis(LGFXBase* gfx, const emoji_png_group_t (&emojis_groups)[count]) // groups sets
        {
          if( _loaded || !gfx || count==0)
            return false;
          _gfx = gfx;
          if( _create_list_from_groups(emojis_groups) )
          {
            _gfx->setEmojiCallback( _draw_cb );
            return true;
          }
          return false;
        }

        // get all loaded emojis
        static const std::vector<emoji_code_ptr_t>& emojis()
        {
          return emojisVec;
        }

        // how many emojis are loaded
        static size_t count()
        {
          return emojisVec.size();
        }


      #if __cplusplus >= 202002L // C++20
        // C++20 warns: "operator[]() may be a static member function only with c++23", seems to work anyway
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wc++23-extensions"

        static const emoji_desc_t* operator [](uint32_t code) // lookup by code
        {
          return _lookup(code);
        }

        #pragma GCC diagnostic pop
      #endif

      private:

        static const emoji_desc_t* _lookup(uint32_t code);
        static int32_t _draw_cb(lgfx::LGFXBase* gfx, int32_t x, int32_t y, uint32_t code, int32_t font_height);

        static bool _create_list_from_groups(const emoji_png_group_t* emojis_groups, size_t groups_count);

        template<std::size_t groups_count>
        static bool _create_list_from_groups(const emoji_png_group_t (&emojis_groups)[groups_count])
        {
          return _create_list_from_groups(emojis_groups, groups_count);
        }

        static std::vector<emoji_code_ptr_t> emojisVec;
        static std::vector<emoji_block_range_t> rangedCodes;

        static LGFXBase* _gfx;

        static bool _loaded;
    };

// ========================================================================================


  } // namespace emojis

  using namespace emojis;

 } // namespave v1
} // namespace lgfx
