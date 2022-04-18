#define trigPin 7
#define echoPin 6
int pushButton = 2;
long duration, distance;
int count = 0;


void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(pushButton, INPUT);
}


void loop() {
  int buttonState = digitalRead(pushButton);
  if (buttonState == 1 && lastButtonState != buttonState) {
    count += 1;
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = duration / 58.2;
    Serial.println(distance);
    if (count == 1)
      long AC = distance;
    else if (count == 2)
      long BC = distance;
    else{
      count = 0;
      AC = 0;
      BC = 0;
    }
  }
  lastButtonState = buttonState;





  delay(50);
}
