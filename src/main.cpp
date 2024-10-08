#include <Arduino.h>
#include "stdafx.h"
// put function declarations here:
void TaskMenu(void *pvParameters);

void tickerMQTT_tik()
{
  mqttClient.clientMQTT.loop();
  // Проверка состояния подключения к MQTT серверу
  if (!mqttClient.connected())
    mqttClient.reconnect(stg_data.stg_MQTT.nConnect, stg_data.stg_MQTT.user, stg_data.stg_MQTT.password);
  // Проверка флага нового сообщения
  if (newMessageReceived)
  {
    String str(receivedMessage);
    if (str == "reset")
      ESP.restart();
    // st7789.printStrln(str, 1, ST77XX_GREEN);

    // Сброс флага нового сообщения
    newMessageReceived = false;
  }

  // Чтение значения температуры с датчика DS18B20
  // float temperature = readTemperature();
  float temperature = 678;
  // Отправка значения температуры на MQTT-сервер
  char temperatureStr[10];
  dtostrf(temperature, 6, 2, temperatureStr);
  mqttClient.clientMQTT.publish("samovar/t_hol", temperatureStr);

  // Проверка состояния подключения Wi-Fi и повторное подключение при необходимости
  wifi_esp.checkWiFiConnection();

  // Обработка входящих клиентских запросов
  server.handleClient();
}

void tickerBN_tik()
{
  buttum_esp.timerCallback();
}
ST7789_esp st7789 = ST7789_esp(TFT_RST, TFT_DC, TFT_MOSI, TFT_SCLK);

void setup()
{
  Serial.begin(115200);
  setting_esp.loadSetting();
  buttum_esp.initialization(36);
  st7789.initialization();
  // Устанавливаем прерывание на каждую секунду
  tickerBN.attach_ms(100, tickerBN_tik);

  count_menu_main = sizeof(menu_main) / sizeof(menu_main[0]);
  st7789.drawMenu(menu_main, count_menu_main);
  // Подключение к Wi-Fi
  wifi_esp.initialization(stg_data.stg_WIFI.ssid, stg_data.stg_WIFI.password, stg_data.stg_WIFI.nConnect);
  wifi_esp.connectToWiFi();
  // Настройка веб сервера
  setupServer();

  // Подключение к MQTT-серверу
  mqttClient.initialization(stg_data.stg_MQTT.ip, stg_data.stg_MQTT.port);
  mqttClient.clientMQTT.setCallback(callback);
  // Подписка на топик "samovar/msg"
  mqttClient.reconnect(stg_data.stg_MQTT.nConnect, stg_data.stg_MQTT.user, stg_data.stg_MQTT.password);
  // clientMQTT.subscribe("samovar/msg");

  tickerMQTT.attach_ms(100, tickerMQTT_tik);
  // xTaskCreateUniversal(TaskMenu, "button", 2048, NULL, 5, NULL,1);
  xTaskCreate(TaskMenu, "Blink1", 4096, NULL, 5, NULL);
}

void loop()
{
}

void TaskMenu(void *pvParameters) // Это задача.
{
  (void)pvParameters;

  for (;;) // задача должна никогда не прекращаться или прерываться
  {
    if (buttum_esp.isValue)
    {
      uint8_t bnclk = buttum_esp.get_value();
      Serial.print("Нажата кнопка: ");
      Serial.println(bnclk);

      // Обработка нажатия кнопок для выбора пунктов меню
      if (bnclk == 1)
        st7789.drawMenu(menu_main, count_menu_main);
      if (bnclk == 5)
      {
        //tickerBN.detach();
        tickerMQTT.detach();
          // Очист дисплей
        st7789.fillScreen(ST77XX_BLACK);

        Serial.println("Вывод списка сетей");
        uint8_t nst = wifi_esp.scanAvailableNetworks();
        st7789.print("Num networks = ");
        st7789.println(wifi_esp.availableNetworks.getSize());
        for (uint8_t i = 0; i < nst; i++)
        {
          st7789.printStrln(wifi_esp.availableNetworks[i], 2, ST77XX_RED);
          //st7789.println(wifi_esp.availableNetworks[i]);
        }
        tickerMQTT.active();
      }
      if (bnclk == 2)
      {
        if (st7789.selectedItemIndex > 0)
        {
          st7789.selectedItemIndex--;
          if (st7789.selectedItemIndex < st7789.firstVisibleItemIndex)
          {
            st7789.firstVisibleItemIndex--;
          }
          st7789.drawMenu(menu_main, count_menu_main);
        }
      }

      if (bnclk == 3)
      {
        if (st7789.selectedItemIndex < count_menu_main - 1)
        {
          st7789.selectedItemIndex++;
          if (st7789.selectedItemIndex >= st7789.firstVisibleItemIndex + (MENU_HEIGHT / (MENU_ITEM_HEIGHT + MENU_ITEM_SPACING)))
          {
            st7789.firstVisibleItemIndex++;
          }
          st7789.drawMenu(menu_main, count_menu_main);
        }
      }

      // st7789.printStrln(String(buttum_esp.get_value()), 1, ST77XX_GREEN);
    }
    delay(100);
  }
}