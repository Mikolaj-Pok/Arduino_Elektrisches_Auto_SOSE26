#include "Arduino.h"
#include "motor.hpp"
#include "pid.hpp"
#include "sensor.hpp"
#include "servo.hpp"
#include "uart.hpp"
#include "system.hpp"
#include "speed_sens.hpp"

//the entries should not rearranged (compiler error)
servo_settings_t servo = {
  .pin = 0,
  .full_left = 0,
  .full_right = 0,
  .center = 0,
};

//the entries should not rearranged (compiler error)
motor_settings_t motor = {
  .pin = 3,
  .max_speed = 100,
  .min_speed = 0
};

//the entries should not rearranged (compiler error)
sensor_settings_t left_sensor = {
  .pin = 0,
  .value = 0,
  .avg = {}
};

//the entries should not rearranged (compiler error)
sensor_settings_t right_sensor = {
  .pin = 0,
  .value = 0,
  .avg = {}
};

//the entries should not rearranged (compiler error)
pid_settings_t direction_control = {
  .p = 0.0,
  .i = 0.0,
  .d = 0.0,
  .anti_windup = 0.0,
  .integral = 0.0,
  .last_error = 0.0
};

//the entries should not rearranged (compiler error)
pid_settings_t speed_control = {
  .p = 0.0,
  .i = 0.0,
  .d = 0.0,
  .anti_windup = 0.0,
  .integral = 0.0,
  .last_error = 0.0
};

//the entries should not rearranged (compiler error)
system_settings_t settings = {
  .off_track_detection = 0,
  .idle_speed = 0,
  .plot_analog_readings = false
};

speed_sense_settings_t speed_sense = {
  .pin = 0,
  .time_diff = 0,
  .last_time = 0
};

void setup() {
  setup_uart();
  servo_setup(servo);
  motor_setup(motor);
  sensor_setup(left_sensor);
  sensor_setup(right_sensor);
  
  setup_speed_sense(speed_sense);

}

//interrupt for measuring speed from speed sensor
void speed_interrupt() {
  //TODO
  //mit attachInterrupt(digitalPinToInterrupt(pin), ISR, modus) unterbricht man den Programmablauf,
  //um die geschwindigkeit zu messen, danach macht der Arduino normal weiter

  unsigned long current_time=micros(); //micros(): fragt die Zeit, die seit Programmstart vergangen ist, in Mikrosekunden ab.

  speed_sense.time_diff=current_time-speed_sense.last_time;
  speed_sense.last_time=current_time;

}

void loop() {

  //code needs to be added here
  
  float direction = 0;

  if (settings.plot_analog_readings) {
    Serial.print("Left_avg:");
    Serial.print(left_sensor.value);
    Serial.print(",Right_avg:");
    Serial.print(right_sensor.value);
    Serial.print(",Left:");
    Serial.print(analogRead(left_sensor.pin));
    Serial.print(",Right:");
    Serial.print(analogRead(right_sensor.pin));
    Serial.print(",Controller:");
    Serial.print(direction);
    Serial.println("");
    delay(50);
  }

  //code needs to be added here
  
  handle_serial_input();
}
