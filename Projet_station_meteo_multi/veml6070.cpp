#include <Arduino.h>
#include "veml6070.h"
#include "mqtt.h"

// Variables Index Domoticz. (Mettre IDX = 0 si pas de device).
int idxVEML6070       = 62;                            // Index du Device de l'indice UV.

// Initialisation UV
Adafruit_VEML6070 uv = Adafruit_VEML6070();

void init_veml() {
  uv.begin(VEML6070_1_T);   // passer dans la constante de temps d'intégration
}

void getDataVEML6070() {
  uint16_t valeur = uv.readUV();

   if ( idxVEML6070 != 0) {
    String svalue =  String(valeur) + ";0" ;
    Serial.print("VEML6070 : svalue = "); Serial.print(svalue); Serial.print(" (Indice + un 0)");
    SendData("udevice", idxVEML6070, 0, svalue);
  }
}
