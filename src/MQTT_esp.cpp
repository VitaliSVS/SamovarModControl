#include "MQTT_esp.h"

MQTT_esp::MQTT_esp(char* _mqttBroker, uint16_t _mqttPort) {
  initialization(_mqttBroker,_mqttPort);
}
void MQTT_esp::initialization(char* _mqttBroker, uint16_t _mqttPort) {
  mqttBroker = _mqttBroker;
  mqttPort = _mqttPort;
  newMessageReceived = false;
  clientMQTT.setClient(espClient);
  clientMQTT.setServer(mqttBroker, mqttPort);
}
void MQTT_esp::reconnect(uint8_t nConnect, const char* mqttUsername, const char* mqttPassword) {
  // Переподключение, пока клиент не будет подключен
  uint8_t i = 0;
  while (!clientMQTT.connected()) {
    Serial.print("Подключение к MQTT-серверу...");
    if (clientMQTT.connect("ESP32Client", mqttUsername, mqttPassword)) {
      Serial.println("Подключено!");
      clientMQTT.subscribe("msg");
    } else {
      Serial.print("Не удалось подключиться, ошибка код = ");
      Serial.println(clientMQTT.state());
      delay(1000);
      if (i++ == nConnect) {
        Serial.println("");
        Serial.println("Не удалось подключиться к MQTT-серверу!");
        return;
      }
    }
  }
}

boolean MQTT_esp::connected() {
  return clientMQTT.connected();
}