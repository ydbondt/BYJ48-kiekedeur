#include "kiekedeur.h"
Kiekedeur deur;

void setup() {
  
}

void loop() {
  deur.open();
  delay(4000);
  deur.toe();
  delay(4000);
}

