/*
  Controlling a servo position using a potentiometer (variable resistor)
  by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>
  modified on 8 Nov 2013
  by Scott Fitzgerald
  http://www.arduino.cc/en/Tutorial/Knob
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int potpin = A0;  // analog pin used to connect the potentiometer
int val, last = 0;    // variable to read the value from the analog pin
int direct = 1, degree = 0;
int sensorMin = 1023;        // minimum sensor value
int sensorMax = 0;           // maximum sensor value
int sensorValue = 0;

void setup() {
  Serial.begin(9600);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object

  while (millis() < 5000) {
    sensorValue = analogRead(potpin);
    // record the maximum sensor value
    if (sensorValue > sensorMax) {
      sensorMax = sensorValue;
    }

    // record the minimum sensor value
    if (sensorValue < sensorMin) {
      sensorMin = sensorValue;
    }
  }
}

void loop() {
  sensorValue = analogRead(potpin);

  // in case the sensor value is outside the range seen during calibration
  sensorValue = constrain(sensorValue, sensorMin, sensorMax);
  // apply the calibration to the sensor reading
  val = map(sensorValue, sensorMin, sensorMax, 0, 180);
  //Serial.println(val);
int val_m,d;
  val_m = (sensorMax - sensorValue);
  d = map(val_m, sensorMin, sensorMax, 0, 180);
  Serial.println(val);
  if(d>10 && d<10)
  degree = 0;
  else if (d > 90)
    degree -= 5;
  else if (d < 90)
    degree += 5;
  else if (d < 50)
    degree += 3;
  else if (d < 20)
    degree += 1;
  else if (d > 130)
    degree -= 3;
  else if (d > 160)
    degree -= 1;
  if (degree < 0)
    degree = 0;
  else if (degree > 180)
    degree = 180;
  Serial.print("degree: ");
  Serial.println(degree);
  myservo.write(degree);                  // sets the servo position according to the scaled value
  delay(100);                           // waits for the servo to get there
}
