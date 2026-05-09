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

// ========================================================================================

    // Emoji runtime storage
    struct emoji_code_ptr_t
    {
      uint32_t code;          // emoji code
      const emoji_png_t* ptr; // pointer to emoji png data in flash
    };

    // Code/Index ranges in emoji_code_ptr_t[], used for faster lookups
    struct emoji_block_range_t
    {
      uint32_t start = 0; // emoji code start
      uint32_t end = 0;   // emoji code end
      uint32_t idx_start = 0; // index start
      uint32_t idx_end = 0;   // index end
    };

    // Emoji data description for final gfx rendering, used in draw callback
    struct emoji_desc_t
    {
      uint32_t code = 0;
      uint8_t* data = nullptr;
      uint32_t len = 0;
      int16_t png_w = 0;
      int16_t png_h = 0; // 0 = file missing / invalid
    };

    typedef const emoji_desc_t* (*emoji_lookup_cb_t)(uint32_t code);

    // Lazy and ugly, but LGFXBase::decodeUTF8() is protected :(
    class UTF8Decoder : public LGFXBase
    {
      public:
        UTF8Decoder(void) = default;
        virtual ~UTF8Decoder(void) = default;
        uint32_t _decodeUTF8(uint8_t c) { return LGFXBase::decodeUTF8(c); }
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
          const emoji_png_set_t emojis_sets[] = {{emojis, count}};
          const emoji_png_group_t emoji_groups[] = {{ emojis_sets, 1 }};
          if( _create_list_from_groups(emoji_groups) ) {
            _gfx->setEmojiCallback( _draw_cb );
            return true;
          }
          return true;
        }


        template<std::size_t count>
        static bool loadEmojis(LGFXBase* gfx, const emoji_png_set_t (&emojis_sets)[count]) // emoji sets
        {
          if( _loaded || !gfx || count==0)
            return false;
          _gfx = gfx;
          const emoji_png_group_t emoji_groups[] = {{ emojis_sets, count }};
          if( _create_list_from_groups(emoji_groups) ) {
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
          if( _create_list_from_groups(emojis_groups) ) {
            _gfx->setEmojiCallback( _draw_cb );
            return true;
          }
          return false;
        }

        // get all loaded emojis
        static const emoji_code_ptr_t* emojis() { return emojisPtr; }

        // get loaded emojis count
        static size_t count() { return emojisCount; }

        // get loaded emojis heap memory footprint
        static size_t allocated() { return emojisAllocSize+rangeCodesAllocSize; }

        // /!\ c++ versions below c++23 will drop the static attribute for operator[]
        #if __cplusplus < 202302L
          // Turn silent warning: "operator[]() may be a static member function only with c++23"
          #pragma GCC diagnostic push
          #pragma GCC diagnostic ignored "-Wc++23-extensions"
        #endif

        // lookup by code
        static const emoji_desc_t* operator [](uint32_t code)
        {
          return _lookup_cb(code);
        }

        // lookup by string
        static const emoji_desc_t* operator [](const char* emoji)
        {
          if(!emoji || !_gfx)
            return _lookup_cb(0);

          auto decoder = (UTF8Decoder*)_gfx;

          uint32_t code = 0;

          do {
            uint32_t uniCode = *emoji;
            do {
              uniCode = decoder->_decodeUTF8(*emoji);
            } while (uniCode < 0x20 && *++emoji);
            if (uniCode < 0x20) break;
            if ((uniCode >= 0xFE00) && (uniCode < 0xFE10)) continue;
            code = uniCode;
          } while (*(++emoji));

          return _lookup_cb(code);
        }

        #if __cplusplus < 202302L
          #pragma GCC diagnostic pop
        #endif

      private:

        static bool _create_list_from_groups(const emoji_png_group_t* emojis_groups, size_t groups_count);

        template<std::size_t groups_count>
        static bool _create_list_from_groups(const emoji_png_group_t (&emojis_groups)[groups_count])
        {
          return _create_list_from_groups(emojis_groups, groups_count);
        }

        static void _emoji_code_ptr_sort(emoji_code_ptr_t* emojisPtr, size_t emojisCount);
        static bool _emoji_code_range_split(emoji_code_ptr_t*emojisPtr, size_t emojisCount);

        static const emoji_desc_t* _lookup(uint32_t code);
        static const emoji_desc_t* _lookup_fast(uint32_t code);

        static emoji_lookup_cb_t _lookup_cb;

        static int32_t _draw_cb(lgfx::LGFXBase* gfx, int32_t x, int32_t y, uint32_t code, int32_t font_height);

        static emoji_code_ptr_t* emojisPtr;
        static size_t emojisCount;
        static size_t emojisAllocSize;

        static emoji_block_range_t* rangeCodesPtr;
        static size_t rangeCodesCount;
        static size_t rangeCodesAllocSize;

        static LGFXBase* _gfx;

        static bool _loaded;
    };

// ========================================================================================


  } // namespace emojis

  using namespace emojis;

 } // namespave v1
} // namespace lgfx
