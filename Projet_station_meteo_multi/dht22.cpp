#include <Arduino.h>
#include "dht22.h"
#include "mqtt.h"

// Variables Index Domoticz. (Mettre IDX = 0 si pas de device).
int idxDHT22          = 63;                           // Index du Device de température et humidité.
int idxTempRessenti   = 65;                           // Index du Device de température ressenti (fonction de la température et de l'humidité du DHT22).

// Variables techniques :
#define DHTPIN D4                                     // PIN digital de connexion DATA du DHT22
#define DHTTYPE DHT22                                 // Définition du type de DHT utilisé

// On intégre les librairies necessaires aux Capteurs.
#include <DHT.h>

// Initialisation du DHT
DHT dht(DHTPIN, DHTTYPE);

void init_dht() {
  dht.begin();              // Initialisation du capteur DHT  
}

 void getDataDHT() {
  // Relevé et envoi du DHT11 ou DHT22 (Température et humidité)
  float hum   = dht.readHumidity();                         // Lecture de l'humidité
  float temp  = dht.readTemperature();                      // Lecture de la temperature en degrés Celsius (par défaut)

  // Si on a des données, on envoi à Domoticz 
  if (isnan(hum) || isnan(temp)) {
    // On établi le degré de confort
    int hum_status = 0;
    if ((hum >= 45) and (hum <= 70))      { hum_status = 1; } // confortable
    else if ((hum >= 30) and (hum < 45))  { hum_status = 0; } // Normal
    else if (hum < 30)                    { hum_status = 2; } // sec
    else if (hum > 70)                    { hum_status = 3; } // humide
                  
    if ( idxDHT22 != 0) {
      String svalue =  String(temp,1) + ";" + String(hum,0) + ";" + String(hum_status);
      Serial.print("DHT22 : svalue = "); Serial.print(svalue); Serial.print(" (TEMP;HUM;HUM_STAT)");
      SendData("udevice", idxDHT22, 0, svalue);
    }
      
    if ( idxTempRessenti != 0) {
      String svalue2 = String(dht.computeHeatIndex(temp, hum, false),1);   // Calcul de l'indice de chaleur en Celsius - Température ressenti (isFahreheit = false)
      Serial.print("DHT22 Temp Ressenti : svalue = "); Serial.print(svalue2); Serial.print(" (TEMP)");
      SendData("udevice", idxTempRessenti, 0, svalue2);
    } 
  }
}
