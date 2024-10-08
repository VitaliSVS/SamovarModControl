#include "Wifi_esp.h"


void Wifi_esp::initialization(char* _ssid, char* _password, uint8_t _nConnect) {
  ssid = _ssid;
  password = _password;
  connected = false;
  nConnect = _nConnect;
}

// Функция для подключения к Wi-Fi
void Wifi_esp::connectToWiFi() {
  Serial.print("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  uint8_t i = 0;

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i++ == nConnect) {
      Serial.println("");
      Serial.print("Не удалось подключиться к");
      Serial.println(ssid);
      connected = false;
      return;
    }
  }
  Serial.println("");
  Serial.print("Подключено к ");
  Serial.println(ssid);
  Serial.print("IP адрес: ");
  Serial.println(WiFi.localIP());
  IP = WiFi.localIP().toString();
  connected = true;
}

//Функция для проверки состояния подключения и повторного подключения при необходимости
void Wifi_esp::checkWiFiConnection() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Потеряно соединение Wi-Fi. Повторное подключение...");
    connected = false;
    connectToWiFi();
  }
}

// Метод, который возвращает сообщение в соответствии со статусом подключения Wi-Fi
String Wifi_esp::getWiFiStatusMessage() {
  switch (WiFi.status()) {
    case WL_IDLE_STATUS:
      return "Устройство в режиме ожидания";
    case WL_NO_SSID_AVAIL:
      return "Нет доступных Wi-Fi сетей";
    case WL_SCAN_COMPLETED:
      return "Сканирование завершено";
    case WL_CONNECTED:
      return "Подключено к Wi-Fi сети";
    case WL_CONNECT_FAILED:
      return "Не удалось подключиться к Wi-Fi сети";
    case WL_CONNECTION_LOST:
      return "Потеряно соединение с Wi-Fi сетью";
    case WL_DISCONNECTED:
      return "Отключено от Wi-Fi сети";
    case WL_NO_SHIELD:
      return "Отсутствует Wi-Fi модуль или шилд";
    default:
      return "Неизвестный статус";
  }
}

// Метод для получения списка доступных Wi-Fi сетей
uint8_t Wifi_esp::scanAvailableNetworks() {
  // Инициализация Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(1000);
  int nst = WiFi.scanNetworks();
  Serial.print("Найдено сетей: ");
  Serial.println(nst);
  // Перебор найденных сетей
  availableNetworks.clear();
  for (uint8_t i = 0; i < nst; i++) {
    availableNetworks.add(WiFi.SSID(i));  // Добавление имени сети в вектор
    Serial.println(WiFi.SSID(i));
  }
  return nst;
}
