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
  .pin = 5,
  .full_left = 50,
  .full_right = 130,
  .center = 90
};

//the entries should not rearranged (compiler error)
motor_settings_t motor = {
  .pin = 3, 
  .max_speed = 50.0, //values range from 0 to 255 but above 100, the battery tends to shut off because the current gets too high
  .min_speed = 15.0 
};

//the entries should not rearranged (compiler error)
sensor_settings_t left_sensor = {
  .pin = A3,
  .value = 0,
  .avg = {}
};

//the entries should not rearranged (compiler error)
sensor_settings_t right_sensor = {
  .pin = A2,
  .value = 0,
  .avg = {}
};

//the entries should not rearranged (compiler error)
pid_settings_t direction_control = {
  .p = 3.5,
  .i = 0.0,
  .d = 2.0,
  .anti_windup = 50.0, //egal, integral unbenutzt
  .integral = 0.0,
  .last_error = 0.0
};

//the entries should not rearranged (compiler error)
pid_settings_t speed_control = {
  .p = 2.5,
  .i = 0.0,
  .d = 0.0,
  .anti_windup = 20.0,
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
  .pin = 2,
  .time_diff = 0.0,
  .last_time = 0.0
};

void setup() {
  //setup functions which tell the program where the Inputs/Outputs are and what the parameters are
  setup_uart();
  servo_setup(servo);
  motor_setup(motor);
  sensor_setup(left_sensor);
  sensor_setup(right_sensor);
  setup_speed_sense(speed_sense);
  uart_attach_servo(servo);
  uart_attach_settings(settings);
  uart_attach_motor(motor);
}

//interrupt for measuring speed from speed sensor
void speed_interrupt() {
  //TODO
  // attachInterrupt(digitalPinToInterrupt(pin), ISR, modus) interrupts the code
  // to measure the speed, continues the code afterwards

  unsigned long current_time=millis(); //millis(): return the passed time in milliseconds since the start of the code
  speed_sense.time_diff=current_time-speed_sense.last_time;
  speed_sense.last_time=current_time;

}

float aktueller_fehler= 0.0;
float direction= 0.0;
float lenkwinkel= 90.0;
int v_soll= (int) motor.max_speed;
//float geschwindigkeit=0.0;
//float v_last = motor.max_speed;
float fehler_betrag=0.0;
float letzter_fehler_betrag = 0.0;
float fehler_aenderung=0.0;
float bremskraft=0.0;

void loop() {

 
  sensor_read(left_sensor);
  sensor_read(right_sensor);

  aktueller_fehler = (float)left_sensor.value - (float)right_sensor.value; //maximum value ~  8 ; float cast solves underflow with unsigned floats
  if(abs(aktueller_fehler) < 1.0){
    aktueller_fehler = 0.0;  //Threshold for minimal errors, shall prevent jittering
      }
  
  direction = pid(direction_control, 0.0, aktueller_fehler);

  lenkwinkel= servo.center + direction;

  lenkwinkel= constrain(lenkwinkel, servo.full_left, servo.full_right);
  
  servo_set_position(servo, lenkwinkel);

aktueller_fehler = (float)left_sensor.value - (float)right_sensor.value;
if(abs(aktueller_fehler) < 2.0){
    aktueller_fehler = 0.0;
}

fehler_betrag = abs(aktueller_fehler);

fehler_aenderung = fehler_betrag - letzter_fehler_betrag;
if (fehler_aenderung < 0) {
    fehler_aenderung = 0; 
}

bremskraft = (1.5 * fehler_betrag) + (3.5 * fehler_aenderung); // P- und D-Teil

v_soll = (int)(motor.max_speed - bremskraft);
v_soll = constrain(v_soll, (int)motor.min_speed, (int)motor.max_speed);

motor_set_speed(motor, (unsigned int)v_soll);

letzter_fehler_betrag = fehler_betrag;

/* ZWISCHEINSPEICHER LETZTER CODE
  //the larger the current error, the slower the car should go
  v_soll = (int) (motor.max_speed - 3 * abs(aktueller_fehler));
  v_soll = constrain(v_soll, (int) motor.min_speed, (int) motor.max_speed);
  motor_set_speed(motor, (unsigned int) v_soll);
*/

/*
  float v_ms=0.0;
  float v_kmh=0.0;
  //calculate Speed in km/h
  if (speed_sense.time_diff > 0.0) {
  float period_s = speed_sense.time_diff / 1000.0;   // millis → seconds
  float freq = 1.0 / period_s;                          // Hz
  const float radumfang = 0.1885;                       // Meter per rotation

  v_ms = freq * radumfang;                  // m/s
  v_kmh = v_ms * 3.6;                       // km/h
  }
*/
  /*
  v_soll = constrain(v_soll, (float) motor.min_speed, (float)motor.max_speed);
  geschwindigkeit = pid(speed_control, v_soll, v_last);
  geschwindigkeit = constrain(geschwindigkeit, (float) motor.min_speed, (float) motor.max_speed);
  v_last = geschwindigkeit; 
  */


  if (settings.plot_analog_readings) {
    sensor_read(left_sensor);
    Serial.print("Left_avg:");
    Serial.print(left_sensor.value);
    sensor_read(right_sensor);
    Serial.print(" ,Right_avg:");
    Serial.print(right_sensor.value);
    Serial.print(" ,Left:");
    Serial.print(analogRead(left_sensor.pin));
    Serial.print(" ,Right:");
    Serial.print(analogRead(right_sensor.pin));
    Serial.print(" ,Controller:");
    Serial.print(direction);
    Serial.print(" ,Fehler");
    Serial.print(aktueller_fehler);
    Serial.print(" ,Geschwindigkeit");
    Serial.print(v_soll);
    Serial.println("");
    /* Serial.print("Speed:");
    Serial.print(digitalRead(speed_sense.pin));
    Serial.print('\n'); */
    delay(50);
  }

  //code needs to be added here
  
  handle_serial_input();
}
