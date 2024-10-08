
#include "ST7789_esp.h"

// CONSTRUCTORS ************************************************************

/*!
    @brief  Instantiate Adafruit ST7789 driver with software SPI
    @param  dc    Data/Command pin #
    @param  mosi  SPI MOSI pin #
    @param  sclk  SPI Clock pin #
    @param  rst   Reset pin #
*/
ST7789_esp::ST7789_esp(int8_t rst, int8_t dc, int8_t mosi, int8_t sclk)
    //: Adafruit_ST7789(-1, 26, 14,12,27)
    : Arduino_ST7789(dc, rst, mosi, sclk)
{
  // _rst = rst;
  // _cs = cs;
  // _dc = dc;
  // init(240, 240, SPI_MODE3);
}
// Функция для инициализации дисплея
void ST7789_esp::initialization()
{

  textLine = 0;
  init(240, 240); // initialize a ST7789 chip, 240x240 pixels
  Serial.println("Initialized ST7789");
  uint16_t time = millis();
  fillScreen(ST77XX_BLACK);
  time = millis() - time;
  Serial.println(time, DEC);
  selectedItemIndex = 0;
  firstVisibleItemIndex = 0;
}

void ST7789_esp::printStr(String str, uint8_t textSize, uint16_t textColor)
{
  setTextColor(textColor);
  setTextSize(textSize);
  println(str);
}

void ST7789_esp::printStrln(String str, uint8_t textSize, uint16_t textColor)
{
  setCursor(0, textLine);
  if (textLine > 230)
  {
    setTextWrap(false);
    fillScreen(ST77XX_BLACK);
    setCursor(0, 0);
    textLine = 0;
  }
  setTextColor(textColor);
  setTextSize(textSize);
  println(str);
  textLine += 13;
}

void ST7789_esp::printPower(uint16_t power, uint8_t textSize, uint16_t textColor)
{
  fillRect(180, 0, 60, 40, ST77XX_BLACK);
  drawRect(180, 0, 60, 40, ST77XX_WHITE);
  setCursor(190, 10);
  setTextColor(textColor);
  setTextSize(textSize);
  print(power);
}
void ST7789_esp::drawMenu(const char *menuItems[], uint8_t itemCount)
{
  // setFont(&FreeSerif14pt8b ); // выбор шрифта
  setFont(&TimesNRCyr12pt8b); // выбор шрифта

  uint8_t maxVisibleItems = MENU_HEIGHT / (MENU_ITEM_HEIGHT + MENU_ITEM_SPACING);
  uint8_t lastVisibleItemIndex = firstVisibleItemIndex + maxVisibleItems - 1;

  if (lastVisibleItemIndex >= itemCount)
  {
    lastVisibleItemIndex = itemCount - 1;
  }

  for (uint8_t i = firstVisibleItemIndex; i <= lastVisibleItemIndex; i++)
  {
    uint16_t xPos = MENU_X;
    uint16_t yPos = MENU_Y + (i - firstVisibleItemIndex) * (MENU_ITEM_HEIGHT + MENU_ITEM_SPACING);
    uint16_t width = MENU_WIDTH;
    uint16_t height = MENU_ITEM_HEIGHT;

    if (i == selectedItemIndex)
    {
      fillRect(xPos, yPos, width, height, MENU_SELECTED_COLOR);
      setTextColor(MENU_BACKGROUND_COLOR);
    }
    else
    {
      fillRect(xPos, yPos, width, height, MENU_BACKGROUND_COLOR); // Очищаем предыдущее значение
      drawRect(xPos, yPos, width, height, MENU_ITEM_COLOR);
      setTextColor(MENU_ITEM_COLOR);
    }

    setTextSize(1);
    setCursor(xPos + 10, yPos + 23);
    println(menuItems[i]);
  }

  // Отрисовка полосы прокрутки
  if (itemCount > maxVisibleItems)
  {
    uint16_t scrollbarX = MENU_X + MENU_WIDTH;
    uint16_t scrollbarY = MENU_Y;
    uint16_t scrollbarHeight = 40;

    fillRect(scrollbarX, scrollbarY, 8, MENU_HEIGHT, MENU_BACKGROUND_COLOR);
    fillRect(scrollbarX, scrollbarY + firstVisibleItemIndex * (MENU_HEIGHT - scrollbarHeight) / (itemCount - maxVisibleItems), 8, scrollbarHeight, SCROLLBAR_COLOR);
  }
  setFont(); // выбор шрифта по умолчанию
}