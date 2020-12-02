#include <Arduino.h>
#include "wifi.h"

// Appel de la bibliothéque NTP
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 3600, 60000);


// CONNEXION WIFI
// **************
void setup_wifi() {
  // Connexion au réseau Wifi
  delay(10);
  Serial.println();
  Serial.print("Connection au réseau : ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);            // Passage de la puce en mode client
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    // Tant que l'on est pas connecté, on boucle.
    delay(500);
    Serial.print(".");
  }
  // Initialise la séquence Random
  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connecté");
  Serial.print("Addresse IP : ");
  Serial.println(WiFi.localIP());
}

// CONNEXION NTP
// *************
void NTP_setup(){
  // Begin du NTP
  timeClient.begin();
}

int NTP_heures() {
  // Retour int de l'heure NTP
  timeClient.update();
  return timeClient.getHours();
}

int NTP_minutes(){
  // Retour int des minutes NTP
  timeClient.update();
  return timeClient.getMinutes();
}
