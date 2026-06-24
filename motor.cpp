#include "motor.hpp"
#include "Arduino.h"


void motor_setup(motor_settings_t &s) {

  pinMode(s.pin, OUTPUT);

}

void motor_set_speed(motor_settings_t &s, unsigned int speed) {

  if (speed>s.max_speed){
    speed=s.max_speed;
  }

  else if (speed<s.min_speed && speed>0){
   speed=s.min_speed;
  }

  analogWrite(s.pin, speed);
  
}
