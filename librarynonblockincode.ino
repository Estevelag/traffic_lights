#include <traffic_light.h>
void setup(){
  Serial.begin(9600);
}
void loop() {
  traffic_light intento(6,7,2,3,4,5);
}
