#include <Arduino.h>
#include "bme280.h"
#include "mqtt.h"

// Variables Index Domoticz. (Mettre IDX = 0 si pas de device).
int idxBME280         = 61;                           // Index du capteur BME280
int idxPA             = 0;                            // Index du capteur BME ou BMP 280, uniquement pour la pression atmosphérique.
int correctionBME280  = 11;                           // Correction de la PA en fonction de l'altitude de la station (+ 1hPA tous les 8 m).
int idxAltitude       = 0;                            // Index du Device de distance.


// Initialisation du BME280
Adafruit_BME280 bme;

// float temperature, humidity, pressure, altitude;
#define SEALEVELPRESSURE_HPA (1013.25)

void init_bme() {
  bme.begin(0x76);          // 0x76 = I2C adresse
}

void getDataBME280() {
  // Relevé et envoi du BM280 (Pression atmosphérique)
  String temperature  = String(bme.readTemperature());
  String humidity     = String(bme.readHumidity());
  int pressure        = (bme.readPressure() / 100.0F) + correctionBME280;
  String altitude     = String(bme.readAltitude(SEALEVELPRESSURE_HPA) * 100);
  
  int bar_for         = 0;
  // Calcul de BAR_FOR (0 = No info; 1 = Soleil; 6 = Partiellement nuageux; 3 = Variable; 4 = Pluie)
  if (pressure < 980) { bar_for = 4; }
  else if (pressure < 1000) { bar_for = 6; }
  else if (pressure < 1020) { bar_for = 3; } 
  else if (pressure >= 1020) { bar_for = 1; }
  else { bar_for = 0; }
  // Envoi des données à Domoticz via MQTT
  if ( idxBME280 != 0) {
    String svalue     = temperature + ";" + humidity + ";0;" + String(pressure) + ";" + String(bar_for);          // svalue = TEMP;HUM;HUM_STAT;BAR;BAR_FOR
    Serial.print("BME280 : svalue = "); Serial.print(svalue); Serial.print(" (TEMP;HUM;HUM_STAT;BAR;BAR_FOR)"); // Message pour débug en console
    SendData("udevice", idxBME280, 0, svalue); 
  }
  if ( idxPA != 0) {
    String svalue     = String(pressure) + ";" + String(bar_for);                                                 // svalue = BAR;BAR_FOR
    Serial.print("BME280 : svalue = "); Serial.print(svalue); Serial.print(" (BAR;BAR_FOR)");                   // Message pour débug en console
    SendData("udevice", idxPA, 0, svalue); 
  }
  if ( idxAltitude != 0) {
    Serial.print("Altitude : svalue = "); Serial.print(altitude); Serial.print(" (Distance en cm)");
    SendData("udevice", idxAltitude, 0, altitude);        
  }
}
