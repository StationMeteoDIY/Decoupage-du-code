#include <Arduino.h>
#include "ota.h"
#include "connect.h"

// On intégre les bibliothéques necessaire à la mise à jour via OTA.
#include <ESP8266mDNS.h>
#include <ArduinoOTA.h>


// INITIALISATION Arduino OTA
// **************************
void initOTA() {
  /* Port par defaut = 8266 */
  // ArduinoOTA.setPort(8266);

  /* Hostname, par defaut = esp8266-[ChipID] */
  ArduinoOTA.setHostname(nomModule);

  /* Pas d'authentication par defaut */
  // ArduinoOTA.setPassword("admin");

  /* Le mot de passe peut également être défini avec sa valeur md5 */
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");
  
  // code à exécuter au démarrage de la mise à jour
  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH)
      type = "sketch";
    else // U_SPIFFS
      type = "filesystem";

    // NOTE: si vous mettez à jour SPIFFS, démonter SPIFFS à l'aide de SPIFFS.end ()
    Serial.println("Début de update " + type);
  });
  
  // code à exécuter à la fin de la mise à jour
  ArduinoOTA.onEnd([]() {
    Serial.println("\nFin");
  });
  
  // code à exécuter pendant la mise à jour
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progression : %u%%\r", (progress / (total / 100)));
  });
  
  // code à exécuter en cas d'erreur de la mise à jour
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Erreur[%u] : ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Authentification Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Exécution Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connexion Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Réception Failed");
    else if (error == OTA_END_ERROR) Serial.println("Fin Failed");
  });
  
  ArduinoOTA.begin();
  Serial.println("Prêt");
  Serial.print("Adresse IP : ");
  Serial.println(WiFi.localIP());
}

void maj_ota() {
   ArduinoOTA.handle();                            // On verifie si une mise a jour OTA nous est envoyée. Si OUI, la lib ArduinoOTA se charge de faire la MAJ.
}
