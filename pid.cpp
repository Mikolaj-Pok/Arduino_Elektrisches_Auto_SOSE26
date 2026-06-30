#include "pid.hpp"

float pid(pid_settings_t &s, float soll, float in) {
  //code needs to be added here
 float pid = 0.0;
  float current_error = soll - in;
  
  //Proportional part
  float u_P = s.p * current_error;
  
  //Integral part
  

  //Differential part
  float u_D = s.d * ((current_error-last_error)/T)

  //PID 
  float pid = u_P + u_I + u_D;

  last_error = current_error;
  reset_integrator(&s);
  //pid=s.p+s.i+s.d; so richtig?
  return pid;
}

void reset_integrator(pid_settings_t &s) {
  //code needs to be added here

  s.i=0; //sets the integral sum-value back to zero

}
