#include "Buttun_esp.h"

void Buttun::initialization(uint8_t _bn_pin)
{

  // lastChange = _lastChange;
  // bnTikTime = _bnTikTime;
  bn_pin = _bn_pin;
  bn_value = 0;
  bn_old_analg = 0;
  bn_old_value = 6;
  lastChange = 0;
  bnTikTime = 0;
  isValue = false;
  key_values[0] = 100;
  key_values[1] = 500;
  key_values[2] = 1200;
  key_values[3] = 2000;
  key_values[4] = 3000;
}

uint8_t Buttun::get_value()
{
  uint8_t n = bn_value;
  bn_value = 0;
  isValue = false;
  return n;
}

void Buttun::timerCallback()
{
  bn_new_analg = analogRead(bn_pin); // Используем объект для доступа к членам класса
  if ((bn_new_analg != bn_old_analg) && (millis() - lastChange > 100))
  {
    bn_old_analg = bn_new_analg;
    lastChange = millis();
  }
  uint8_t bt_new = get_button_press(bn_old_analg);
  // Serial.println(bt_new);
  //  Вызываем функцию-член на объекте
  if (bt_new != bn_old_value)
  {
    bn_old_value = bt_new;
    if (bt_new < 6)
    {
      bn_value = bt_new;
      isValue = true;
    }
    bnTikTime = millis();
  }
  else
  {
    if ((bn_old_value != 6) && (millis() - bnTikTime > 500))
    {
      bn_value = bn_old_value;
      isValue = true;
    }
  }
}

uint8_t Buttun::get_button_press(int val)
{
  for (uint8_t i = 0; i < 5; i++)
  {
    if (val < key_values[i])
    {
      return i + 1;
    }
  }
  return 6;
}
