#include <Arduino.h>
#include "hello.h"

void bonjour() {
  static int compteur = 0;
  compteur += 1;

  Serial.print(compteur);
  Serial.print(" - ");
  Serial.println("Bonjour ! ");
  
  delay(5000);
}
