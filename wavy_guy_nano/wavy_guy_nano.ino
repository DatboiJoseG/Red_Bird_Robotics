#include <Wire.h>
#include <FaBo9Axis_MPU9250.h>
#include <math.h>
#include <Servo.h>

FaBo9Axis fabo_9axis;
Servo testServo;

void setup() {
  Serial.begin(9600);
  Serial.println("RESET");
  Serial.println();
  Serial.println("configuring device.");
  if (fabo_9axis.begin()) {
    Serial.println("configured FaBo 9Axis I2C Brick");
  } else {
    Serial.println("device error");
    while(1);
  }

  testServo.attach(9);

}

void loop() {
  float mx,my,mz;
  float magnet_magn;
  fabo_9axis.readMagnetXYZ(&mx,&my,&mz);
  magnet_magn = sqrt(mx*mx + my*my + mz*mz ); //Calculate magnitude, or length, of magnetic vector.
  Serial.print("Magnitude of magnet:");
  Serial.println(magnet_magn);
  delay(2500);
  //If magnitude or length of magnetic vector is greater than 100, or powerful, than run test servo motor.
if (magnet_magn > 100) {
  testServo.write(180);
  delay(300);
  testServo.write(90);
  delay(250);
}
  delay(100);
}