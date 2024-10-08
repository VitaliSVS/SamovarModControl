#pragma once
#include <PubSubClient.h>
#include <WiFiClient.h>
#define MAX_MESSAGE_LENGTH 128
static char receivedMessage[MAX_MESSAGE_LENGTH];
static bool newMessageReceived;

static void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  // Очистка предыдущего сообщения
  memset(receivedMessage, 0, sizeof(receivedMessage));
  // Копирование нового сообщения
  strncpy(receivedMessage, (char*)payload, (length < MAX_MESSAGE_LENGTH - 1) ? length : (MAX_MESSAGE_LENGTH - 1));
  receivedMessage[(length < MAX_MESSAGE_LENGTH - 1) ? length : (MAX_MESSAGE_LENGTH - 1)] = '\0';
  // Установка флага нового сообщения
  newMessageReceived = true;
  Serial.println(receivedMessage);
}


class MQTT_esp {
public:
  char* mqttBroker;
  int mqttPort;
  WiFiClient espClient;
  PubSubClient clientMQTT;
  MQTT_esp(char* _mqttBroker, uint16_t _mqttPort);
  void reconnect(uint8_t nConnect, const char* mqttUsername, const char* mqttPassword);
  boolean connected();
  MQTT_esp(){}
  void initialization(char* _mqttBroker, uint16_t _mqttPort);
private:
};
