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

#include "./lgfx_emojis.hpp"

namespace lgfx
{
 inline namespace v1
 {
  namespace emojis
  {

    LGFXBase* LGFX_Emojis::_gfx = nullptr;

    bool LGFX_Emojis::_alloc = false;
    bool LGFX_Emojis::_loaded = false;

    const emoji_png_t* LGFX_Emojis::emojisPtr = nullptr;
    size_t LGFX_Emojis::emojisCount = 0;

    // TODO: use real lookup table instead of loop/match
    const emoji_desc_t* LGFX_Emojis::_lookup(uint32_t code)
    {
      static emoji_desc_t entry;

      entry = emoji_desc_t();
      entry.code = code;

      for(int i=0;i<LGFX_Emojis::emojisCount;i++)
      {
        auto emoji = LGFX_Emojis::emojisPtr[i];
        if( emoji.code ==code )
        {
          if( !emoji.data || emoji.data_len == 0 )
            break;

          entry.data = (uint8_t*)emoji.data;
          entry.len  = emoji.data_len;
          entry.png_w = (int16_t)((entry.data[18] << 8) | entry.data[19]);
          entry.png_h = (int16_t)((entry.data[22] << 8) | entry.data[23]);
        }
      }
      return &entry;
    }


    int32_t LGFX_Emojis::_draw_cb(lgfx::LGFXBase* gfx, int32_t x, int32_t y, uint32_t code, int32_t font_height)
    {
      auto* e = LGFX_Emojis::_lookup(code);
      if (!e->data || e->png_h <= 0)
        return 0;

      float scale = (float)font_height / (float)e->png_h;

      // need font metrics, some fonts have a negative y_offset
      FontMetrics metrics;
      gfx->getFont()->getDefaultMetric(&metrics);
      // also apply zoom level
      auto style = gfx->getTextStyle();
      int32_t sy = 65536 * style.size_y;
      // compensate for negative offset, if any
      y += (metrics.y_offset * sy) >> 16;

      if (style.fore_rgb888 != style.back_rgb888)
      {
        gfx->fillRect(x, y, font_height, font_height, style.back_rgb888);
      }

      if (gfx->drawPng(e->data, e->len, x, y, font_height, font_height, 0, 0, scale))
      {
        return font_height;
      }

      return 0;
    }


    bool LGFX_Emojis::_create_list_from_groups(const emoji_png_group_t* emojis_groups, size_t groups_count)
    {
      assert(emojis_groups);
      assert(groups_count>0);

      LGFX_Emojis::emojisCount = 0;

      // 1) count emojis in all groups/subgroups
      for(int g=0;g<groups_count;g++) // for each group
      {
        auto emojis_group = &emojis_groups[g];
        for(int i=0;i<emojis_group->count;i++) // for each subgroup
        {
          LGFX_Emojis::emojisCount += emojis_group->subgroups[i].count; // for each emojis
        }
      }

      if(LGFX_Emojis::emojisCount==0) // empty
      {
        return false;
      }

      // 2) allocate some space to index emoji descriptions
      LGFX_Emojis::emojisPtr = (emoji_png_t*)malloc(LGFX_Emojis::emojisCount*sizeof(const emoji_png_t));

      if(!LGFX_Emojis::emojisPtr) // malloc error
      {
        LGFX_Emojis::emojisCount = 0;
        LGFX_Emojis::emojisPtr = nullptr;
        return false;
      }

      LGFX_Emojis::_alloc = true;

      // 3) index emoji descriptions in allocated space
      int idx = 0;
      for(int g=0;g<groups_count;g++) // for each group
      {
        auto emojis_group = &emojis_groups[g];

        for(int i=0;i<emojis_group->count;i++)
        {
          const emoji_png_set_t* subgroup = &emojis_group->subgroups[i];

          for(int j=0; j<subgroup->count; j++ )
          {
            auto dst = (void*)&LGFX_Emojis::emojisPtr[idx];
            // TODO: check for duplicate before inserting
            // auto* e = LGFX_Emojis::_lookup(dst->code);
            // if (e->data && e->png_h > 0) // this emoji has already been assigned
            //   continue;
            memcpy(dst, &subgroup->emojis[j], sizeof(emoji_png_t));
            idx++;
          }
        }
      }

      LGFX_Emojis::_loaded = true;
      return true;
    }


  }
 }
}
