#ifndef traffic_light_H// this is the name of the library that opperates a trafi¿fic ligh and the peoples light
#define traffic_light_H
#include "arduino.h"
class traffic_light{
  private:
    float residuo(float i, float j);// this are interior functions
    void esperar(int g);
  public:
    traffic_light(int pin1, int pin2, int pin3, int pin4, int pin5, int pin6);// the code is public so they can change the duration of the lights to whatever they want
    int led_red; // this are variables that anyone can change
    int led_yellow;
    int led_green;
    int led_redp;
    int led_greenp;
    int puls;
};

#endif
