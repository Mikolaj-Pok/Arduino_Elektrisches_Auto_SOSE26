#include "pid.hpp"

float pid(pid_settings_t &s, float soll, float in) {
  //code needs to be added here
  float pid = 0.0;
  float current_error = soll - in;
  s.sum_error += current_error;


  //Proportional part
  float u_P =  s.p * current_error;
  
  //Integral part
  float u_I = s.i * s.integral * s.sum_error;

  //Differential part
  float u_D = s.d * ((current_error-last_error)/s.integral);

  //PID 
  float pid = u_P + u_I + u_D;

  s.last_error = current_error;
 
  return pid;
}

void reset_integrator(pid_settings_t &s) {
  //code needs to be added here
  s.sum_error = 0.0;
  s.last_error = 0.0;
}
