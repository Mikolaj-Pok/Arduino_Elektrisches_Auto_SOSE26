#include "servo.hpp"
#include <Servo.h>
#include "Arduino.h"


Servo servo_object;

void servo_setup(servo_settings_t &s) {
  //code needs to be added here
  servo_object.attach(s.pin);
  sgvsgrsvfehtehtbehteht
  pinMode(s.pin, OUTPUT);
}


void servo_set_position(servo_settings_t &s, int pos) {
  //code needs to be added here
  int micro_pos = s.full_left + (s.full_right - s.full_left) * pos/180;
  servo_object.writeMicroseconds(micro_pos); 

}

void servo_test(servo_settings_t &s) {
  //code needs to be added here
  fahr nach links, setz wert, fahr nachts rechts, setzt wert, setz center in der mitte, fahr zu center
  
}
