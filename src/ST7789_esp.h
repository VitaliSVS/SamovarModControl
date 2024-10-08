
#pragma once
#include <Arduino_ST7789.h>
#include "Adafruit_ST77xx.h"
#include <FontsRus/FreeSerif14.h>
#include <FontsRus/TimesNRCyr12.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <SPI.h>

#define TFT_WIDTH 240
#define TFT_HEIGHT 240

#define MENU_WIDTH 230
#define MENU_HEIGHT 180

#define MENU_X 1
#define MENU_Y 70

#define MENU_ITEM_HEIGHT 30
#define MENU_ITEM_SPACING 5

const float p = 3.1415926;

const uint16_t MENU_BACKGROUND_COLOR = ST77XX_BLACK;
const uint16_t MENU_ITEM_COLOR = ST77XX_WHITE;
const uint16_t MENU_SELECTED_COLOR = ST77XX_CYAN;
const uint16_t SCROLLBAR_COLOR = ST77XX_GREEN;

class ST7789_esp : public Arduino_ST7789
{
public:
  uint8_t selectedItemIndex;
  uint8_t firstVisibleItemIndex;
  ST7789_esp(int8_t rst, int8_t dc, int8_t mosi, int8_t sclk);
  ST7789_esp();
  // Метод для инициализации дисплея
  void initialization();
  // Метод вывода строки
  void printStr(String str, uint8_t textSize, uint16_t textColor);
  void printStrln(String str, uint8_t textSize, uint16_t textColor);
  void printPower(uint16_t power, uint8_t textSize, uint16_t textColor);
  void drawMenu(const char *menuItems[], uint8_t itemCount);

private:
  uint16_t textLine;
};
