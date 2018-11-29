#include <Servo.h>

Servo servo;
void setup() {
  // put your setup code here, to run once:
   pinMode(7,OUTPUT);
  servo.attach(7);
  servo.write(180);
}

void loop() {
  // put your main code here, to run repeatedly:

  servo.write(0);
  
  servo.write(180);
}
