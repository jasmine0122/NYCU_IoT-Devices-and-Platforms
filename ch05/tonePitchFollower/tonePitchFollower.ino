
/*
  Pitch follower

  Plays a pitch that changes based on a changing analog input

  circuit:
  - 8 ohm speaker on digital pin 9
  - photoresistor on analog 0 to 5V
  - 4.7 kilohm resistor on analog 0 to ground

  created 21 Jan 2010
  modified 31 May 2012
  by Tom Igoe, with suggestion from Michael Flynn

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/tonePitchFollower
*/
int pushButton = 2;
int melody[10];
int play = 1;
int count = 0;
int bs = 0;
int ls = 0;
int lastButtonState = 0;   // the previous reading from the input pin
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50  ;// the debounce time; increase if the output flickers

void setup() {
  // initialize serial communications (for debugging only):
  Serial.begin(9600);
  pinMode(pushButton, INPUT);
  for (int i = 0; i < 10; i++)
    melody[i] = 0;
}

void loop() {
  // read the sensor:
  int reading = analogRead(A0);
  int buttonState = digitalRead(pushButton);
  delay(10);
  //Serial.println(buttonState);

  if (buttonState == 1 && lastButtonState != buttonState && play == 1) {
    melody[count] = map(reading, 0, 1023, 120, 1500);
    //Serial.println(lastButtonState);
    Serial.print(count + 1);
    Serial.print(":");
    Serial.println(melody[count]);
    count += 1;
  }
  lastButtonState = buttonState;

  if (count == 10)
  {
    Serial.println("<First>");
    // play the pitch:
    for (int i = 0; i < 10; i++)
    {
      Serial.println(melody[i]);
      tone(8, melody[i], 10);
      delay(100);
    }
    play = 0;
    count = 0;
  }

  if (buttonState != ls) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (buttonState != bs) {
      bs = buttonState;
      Serial.println(bs);
    }
    if (bs == HIGH && ((millis() - lastDebounceTime) > 5000)) {
      lastDebounceTime = millis();
      Serial.println("<Reapeat>");
      for (int i = 0; i < 10; i++)
      {
        Serial.println(melody[i]);
        tone(8, melody[i], 10);
        delay(100);
      }
    }

  }
  ls = buttonState;
  delay(10);
  // delay in between reads for stability
}
