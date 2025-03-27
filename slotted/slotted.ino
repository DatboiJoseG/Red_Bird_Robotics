#include <Servo.h>

//////////////////////////////// MOTOR /////////////////////////////////
//Motor 1
int encoder2_in1 = 28;
int encoder2_in2 = 29;
int encoder2_ena = 4;

//Motor 2
int encoder2_in3 = 30;
int encoder2_in4 = 31;
int encoder2_enb = 5;

//Motor 3
int encoder1_in1 = 24;
int encoder1_in2 = 25;
int encoder1_ena = 2;

//Motor 4
int encoder1_in3 = 26;
int encoder1_in4 = 27;
int encoder1_enb = 3;

///////////////////////////////////////// SLOTTED /////////////////////////////////
int motorSpeed = 150;

int circum = 180;

int ticks_per_revo = 30;

int sen_pin_x = 20; //pin has to be 2, 3, 18, 19, 20, 21 on the mega
int sen_pin_y =

volatile int encoder_ticks_x = 0;
int current_tick_x;

volatile int encoder_ticks_y = 0;
int current_tick_y;

int i = 0;

////////////////////////////////////////// BEACON DROP /////////////////////////////////////////////////
Servo myservo; 

int pos = 0;

////////////////////////////////////////// PHOTO-RESISTOR /////////////////////////////////////////////
const int PHOTORESISTOR_PIN = A0;

////////////////////////////////////////// COUNTING TICKS ////////////////////////////////////////////
void count_x() {
  Serial.println(encoder_ticks_x);
  volatile byte state = LOW;
  encoder_ticks_x += 1;
}

void count_y() {
  Serial.println(encoder_ticks_y);
  volatile byte state = LOW;
  encoder_ticks_y += 1;
}

int readEncoder(char axis) {
  noInterrupts();
  if (axis == "x"){

    int current_tick_x = encoder_ticks_x;

    interrupts();

    return current_tick_x;
  }
  else if (axis == "y") {
    int current_tick_x = encoder_ticks_y
      
    interrupts();

    return current_tick_y;
  }

}

int num_ticks(int distance) { //on god pls provide milimeters
  return (round((distance/circum) * ticks_per_revo)) * 2; 
}

///////////////////////////////////////////////// MOVING ////////////////////////////////////////
void forward(int distance) {
  int target_ticks = num_ticks(distance);
  Serial.println(target_ticks);
  encoder_ticks_x = 0;
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
  analogWrite(encoder1_enb, motorSpeed-75);
  digitalWrite(encoder1_in3, HIGH);
  digitalWrite(encoder1_in4, LOW);

  while (current_tick_x < target_ticks) {
    current_tick_x = readEncoder("x");
  }
  Serial.println("DONE");
  delay(100);
  stop();
}

void backward(int distance) {
  int target_ticks = num_ticks(distance);
  Serial.println(target_ticks);
  encoder_ticks_x = 0;

  // motor 1
  analogWrite(encoder2_ena, motorSpeed);
  digitalWrite(encoder2_in2, HIGH);
  digitalWrite(encoder2_in1, LOW);

  // motor 2
  analogWrite(encoder2_enb, motorSpeed);
  digitalWrite(encoder2_in4, HIGH);
  digitalWrite(encoder2_in3, LOW);

  // motor 3
  analogWrite(encoder1_ena, motorSpeed);
  digitalWrite(encoder1_in1, HIGH);
  digitalWrite(encoder1_in2, LOW);

  // motor 4
  analogWrite(encoder1_enb, motorSpeed);
  digitalWrite(encoder1_in4, HIGH);
  digitalWrite(encoder1_in3, LOW);

  while (current_tick_x < target_ticks) {
    current_tick = readEncoder();
  }
  Serial.println("DONE");
  delay(100);
  stop();
}

void to_one_side(int distance) {
  int target_ticks = num_ticks(distance);
  Serial.println(target_ticks);
  encoder_ticks_y = 0;

  // motor 1
  analogWrite(encoder2_ena, motorSpeed);
  digitalWrite(encoder2_in1, HIGH);
  digitalWrite(encoder2_in2, LOW);

  // motor 2
  analogWrite(encoder2_enb, motorSpeed);
  digitalWrite(encoder2_in4, HIGH);
  digitalWrite(encoder2_in3, LOW);

  // motor 3
  analogWrite(encoder1_ena, motorSpeed);
  digitalWrite(encoder1_in2, HIGH);
  digitalWrite(encoder1_in1, LOW);

  // motor 4
  analogWrite(encoder1_enb, motorSpeed);
  digitalWrite(encoder1_in4, HIGH);
  digitalWrite(encoder1_in3, LOW);

  while (current_tick_y < target_ticks) {
    current_tick_y = readEncoder("y");
  }
  Serial.println("DONE");
  delay(100);
  stop();
}

void to_the_other_side(int distance) {
  int target_ticks = num_ticks(distance);
  Serial.println(target_ticks);
  encoder_ticks_y = 0;

  // motor 1
  analogWrite(encoder2_ena, motorSpeed);
  digitalWrite(encoder2_in2, HIGH);
  digitalWrite(encoder2_in1, LOW);

  // motor 2
  analogWrite(encoder2_enb, motorSpeed);
  digitalWrite(encoder2_in3, HIGH);
  digitalWrite(encoder2_in4, LOW);

  // motor 3
  analogWrite(encoder1_ena, motorSpeed);
  digitalWrite(encoder1_in1, HIGH);
  digitalWrite(encoder1_in2, LOW);

  // motor 4
  analogWrite(encoder1_enb, motorSpeed);
  digitalWrite(encoder1_in3, HIGH);
  digitalWrite(encoder1_in4, LOW);

  while (current_tick_y < target_ticks) {
    current_tick_y = readEncoder("y");
  }
  Serial.println("DONE");
  delay(100);
  stop();
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

//////////////////////////////////////////////////////// SETUP AND LOOP /////////////////////////////////////////////////////////////////
void setup() {
  //Photo-resistor
  pinMode(PHOTORESISTOR_PIN, INPUT);

  //Count ticks
  Serial.begin(9600);
  pinMode(sen_pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(sen_pin_x), count_x, FALLING);
  attachInterrupt(digitalPinToInterrupt(sen_pin_y), count_y, FALLING);

  //Moving
  pinMode(encoder1_in1, OUTPUT);
  pinMode(encoder1_in2, OUTPUT);
  pinMode(encoder1_in3, OUTPUT);
  pinMode(encoder1_in4, OUTPUT);

  pinMode(encoder2_in1, OUTPUT);
  pinMode(encoder2_in2, OUTPUT);
  pinMode(encoder2_in3, OUTPUT);
  pinMode(encoder2_in4, OUTPUT);

  // //Beacon
  // myservo.attach(3);
}

void loop() {
  int lightLevel = analogRead(PHOTORESISTOR_PIN);

  if (lightLevel > 1000){

    int ticks = digitalRead(sen_pin);

    if (i == 0) {
      forward(180);
      // backward(180);
      // Serial.println("in loop");
    }
    else if (i != 0){
      Serial.println("loop ended");
    }

    i++;
  }


}
