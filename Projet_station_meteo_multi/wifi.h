#ifndef WIFI_H
#define WIFI_H

#include "connect.h"
#include "parametre.h"
#include <ESP8266WiFi.h> 
#include <NTPClient.h>
#include <WiFiUdp.h>

void setup_wifi();
void NTP_setup();
int NTP_heures();
int NTP_minutes();

#endif
