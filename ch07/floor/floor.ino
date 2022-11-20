#include <Adafruit_BMP085.h>

const int redPin = 8;
const int greenPin = 9;
const int bluePin = 10;
const int  buttonPin = 2;
int buttonState = 0;
int lastButtonState = 0;
int count=0;
int firstfloor=0;
int floordiff=0;
int whichfloor=0;


Adafruit_BMP085 bmp;
  
void setup() {
  Serial.begin(9600);
  
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(buttonPin, INPUT);
  
  if (!bmp.begin()) {
  Serial.println("Could not find a valid BMP085 sensor, check wiring!");
  while (1) {}
  }
}




void loop() {
    buttonState = digitalRead(buttonPin);
             // Serial.println(bmp.readAltitude());
    if (buttonState != lastButtonState){
      
      if (buttonState == HIGH){
        count++;
        if(count == 1){
          firstfloor = bmp.readAltitude();
          Serial.print("first = ");
          Serial.println(firstfloor);
        }else if(count == 2){
          floordiff = bmp.readAltitude() - firstfloor;
          Serial.print("diff = ");
          Serial.println(floordiff);
        }else{
          whichfloor = (bmp.readAltitude() - firstfloor)/floordiff + 1;
               Serial.print("whichfloor = ");
     Serial.println(whichfloor);
        }
        delay(500);
        Serial.print("count = ");
        Serial.println(count);
        
      }
    }
    lastButtonState = buttonState;


    if(whichfloor == 1){
      analogWrite(redPin, 255);
      analogWrite(greenPin, 0);
      analogWrite(bluePin, 0);
    }else if(whichfloor == 2){
      analogWrite(redPin, 0);
      analogWrite(greenPin, 255);
      analogWrite(bluePin, 0);
    }else if(whichfloor == 3){
      analogWrite(redPin, 0);
      analogWrite(greenPin, 0);
      analogWrite(bluePin, 255);
    }
}
