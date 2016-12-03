/**
 * Declear global variable.
 * All variable declear here can be access
 * from any function below.
 */

const int ledPin = 13;
int ledState = LOW;
long previousMillis = 0;
long interval = 1000;     // in milliseconds

void setup() {
  // set the digital pin as output
  pinMode(ledPin, OUTPUT);

}

void loop() {
  // local variable
  // It available in this function only.
  // set current state
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis > interval) {
    // save current state
    previousMillis = currentMillis;

    // if the LED if off turn it on and vice-versa
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

    // set the LED with ledState variable
    digitalWrite(ledPin, ledState);
  }
}
