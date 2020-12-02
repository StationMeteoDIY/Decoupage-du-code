#include <Arduino.h>
#include "parametre.h"

// ---------------------------------------------------
// Variables de configuration :
const char* topicIn     = "domoticz/out";             // Nom du topic envoyé par Domoticz
const char* topicOut    = "domoticz/in";              // Nom du topic écouté par Domoticz
// ---------------------------------------------------

// On intégre les librairies necessaires à l'I2C.
#include <Wire.h>
