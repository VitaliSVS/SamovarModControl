#ifndef Wifi_esp_h
#define Wifi_esp_h
#include <List.hpp>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiScan.h>
class Wifi_esp {
public:
  List<String> availableNetworks;  //Список доступных wifi сетей
  String IP;
  uint8_t nConnect;
  Wifi_esp(char* _ssid, char* _password, uint8_t _nConnect) {
    initialization(_ssid, _password, _nConnect);
  }
  Wifi_esp() {}
  void initialization(char* _ssid, char* _password, uint8_t _nConnect);
  // Функция для подключения к Wi-Fi
  void connectToWiFi();
  //Функция для проверки состояния подключения и повторного подключения при необходимости
  void checkWiFiConnection();
  // Метод, который возвращает сообщение в соответствии со статусом подключения Wi-Fi
  String getWiFiStatusMessage();
  // Метод для получения списка доступных Wi-Fi сетей
  uint8_t scanAvailableNetworks();

private:
  bool connected;  // Флаг для отслеживания состояния подключения
  char* ssid;
  char* password;
};
#endif