#include "pid.hpp"

float pid(pid_settings_t &s, float soll, float in) {
  //code needs to be added here
  float pid = 0.0;
  

  //pid=s.p+s.i+s.d; so richtig?
  return pid;
}

void reset_integrator(pid_settings_t &s) {
  //code needs to be added here

  s.i=0; //sets the integral sum-value back to zero

}