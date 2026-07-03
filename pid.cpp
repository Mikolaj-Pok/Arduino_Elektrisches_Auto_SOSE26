#include "pid.hpp"

float pid(pid_settings_t &s, float soll, float in) {
  //code needs to be added here
  float pid = 0.0;
  float current_error = soll - in;

  s.integral += current_error;


  //Proportional part
  float u_P =  s.p * current_error;
  
  //Integral part
  float u_I = s.i * s.integral ;
   if (u_I > s.anti_windup){
    u_I = s.anti_windup;
  }

  //Differential part
  float u_D = s.d * (current_error-s.last_error);

  //PID 
  pid = u_P + u_I + u_D;

  s.last_error = current_error;
 
  return pid;
}

void reset_integrator(pid_settings_t &s) {
  //code needs to be added here

  s.integral=0.0; //sets the integral sum-value back to zero
  s.last_error=0.0; //resets the error

>>>>>>> a4d30ec6a85848f8f383103652b488d3a89bbb80
}
