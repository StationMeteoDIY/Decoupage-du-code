#include <Arduino.h>
#include "connect.h"

const char* ssid = "_MON_SSID_";                   // SSID du réseau Wifi
const char* password = "_MOT_DE_PASSE_WIFI_";      // Mot de passe du réseau Wifi.
const char* mqtt_server = "_IP_DU_BROKER_";        // Adresse IP ou DNS du Broker.
const int mqtt_port = 1883;                        // Port du Brocker MQTT
const char* mqtt_login = "_LOGIN_";                // Login de connexion à MQTT.
const char* mqtt_password = "_PASSWORD_";          // Mot de passe de connexion à MQTT.


// Variables et constantes utilisateur :
const char* nomModule  = "Station Météo";         // Nom usuel de ce module. Sera visible uniquement dans les Log Domoticz.
