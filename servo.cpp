#include "servo.hpp"
#include <Servo.h>
#include "Arduino.h"


Servo servo_object;

void servo_setup(servo_settings_t &s) {
  //code needs to be added here
  servo_object.attach(s.pin);
 
  pinMode(s.pin, OUTPUT);
}


void servo_set_position(servo_settings_t &s, int pos) {
  //code needs to be added here
  //int micro_pos = map(pos, 0, 180, s.full_left, s.full_right);
  //servo_object.writeMicroseconds(micro_pos); 

  servo_object.write(pos);


}

void servo_test(servo_settings_t &s) {
  //code needs to be added here
  servo_object.writeMicroseconds(s.full_left);
  delay(1000);
  servo_object.writeMicroseconds(s.full_right);
  delay(1000);
  servo_object.writeMicroseconds(s.center);
  delay(1000);  
}
