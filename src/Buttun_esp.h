#include <Arduino.h>

class Buttun {
public:

  bool isValue;
  // Конструктор
  Buttun(uint8_t _bn_pin) {
    initialization(_bn_pin);
  }
  Buttun() {}

  void initialization(uint8_t _bn_pin);
  void timerCallback();
  uint8_t get_value();
private:
  uint8_t bn_value;
  uint8_t bn_pin;
  unsigned long interval;
  int lastChange;
  int bnTikTime;

  int bn_old_analg;
  int bn_old_value;
  int bn_new_analg;
  int key_values[5];

  uint8_t get_button_press(int val);
};
