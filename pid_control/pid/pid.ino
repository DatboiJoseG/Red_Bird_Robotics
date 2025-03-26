#include <cstdlib>

int encoder1_in1 = 24;
int encoder1_in2 = 25;

int encoder1_in3 = 26;
int encoder1_in4 = 27;

int encoder1_ena = 2;
int encoder1_enb = 3;

int encoder2_in1 = 28;
int encoder2_in2 = 29;

int encoder2_in3 = 30;
int encoder2_in4 = 31;

int encoder2_ena = 4;
int encoder2_enb = 5;

int motorSpeed = 200;

int circum = 180;

volatile int encoder_ticks;
volatile int current_tick = 0;

int sen_pin = 7;

int ticks_per_revo = 30;

//Proposed PID Control for Forward Method;
void pidForward(int ticks){
  int current_tick = 0;
  float kp = 0.9;
  float ki = 0.1;
  float kd = 0.3;
  //We have implemented a long long error as
  //the integral summation of error over the
  //course of program execution will accumulate
  //exponentially.
  long long int total_error = 0;
  //Value of differentiation with respect to
  //change in error of system will be calculated
  //each tenth of a second in our system.

  //Placeholder values for error in previous iteration
  //of system heuristic and differential calculation
  //in change of error initialized to 0 in our method
  //execution.
  int last_error = 0;
  int delta_error = 0;
  while(current_tick < ticks){
    current_tick = readEncoder();
    int error = ticks - current_tick;
    total_error += error;
    delta_error = error - last_error;
    float speed = kp*error + ki*total_error * kd*delta_error;
    forward(speed);
    last_error = error;
    delay(100);
  }
  stop();
}

//Proposed PID Control for Backward Method;
void pidBackward(int ticks){
  int current_tick = 0;
  float kp = 0.9;
  float ki = 0.1;
  float kd = 0.3;
  //We have implemented a long long error as
  //the integral summation of error over the
  //course of program execution will accumulate
  //exponentially.
  long long int total_error = 0;
  //Value of differentiation with respect to
  //change in error of system will be calculated
  //each tenth of a second in our system.

  //Placeholder values for error in previous iteration
  //of system heuristic and differential calculation
  //in change of error initialized to 0 in our method
  //execution.
  int last_error = 0;
  int delta_error = 0;
  while(std::abs(current_tick) < ticks){
    current_tick = std::abs(readEncoder());
    int error = ticks - current_tick;
    total_error += error;
    delta_error = error - last_error;
    float speed = kp*error + ki*total_error * kd*delta_error;
    backward(speed);
    last_error = error;
    delay(100);
  }
  stop();
}

int readEncoder() {
  noInterrupts();
  int current_tick = encoder_ticks;
  encoder_ticks = 0;
  interrupts();

  return current_tick;
}

float num_ticks(int distance) { //on god pls provide milimeters
  return round((distance/circum) * ticks_per_revo); 
}

void forward() {
    //motor 1
  analogWrite(encoder2_ena, motorSpeed);
  digitalWrite(encoder2_in1, HIGH);
  digitalWrite(encoder2_in2, LOW);

  //motor 2
  analogWrite(encoder2_enb, motorSpeed);
  digitalWrite(encoder2_in3, HIGH);
  digitalWrite(encoder2_in4, LOW);

  //motor3
  analogWrite(encoder1_ena, motorSpeed);
  digitalWrite(encoder1_in2, HIGH);
  digitalWrite(encoder1_in1, LOW);

  //motor 4
  analogWrite(encoder1_enb, motorSpeed + 30);
  digitalWrite(encoder1_in3, HIGH);
  digitalWrite(encoder1_in4, LOW);
}

void backward() {
  //motor 1
  analogWrite(encoder2_ena, motorSpeed);
  digitalWrite(encoder2_in2, HIGH);
  digitalWrite(encoder2_in1, LOW);

  //motor 2
  analogWrite(encoder2_enb, motorSpeed);
  digitalWrite(encoder2_in4, HIGH);
  digitalWrite(encoder2_in3, LOW);

  //motor3
  analogWrite(encoder1_ena, motorSpeed);
  digitalWrite(encoder1_in1, HIGH);
  digitalWrite(encoder1_in2, LOW);

  //motor 4
  analogWrite(encoder1_enb, motorSpeed + 30);
  digitalWrite(encoder1_in4, HIGH);
  digitalWrite(encoder1_in3, LOW);
  
}

void spin() {
  //motor 1
  analogWrite(encoder2_ena, motorSpeed);
  digitalWrite(encoder2_in2, HIGH);
  digitalWrite(encoder2_in1, LOW);

  //motor 2
  analogWrite(encoder2_enb, motorSpeed);
  digitalWrite(encoder2_in3, HIGH);
  digitalWrite(encoder2_in4, LOW);

  //motor3
  analogWrite(encoder1_ena, motorSpeed);
  digitalWrite(encoder1_in2, HIGH);
  digitalWrite(encoder1_in1, LOW);

  //motor 4
  analogWrite(encoder1_enb, motorSpeed + 30);
  digitalWrite(encoder1_in4, HIGH);
  digitalWrite(encoder1_in3, LOW);
}

void stop() {
  analogWrite(encoder1_ena, 0);
  analogWrite(encoder1_enb, 0);
  analogWrite(encoder2_ena, 0);
  analogWrite(encoder2_enb, 0);

  digitalWrite(encoder2_in2, LOW);
  digitalWrite(encoder2_in1, LOW);
  digitalWrite(encoder2_in4, LOW);
  digitalWrite(encoder2_in3, LOW);
  digitalWrite(encoder1_in2, LOW);
  digitalWrite(encoder1_in1, LOW);
  digitalWrite(encoder1_in4, LOW);
  digitalWrite(encoder1_in3, LOW);
}

void setup(){
  pinMode(encoder1_in1, OUTPUT);
  pinMode(encoder1_in2, OUTPUT);
  pinMode(encoder1_in3, OUTPUT);
  pinMode(encoder1_in4, OUTPUT);
  pinMode(encoder2_in1, OUTPUT);
  pinMode(encoder2_in1, OUTPUT);
  pinMode(encoder2_in1, OUTPUT);
  pinMode(encoder2_in1, OUTPUT);
}

void loop(){

}