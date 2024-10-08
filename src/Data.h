#pragma once
#include <Arduino.h>

uint8_t count_menu_main;

// Навигация меню
struct Menu_nav
{
  uint8_t count;
  uint8_t selectedItemIndex;
  uint8_t firstVisibleItemIndex;
};

Menu_nav menu_nav_main;
const char *menu_main[] = {
    "Ручной режим",
    "Авто. режим",
    "Настройки WIFI",
    "Консоль",
    "Общие настройки",
};
