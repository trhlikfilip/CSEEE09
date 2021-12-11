#include "ph.h"
#include <Arduino.h>

void phSetup() {

}

float phLoop() {
  return (float)random(4000)/1000.0 + 5;
}
