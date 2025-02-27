int encoder1_in1 = 7;
int encoder1_in2 = 3;
int encoder1_in3 = 2;
int encoder1_in4 = 1;
int encoder1_ena = 6;
int encoder1_enb = 5;

int encoder2_in1 = 13;
int encoder2_in2 = 12;
int encoder2_in3 = 9;
int encoder2_in4 = 8;
int encoder2_ena = 11;
int encoder2_enb = 10;

int motorSpeed = 255;

void forward() {
    //motor 1
  analogWrite(encoder2_ena, motorSpeed);
  digitalWrite(encoder2_in1, HIGH);
  // delay(1000);
  // digitalWrite(encoder2_in1, LOW);
  // delay(5000);
  digitalWrite(encoder2_in2, LOW);

  //motor 2
  analogWrite(encoder2_enb, motorSpeed);
  digitalWrite(encoder2_in3, HIGH);
  digitalWrite(encoder2_in4, LOW);

  //motor3
  analogWrite(encoder1_ena, motorSpeed);
  digitalWrite(encoder1_in1, HIGH);
  digitalWrite(encoder1_in2, LOW);

  //motor 4
  analogWrite(encoder1_enb, motorSpeed);
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
  digitalWrite(encoder1_in2, HIGH);
  digitalWrite(encoder1_in1, LOW);

  //motor 4
  analogWrite(encoder1_enb, motorSpeed);
  digitalWrite(encoder1_in4, HIGH);
  digitalWrite(encoder1_in3, LOW);
}

void spin() {
  //motor 1
  analogWrite(encoder2_ena, motorSpeed);
  digitalWrite(encoder2_in1, HIGH);
  digitalWrite(encoder2_in2, LOW);

  //motor 2
  analogWrite(encoder2_enb, motorSpeed);
  digitalWrite(encoder2_in4, HIGH);
  digitalWrite(encoder2_in3, LOW);

  //motor3
  analogWrite(encoder1_ena, motorSpeed);
  digitalWrite(encoder1_in2, HIGH);
  digitalWrite(encoder1_in1, LOW);

  //motor 4
  analogWrite(encoder1_enb, motorSpeed);
  digitalWrite(encoder1_in3, HIGH);
  digitalWrite(encoder1_in4, LOW);
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

void setup() {
  // put your setup code here, to run once:
  pinMode(encoder1_in1, OUTPUT);
  pinMode(encoder1_in2, OUTPUT);
  pinMode(encoder1_in3, OUTPUT);
  pinMode(encoder1_in4, OUTPUT);

  pinMode(encoder2_in1, OUTPUT);
  pinMode(encoder2_in2, OUTPUT);
  pinMode(encoder2_in3, OUTPUT);
  pinMode(encoder2_in4, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  forward();
  delay(1000);
  stop();
  delay(2000);

  backward();
  delay(1000);
  stop();
  delay(2000);

  spin();
  delay(1000);
  stop();
  delay(2000);
}