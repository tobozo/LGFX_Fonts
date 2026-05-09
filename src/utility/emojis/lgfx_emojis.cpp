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

    emoji_code_ptr_t* LGFX_Emojis::emojisPtr = nullptr;
    size_t LGFX_Emojis::emojisCount = 0;
    size_t LGFX_Emojis::emojisAllocSize = 0;

    emoji_block_range_t* LGFX_Emojis::rangeCodesPtr = nullptr;
    size_t LGFX_Emojis::rangeCodesCount = 0;
    size_t LGFX_Emojis::rangeCodesAllocSize = 0;

    emoji_lookup_cb_t LGFX_Emojis::_lookup_cb = _lookup;


    // bubble sort
    void LGFX_Emojis::_emoji_code_ptr_sort(emoji_code_ptr_t* emojisPtr, size_t emojisCount)
    {
      if(!emojisPtr || emojisCount==0)
        return;
      for (int i = 0; i < emojisCount - 1; i++)
        for (int j = 0; j < emojisCount - i - 1; j++)
          if (emojisPtr[j].code > emojisPtr[j + 1].code)
            std::swap(emojisPtr[j], emojisPtr[j + 1]);
    }


    // Split indexes/codes from emoji_code_ptr_t array into emoji_block_range_t (buckets) for faster lookup.
    bool LGFX_Emojis::_emoji_code_range_split(emoji_code_ptr_t*emojisPtr, size_t emojisCount)
    {
      if(!emojisPtr || emojisCount==0)
        return false;

      rangeCodesCount = 0;

      // The amount of buckets is estimated by extracting the sqrt(emojisCount).
      // This sets the maximum lookup iterations to bucketSize*2 (instead of bucketSize^2 for a single loop).
      const float sqrCount = sqrt(emojisCount);
      const size_t bucketSize = sqrCount>8 ? ceil(sqrCount) : 8;

      rangeCodesAllocSize = bucketSize*sizeof(emoji_block_range_t);
      rangeCodesPtr = (emoji_block_range_t*)malloc(rangeCodesAllocSize);

      if(!rangeCodesPtr) { // malloc failed
        rangeCodesAllocSize = 0;
        return false;
      }

      uint32_t range_start = emojisPtr[0].code;
      uint32_t range_end = range_start;
      uint32_t idx_start = 0;

      for(uint32_t i=1;i<emojisCount;i++) {
        if( i-idx_start>bucketSize ) {
          rangeCodesPtr[rangeCodesCount++] = {range_start, range_end, idx_start, i-1};
          range_start = emojisPtr[i].code;
          idx_start = i;
        }
        range_end = emojisPtr[i].code;
      }

      if( rangeCodesCount>0 && rangeCodesPtr[rangeCodesCount-1].end != range_end )
        rangeCodesPtr[rangeCodesCount++] = {range_start, range_end, idx_start, emojisCount-1};

      return rangeCodesCount>0;
    }

    // slow emoji lookup
    const emoji_desc_t* LGFX_Emojis::_lookup(uint32_t code)
    {
      static emoji_desc_t entry;
      entry = emoji_desc_t();
      entry.code = code;

      if( !emojisPtr || emojisCount==0 || code == 0)
        goto _end;

      for(int i=0;i<LGFX_Emojis::emojisCount;i++) {
        auto emoji = LGFX_Emojis::emojisPtr[i].ptr;
        if( emoji->code == code ) { // match
          if( !emoji->data || emoji->data_len == 0 )
            goto _end; // bad emoji?
          entry.data  = (uint8_t*)emoji->data;
          entry.len   = emoji->data_len;
          entry.png_w = (int16_t)((entry.data[18] << 8) | entry.data[19]);
          entry.png_h = (int16_t)((entry.data[22] << 8) | entry.data[23]);
          goto _end;
        }
      }
      _end:
      return &entry;
    }

    // fast emoji lookup
    const emoji_desc_t* LGFX_Emojis::_lookup_fast(uint32_t code)
    {
      static emoji_desc_t entry;
      entry = emoji_desc_t();
      entry.code = code;

      if( !rangeCodesPtr || rangeCodesCount==0 || code == 0)
        goto _end;

      for(int i=0;i<rangeCodesCount;i++) {
        auto range = rangeCodesPtr[i];
        if( code > range.end )
          continue; // code value to look up is outside the current range, no need to loop through
        for( int idx=range.idx_start; idx<=range.idx_end; idx++ ) {
          auto emoji = emojisPtr[idx].ptr;
          if( emoji->code == code ) { // match
            if( !emoji->data || emoji->data_len == 0 )
              goto _end; // bad emoji?
            entry.data  = (uint8_t*)emoji->data;
            entry.len   = emoji->data_len;
            entry.png_w = (int16_t)((entry.data[18] << 8) | entry.data[19]);
            entry.png_h = (int16_t)((entry.data[22] << 8) | entry.data[23]);
            goto _end;
          }
        }
      }
      _end:
      return &entry;
    }

    // draw callback for LGFX
    int32_t LGFX_Emojis::_draw_cb(lgfx::LGFXBase* gfx, int32_t x, int32_t y, uint32_t code, int32_t font_height)
    {
      auto* e = _lookup_cb(code);
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

    // sort and index selected emojis
    bool LGFX_Emojis::_create_list_from_groups(const emoji_png_group_t* emojis_groups, size_t groups_count)
    {
      if(!emojis_groups)
        return false;
      if(groups_count==0)
        return false;

      emojisCount = 0;

      // count selected emojis
      for(int g=0;g<groups_count;g++)
        for(int i=0;i<emojis_groups[g].count;i++)
          emojisCount += emojis_groups[g].subgroups[i].count;

      if(emojisCount == 0)
        return false;

      emojisAllocSize = emojisCount*sizeof(emoji_code_ptr_t);
      emojisPtr = (emoji_code_ptr_t*)malloc(emojisAllocSize);

      if(!emojisPtr) {
        emojisAllocSize = 0;
        return false;
      }

      size_t emojiIdx = 0;

      // add selected emojis (code+pointer) to an array
      for(int g=0;g<groups_count;g++) { // for each group
        auto emojis_group = &emojis_groups[g];
        for(int i=0;i<emojis_group->count;i++) {
          auto subgroup = &emojis_group->subgroups[i];
          for(int j=0; j<subgroup->count; j++ )
            emojisPtr[emojiIdx++] = { subgroup->emojis[j].code, &subgroup->emojis[j] };
        }
      }

      _emoji_code_ptr_sort(emojisPtr,  emojisCount); // sort emojis by code

      if( _emoji_code_range_split(emojisPtr,  emojisCount) )
        _lookup_cb = _lookup_fast; // fast lookup enabled
      else // _emoji_code_range_split allocation failed, fallback to slow lookup
        _lookup_cb = _lookup;

      _loaded = true;
      return true;
    }

// ========================================================================================

  } // namespace emojis
 } // namespave v1
} // namespace lgfx
