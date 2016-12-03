/**
 * Math formular:
 * sensorValue = Vcc * (R1 / (R_sensor + R1))
 */

const int analogInPin = A0;
int sensorValue = 0;
//int outputValue = 0;

void setup() {
  Serial.begin(9600);

}

void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);

  // map it to the range of the analog out:
//  outputValue = map(sensorValue, 0, 1023, 0, 255);

  // print the results to the serial monitor:
  Serial.print("sensor = ");
  Serial.print(sensorValue);
//  Serial.print("\t output = ");
//  Serial.println(outputValue);

  // wait 2 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(2);
}
