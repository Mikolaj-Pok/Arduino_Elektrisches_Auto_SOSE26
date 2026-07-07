#include "sensor.hpp"
#include <stdlib.h>
#include "Arduino.h"

void sensor_setup(sensor_settings_t &s) {
  //code needs to be added here

  pinMode(s.pin, INPUT);
  s.avg.pos=0; //position in measurment-array set to zero
  s.avg.sum=0; //sum of values set to zero
  unsigned int first = analogRead(s.pin);
  for (int i=0; i < AVG_SIZE ; i++){
    s.avg.measurements[i]=first; //fills the measurments-array with zeros 
  } 

}

void sensor_read(sensor_settings_t &s) {
  //code needs to be added here

  s.avg.sum = s.avg.sum - s.avg.measurements[s.avg.pos]; // deletes the oldest value in the sum to make space for a new measurement

  unsigned int new_measurement = analogRead(s.pin); // new measurement from the sensor pin is saved in a variable

  s.avg.measurements[s.avg.pos] = new_measurement; // the deleted value from the sum is overwritten by a new measurement

  s.avg.sum = s.avg.sum + new_measurement; //add the new measurement to the sum

  s.avg.pos++; // increments the position in the array

  if (s.avg.pos >= AVG_SIZE){ 
    s.avg.pos =0; // if the end is reached, return to the beginning of the array
  }

  s.value= (float)s.avg.sum/(float)AVG_SIZE; //calculate the sensor value

}
