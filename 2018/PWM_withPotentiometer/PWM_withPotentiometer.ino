/*
  Reads an analog input on pin 9, prints the result to the Serial Monitor. Meant to run a motor. 
  More info on motor(PWM)values at "sensorValue=sensorValue" line.
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  http://www.arduino.cc/en/Tutorial/AnalogReadSerial
*/
#include<Servo.h>
Servo myservo;
Servo myservo2;

double sensorValue = 0;        //Doubled the sensor value so that you could get a reading on the Serial Monitor
int sensorOut = 0;             //This variable reads the value of the potentiometer and will display it on the serial monitor

void setup() {
  Serial.begin(9600);               // initialize serial communication at 9600 bits per second
                                    //Open the Serial Monitor under the Tools bar once the program is running and you can see the values of the potentiometer at various point 
  myservo.attach(10);               //assigns the servo called myservo to pin 10, which is also a PWM pin. PWM is better described at https://www.arduino.cc/en/Tutorial/PWM.
  myservo2.attach(9);                //assigns the servo called myservo to pin 9, which is also a PWM pin. PWM is better described at https://www.arduino.cc/en/Tutorial/PWM.
  myservo.writeMicroseconds(1500);  //This sets servo to mid-point of map range. Described better in void loop.
  
}


void loop() {
  sensorValue = analogRead(A1); // read the input on analog pin 0. This is your value from 0-1023.
  sensorOut = map(sensorValue, 0, 1023, 1000, 2000); //This changes the PWM values from 0-1023 to microsecond values. 700 is fully counter-clockwise and 2200 is fully clockwise.
  /*For more info on microseconds and the map function look here at https://www.arduino.cc/en/Reference/ServoWriteMicroseconds. 
  The map function is decribed further here at https://www.arduino.cc/reference/en/language/functions/math/map/.
  */

    Serial.println(sensorOut);                //Prints out the final value of the potentiometer to the Serial Monitor. 
    myservo.writeMicroseconds(sensorOut);     //If the switch state is low(actually high because of the inversion of INPUT_PULLUP), the servo will be set to the value of sensorOut(potentiometer) 
    myservo2.writeMicroseconds(sensorOut);     //If the switch state is low(actually high because of the inversion of INPUT_PULLUP), the servo will be set to the value of sensorOut(potentiometer) 

//  Serial.println(sensorValue);                //Prints out the final value of the potentiometer to the Serial Monitor. 
  delay(100);                                 // delay for 25ms in between helps with stability 
 
}
