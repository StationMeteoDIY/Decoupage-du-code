#ifndef MQTT_H
#define MQTT_H

#include "connect.h"
#include "parametre.h"
// On intégre les librairies necessaires à la connexion Wifi, au MQTT, et à JSON, necessaire pour le MQTT.
#include "wifi.h"
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <WiFiUdp.h>


void init_connect_mqtt();
void reconnect();
void verif_connexion_mqtt();
void SendData (String command, int idxDevice, int nvalue, String svalue);

#endif
