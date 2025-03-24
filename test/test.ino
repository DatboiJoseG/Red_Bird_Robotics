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

//////////////////////////////////////////////////

void encoderInterrupt() {
  // Serial.print(encoder_ticks);
  encoder_ticks++;
}

void setupEncoder() {
  pinMode(sen_pin, INPUT_PULLUP); //default to be HIGH, when interrupted -> LOW, count goes up
  attachInterrupt(digitalPinToInterrupt(sen_pin), encoderInterrupt, FALLING); //pin goes high to low, calls function, function counts
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

/////////////////////////////////////////////////

void forward(int distance) {
  int target_ticks = num_ticks(distance);
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

  while (current_tick < target_ticks) {
    current_tick = readEncoder();
  }
}

void backward(int distance) {
  int target_ticks = num_ticks(distance);
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

  while (current_tick < target_ticks) {
    current_tick = readEncoder();
  }
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

///////////////////////////////////////////////////////////////////

void setup() {
  setupEncoder();
}

///////////////////////////////////////////////////////////////////

void loop() {
  Serial.print("aaa");
  Serial.print("bbbb");
  forward(500);
  delay(1000);
  stop();
  delay(1000);

  backward(500);
  delay(1000);
  stop();
  delay(1000);

}

















