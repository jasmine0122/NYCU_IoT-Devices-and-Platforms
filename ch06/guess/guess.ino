int answer;
int buttonState = 0;
int lastButtonState = 0; 
const int sensorPin = A0;    // pin that the sensor is attached to

// variables:
int sensorValue = 0;         // the sensor value
int sensorMin = 1023;        // minimum sensor value
int sensorMax = 0;           // maximum sensor value

void setup() {
  // initialize the serial communication:
  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(9, OUTPUT);
}

void loop() {
  // send the value of analog input 0:
  while (Serial.available() > 0) {
    int guess = Serial.parseInt();
    if (Serial.read() == '\n') {
      Serial.println(guess);
      if (guess == answer){
        digitalWrite(9, HIGH);
        Serial.println("Yes");    
      }
      else if(guess > answer){
        digitalWrite(9, LOW);
        Serial.println("too large");
      }
      else{
        digitalWrite(9, LOW);
        Serial.println("too small");
      }
    }
  }
  buttonState = digitalRead(2);
  if (buttonState != lastButtonState && buttonState == HIGH) {
    answer = map(constrain(analogRead(A0), 0, 1023), 0, 1023, 0, 10);
    //Serial.println(answer);
    delay(50); 
  }
  lastButtonState = buttonState;
  delay(2);
}
