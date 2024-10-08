#pragma once
#include <Arduino.h>
#include <Preferences.h>
#include <string.h>
// Пины, дисплея ST7789
//#define TFT_MOSI 22  // SDA Pin on ESP32
//#define TFT_SCLK 18  // SCL Pin on ESP32
#define TFT_MOSI 14
#define TFT_SCLK 12

#define TFT_DC 26  // Data Command control pin
#define TFT_RST 27 // Reset pin (could connect to RST pin)


//Настройки по умолчанию WIFI
#define WIFI_SSID "KV42"
#define WIFI_PASS "2136a6829"
#define WIFI_NCONNECT 15

//Настройки по умолчанию MQTT
#define MQTT_IP "113.30.190.232"
#define MQTT_PORT 1883
#define MQTT_NCONNECT 5
#define MQTT_USER "mosquitto"
#define MQTT_PASS "11111111"

// Пины датчика DS18B20
#define ONE_WIRE_BUS 15  



//Пины, дисплея ST7789
struct STG_ST7789 {
  uint8_t mosi;
  uint8_t sclk;
  uint8_t ds;
  uint8_t rst;

};

// Пин датчика DS18B20
struct STG_Sensor {
  uint8_t tsens;
};

// Настройки wifi
struct STG_WIFI {
  char ssid[20];
  char password[20];
  uint8_t nConnect;
};

// Настройки mqtt
struct STG_MQTT {
  char ip[20];
  uint16_t port;
  uint8_t nConnect;
  char user[20]; 
  char password[20];  
};

// Все настройки
struct STG_DATA {
  uint8_t status;
  STG_ST7789 stg_ST7789;
  STG_Sensor stg_Sensor;
  STG_WIFI stg_WIFI;
  STG_MQTT stg_MQTT;  
};

static STG_DATA stg_data;
static Preferences preferences;

class Setting_esp {
public:
  Setting_esp() {
  }
  void setDefaultSetting() {
    preferences.clear();   
    preferences.begin("STG_DATA", false);
    stg_data.stg_ST7789.mosi = TFT_MOSI;
    stg_data.stg_ST7789.sclk = TFT_SCLK;    
    stg_data.stg_ST7789.ds = TFT_DC;
    stg_data.stg_ST7789.rst = TFT_RST;

    stg_data.stg_Sensor.tsens = ONE_WIRE_BUS;

    strcpy(stg_data.stg_WIFI.ssid, WIFI_SSID);
    strcpy(stg_data.stg_WIFI.password, WIFI_PASS);
    stg_data.stg_WIFI.nConnect = WIFI_NCONNECT;

    strcpy(stg_data.stg_MQTT.ip, MQTT_IP);
    stg_data.stg_MQTT.port = MQTT_PORT;
    stg_data.stg_MQTT.nConnect = MQTT_NCONNECT;
    strcpy(stg_data.stg_MQTT.password, MQTT_PASS);
    strcpy(stg_data.stg_MQTT.user, MQTT_USER);
    
    stg_data.status = 50;
    // Записываем структуру в память
    preferences.putBytes("STG_DATA", &stg_data, sizeof(STG_DATA));
    preferences.end();
  }
  void loadSetting() {
    preferences.begin("STG_DATA", false);
    preferences.getBytes("STG_DATA", &stg_data, sizeof(STG_DATA));
    if (stg_data.status != 50) {
      setDefaultSetting();
    }
    preferences.end();
  }
  void saveSetting() {
    preferences.begin("STG_DATA", false);
    stg_data.status = 50;
    // Записываем структуру в память
    preferences.putBytes("STG_DATA", &stg_data, sizeof(STG_DATA));
    preferences.end();
  }
private:
};
