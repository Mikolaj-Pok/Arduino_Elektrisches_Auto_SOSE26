#include "servo.hpp"
#include <Servo.h>
#include "Arduino.h"


Servo servo_object;

void servo_setup(servo_settings_t &s) {
  //code needs to be added here
  pinMode(s.pin, OUTPUT);
}


void servo_set_position(servo_settings_t &s, int pos) {
  //code needs to be added here
}

void servo_test(servo_settings_t &s) {
  //code needs to be added here
}