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

// ========================================================================================

    LGFXBase* LGFX_Emojis::_gfx = nullptr;

    bool LGFX_Emojis::_loaded = false;

    std::vector<emoji_code_ptr_t> LGFX_Emojis::emojisVec;
    std::vector<emoji_block_range_t> LGFX_Emojis::rangedCodes;


    const emoji_desc_t* LGFX_Emojis::_lookup(uint32_t code)
    {
      static emoji_desc_t entry;
      entry = emoji_desc_t();
      entry.code = code;

      for(int i=0;i<rangedCodes.size();i++) {
        if( code>rangedCodes[i].end )
          continue;

        for( int idx=rangedCodes[i].idx_start; idx<=rangedCodes[i].idx_end; idx++ ) {
          auto emoji = emojisVec[idx].ptr;
          if( emoji->code == code ) {
            if( !emoji->data || emoji->data_len == 0 )
              goto _end;

            entry.data = (uint8_t*)emoji->data;
            entry.len  = emoji->data_len;
            entry.png_w = (int16_t)((entry.data[18] << 8) | entry.data[19]);
            entry.png_h = (int16_t)((entry.data[22] << 8) | entry.data[23]);
            goto _end;
          }
        }
      }

      _end:
      return &entry;
    }


    int32_t LGFX_Emojis::_draw_cb(lgfx::LGFXBase* gfx, int32_t x, int32_t y, uint32_t code, int32_t font_height)
    {
      auto* e = _lookup(code);
      if (!e->data || e->png_h <= 0)
        return 0;
      // png will be scaled to font height
      float scale = (float)font_height / (float)e->png_h;
      // need font metrics, some fonts have a negative y_offset
      FontMetrics metrics;
      gfx->getFont()->getDefaultMetric(&metrics);
      // apply text zoom level to that negative y_offset, if any
      auto style = gfx->getTextStyle();
      int32_t sy = 65536 * style.size_y;
      // compensate for negative y_offset, if any
      y += (metrics.y_offset * sy) >> 16;
      // paint background if style specifies it
      if (style.fore_rgb888 != style.back_rgb888)
        gfx->fillRect(x, y, font_height, font_height, style.back_rgb888);
      // overlay with resized png
      if (gfx->drawPng(e->data, e->len, x, y, font_height, font_height, 0, 0, scale))
        return font_height; // success
      return 0; // png rendering failed, image too big or scale too low?
    }


    bool LGFX_Emojis::_create_list_from_groups(const emoji_png_group_t* emojis_groups, size_t groups_count)
    {
      if(!emojis_groups)
        return false;
      if(groups_count==0)
        return false;

      emojisVec.clear();
      rangedCodes.clear();

      // 1) add selected emojis (code+pointer) to a vector
      for(int g=0;g<groups_count;g++) { // for each group
        auto emojis_group = &emojis_groups[g];
        for(int i=0;i<emojis_group->count;i++) {
          auto subgroup = &emojis_group->subgroups[i];
          for(int j=0; j<subgroup->count; j++ ) {
            emojisVec.push_back({ subgroup->emojis[j].code, &subgroup->emojis[j] });
          }
        }
      }

      if( emojisVec.size() == 0 )
        return false;

      // 2) sort emojis by code
      std::sort(emojisVec.begin(), emojisVec.end(), [](auto &a, auto &b) -> bool { return a.code < b.code; });

      // 3) split indexes/codes in ranges for faster lookup
      uint32_t lastCode = emojisVec[0].code;
      uint32_t lastInsertedIdx = 0;
      uint32_t blocks = 1;
      uint32_t range_start = lastCode;
      uint32_t idx_start = 0;
      for(uint32_t i=1;i<emojisVec.size();i++)
      {
        if( lastCode+1 != emojisVec[i].code && i-lastInsertedIdx>8)
        {
          rangedCodes.push_back({range_start, lastCode, idx_start, i-1});
          range_start = emojisVec[i].code;
          idx_start = i;
          blocks++;
          lastInsertedIdx = i;
        }
        lastCode = emojisVec[i].code;
      }
      if( rangedCodes[rangedCodes.size()-1].end != lastCode )
        rangedCodes.push_back({range_start, lastCode, idx_start, emojisVec.size()-1});

      _loaded = true;
      return true;
    }

// ========================================================================================

  } // namespace emojis
 } // namespave v1
} // namespace lgfx
