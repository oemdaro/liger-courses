/*
 * This code was Created by Jonathan Pereira on 10th February 2016 and is in the public domain.
 * Comment the type of wave that you do not wish to generate.
 * 
 * Modified by: Daro Oem
 * Modified date: December 03, 2016
*/

const float pi = 3.14159;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  //Single sinusoid wave
  float angle = 0;
  for(angle=0; angle<=360; angle=angle+5) {
    float rad = angle * (pi / 180);
    float sina = sin(rad);
    Serial.println(sina);
    delay(1);
  }

  //Sine Wave & Cosine Wave
//  float angle = 0;
//  for(angle=0; angle<=90; angle=angle+0.1) {
//    float sina = sin(angle);
//    float cosa = cos(angle);
//    Serial.print(sina);
//    Serial.print(" ");
//    Serial.println(cosa);
//    delay(1);
//  }

  //Sawtooth Wave
//  for(float i=0; i<=90; i=i+1) {
//    Serial.println(i);
//    delay(1);
//  }



  //Square Wave
//  for(int a=0; a<=100; a++) {
//    int b=0;
//    Serial.println(b);
//    delay(1);  
//  }
//  for(int a=0; a<=100; a++) {
//    int b=100;
//    Serial.println(b);
//    delay(1);  
//  }


  //Triangular wave
//  for(float i=0; i<=100; i=i+1) {
//    Serial.println(i);
//    delay(1);
//  }
//  for(float i=100; i>=0; i=i-1) {
//    Serial.println(i);
//    delay(1);  
//  }

}
