
//#include <lvgl.h>


#define USE_LGFX
//#define USE_M5GFX


#if defined USE_LGFX

  #include <LovyanGFX.hpp>
  #include <lgfx_user/LGFX_3.5_RPI_LCD_A.hpp>

  static LGFX lcd;
  #define initExample lcd.init


#elif defined USE_M5GFX // Note: M5GFX version < 1.2.20

  #include <M5GFX.h>
  #include <M5Unified.h>

  #define lcd M5.Display
  #define initExample M5.begin

#endif


#include <LGFX_Fonts.hpp>


void setup()
{
    initExample();

    lcd.setTextColor(TFT_BLACK, TFT_WHITE);

#if defined M5GFX_LVGL_INTERNAL_H
    // use a lvgl font from the M5GFX/LovyanGFX library
    lcd.setFont(&fonts::lv_font_montserrat_8);
    lcd.println("ABCDEFGHJKLMNOPQRSTUVWXYZabcdefghjklmnopqrstuvwxyz0123456789");
    lcd.setFont(&fonts::lv_font_montserrat_10);
    lcd.println("ABCDEFGHJKLMNOPQRSTUVWXYZabcdefghjklmnopqrstuvwxyz0123456789");
    lcd.setFont(&fonts::lv_font_montserrat_28);
    lcd.println("ABCDEFGHJKLMNOPQRSTUVWXYZabcdefghjklmnopqrstuvwxyz0123456789");
#else
    // use a lvgl font from the LGFX_Fonts library
    lcd.setFont(&fonts::lvFontMontserrat8);
    lcd.println("ABCDEFGHJKLMNOPQRSTUVWXYZabcdefghjklmnopqrstuvwxyz0123456789");
    lcd.setFont(&fonts::lvFontMontserrat10);
    lcd.println("ABCDEFGHJKLMNOPQRSTUVWXYZabcdefghjklmnopqrstuvwxyz0123456789");
    lcd.setFont(&fonts::lvFontMontserrat28);
    lcd.println("ABCDEFGHJKLMNOPQRSTUVWXYZabcdefghjklmnopqrstuvwxyz0123456789");
#endif
}


void loop()
{

}
