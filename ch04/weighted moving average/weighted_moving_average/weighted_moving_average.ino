/*
  Calibration

  Demonstrates one technique for calibrating sensor input. The sensor readings
  during the first five seconds of the sketch execution define the minimum and
  maximum of expected values attached to the sensor pin.

  The sensor minimum and maximum initial values may seem backwards. Initially,
  you set the minimum high and listen for anything lower, saving it as the new
  minimum. Likewise, you set the maximum low and listen for anything higher as
  the new maximum.

  The circuit:
  - analog sensor (potentiometer will do) attached to analog input 0
  - LED attached from digital pin 9 to ground through 220 ohm resistor

  created 29 Oct 2008
  by David A Mellis
  modified 30 Aug 2011
  by Tom Igoe
  modified 07 Apr 2017
  by Zachary J. Fields

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Calibration
*/
const int numReadings = 10;

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average

// These constants won't change:
const int sensorPin = A0;    // pin that the sensor is attached to
const int ledPin = 9;        // pin that the LED is attached to

// variables:
int sensorValue = 0;         // the sensor value
int sensorMin = 1023;        // minimum sensor value
int sensorMax = 0;           // maximum sensor value


void setup() {
  // turn on LED to signal the start of the calibration period:
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  Serial.begin(9600);
  // calibrate during the first five seconds
  while (millis() < 5000) {
    sensorValue = analogRead(sensorPin);

    // record the maximum sensor value
    if (sensorValue > sensorMax) {
      sensorMax = sensorValue;
    }

    // record the minimum sensor value
    if (sensorValue < sensorMin) {
      sensorMin = sensorValue;
    }
  }

  // signal the end of the calibration period
  digitalWrite(13, LOW);

}

int smoothing() {
  // subtract the last reading:
  //total = total - readings[readIndex];
  // read from the s`ensor:
  readings[readIndex] = sensorValue;

  total = 0;
  int index = readIndex;
  for (int i = 10; i > 0; i--)
  {
    // add the reading to the total:
    total = total + readings[index] * i;
    index--;
    if (index < 0)
      index = 9;
  }
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  // calculate the average:
  return total / 55;
}

int calibration() {
  // in case the sensor value is outside the range seen during calibration
  sensorValue = constrain(sensorValue, sensorMin, sensorMax);

  // apply the calibration to the sensor reading
  sensorValue = map(sensorValue, sensorMin, sensorMax, 0, 255);
}




void loop() {
  // read the sensor:
  sensorValue = analogRead(sensorPin);
  calibration();
  int smooth = smoothing();
  Serial.print("sensorValue:");
  Serial.println(sensorValue);

  Serial.print("smooth:");
  Serial.println(smooth);

  // fade the LED using the calibrated value:
  analogWrite(ledPin, abs(smooth - 255));

  delay(100);
}
