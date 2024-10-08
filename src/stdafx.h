#pragma once
#include "freertos/FreeRTOS.h"
//#include "freertos/task.h"
//#include "esp_log.h"
#include <List>

#include "Settings.h"
#include "Data.h"
#include "Wifi_esp.h"
#include "WebServer_esp.h"
#include "ST7789_esp.h"
#include "MQTT_esp.h"
#include "Buttun_esp.h"
#include "ST7789_esp.h"
#include <Ticker.h>

Setting_esp setting_esp;


Ticker tickerMQTT;
Wifi_esp wifi_esp;
//ST7789_esp st7789(TFT_RST, TFT_DC, TFT_MOSI, TFT_SCLK);
MQTT_esp mqttClient;
Buttun buttum_esp;
Ticker tickerBN;