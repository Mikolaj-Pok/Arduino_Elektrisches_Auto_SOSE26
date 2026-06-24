//This file needs value modifications
#pragma once
#define AVG_SHIFT 0
#define AVG_SIZE (1<<(AVG_SHIFT))

struct moving_average{
  unsigned int pos;           //Position within array
  unsigned int sum;           //Sum of values
  unsigned int measurements[AVG_SIZE]; //Array of measurements
};

struct sensor_settings_t{
  unsigned int pin;        //Pin the sensor is connected to
  unsigned int value;      //The averaged value of the sensor reading
  moving_average avg;      //Pointer to the moving average
};

void sensor_setup(sensor_settings_t &s);
void sensor_read(sensor_settings_t &s);
