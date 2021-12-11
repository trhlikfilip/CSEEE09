#include <Arduino.h>
#include "spin.h"
void spinSetup() {

}

unsigned long spinLoop() {
  return (float)random(1000)/10.0 + 400.0; 
}
