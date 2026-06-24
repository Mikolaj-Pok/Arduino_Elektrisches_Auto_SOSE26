#include "sensor.hpp"
#include <stdlib.h>
#include "Arduino.h"

void sensor_setup(sensor_settings_t &s) {
  //code needs to be added here

  pinMode(s.pin, INPUT);

}

void sensor_read(sensor_settings_t &s) {
  //code needs to be added here

  
}