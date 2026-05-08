//#include <lvgl.h>

#if !defined USE_M5GFX && !defined USE_LGFX
  // just pick one

  #define USE_M5GFX
  //#define USE_LGFX

#endif

#if defined USE_M5GFX // Note: M5GFX version must be >= 1.2.20

  #include <M5GFX.h>
  #include <M5Unified.h>

  #define lcd M5.Display
  #define initExample M5.begin

#elif defined USE_LGFX

  #define LGFX_AUTODETECT
  #include <LovyanGFX.hpp>
  // If autodetect fails, check `LovyanGFX/src/lgfx_user` folder to see if your device is listed and add it as follows:
  // #include <lgfx_user/LGFX_3.5_RPI_LCD_A.hpp>
  // If it isn't listed, see https://github.com/lovyan03/LovyanGFX/blob/master/examples/HowToUse/2_user_setting/2_user_setting.ino
  static LGFX lcd;
  #define initExample lcd.init

#else

  #error "missing define: USE_LGFX or USE_M5GFX"

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
