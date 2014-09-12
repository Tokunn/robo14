#include <Servo.h>

Servo myservo;
int pos;
int servopin = 9;


void setup() {
    pinMode(servopin, OUTPUT);
    myservo.attach(servopin);
    myservo.write(0);
}


void loop() {
    for(pos = 0; pos <= 90; pos += 1) {
        myservo.write(pos);
        delay(5);
    }
    for(pos = 180; pos>=0; pos -= 1) {
        myservo.write(pos);
        delay(5);
    }
    delay(3000);
}
