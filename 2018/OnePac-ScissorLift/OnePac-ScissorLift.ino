 
 /*
Scissorlift code for ONEPAC
-Steve Olson 02 Feb 2018

 Reads an analog input from potentiometer on pin A0, uses the potentiometer value to drive a PWM device from pin 9.  Meant to run a motor. 
  More info on motor(PWM)values at "sensorValue=sensorValue" line.
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.
  http://www.arduino.cc/en/Tutorial/AnalogReadSerial
*/
#include<Servo.h>
Servo myservo;
// Input Pins
int potPin= A0; // input pin of potentiometer; should be an anolog pin. If only using AnalogRead() i.e. not digitalRead(), can skip the 'A' in front of the pin number. 
int servoPin = 9; // outpint pin to servo motor; this should be a PWM pin. PWM is better described at https://www.arduino.cc/en/Tutorial/PWM.

// Initialize variables
double potValue = 0; // value of the potentiometer  value sent to serial monitor
int potOut = 0;//This variable reads the value of the potentiometer and will display it on the serial monitor

void setup() {
  //Open the Serial Monitor under the Tools bar once the program is running and you can see the values of the potentiometer at various point 
  Serial.begin(9600);  // initialize serial communication at 9600 bits per second
  
  myservo.attach(servoPin); //assigns the servo called myservo to servoPin;
  myservo.writeMicroseconds(1500);  //This sets servo to mid-point of map range. Described better in void loop.
 

}


void loop() {
  // read the potentiometer input on analog pin A0. This will be a value between 0-1023.
  potValue = analogRead(potPin); 
  
  //This converts the PWM outputs to microsecond values. 700 is fully counter-clockwise and 2200 is fully clockwise. (governed to 1200 and 1700 for better control at slow speeds for scissor lift)
  potOut = map(potValue, 0, 1023, 1300, 1600); 
  /*For more info on microseconds and the map function look here at https://www.arduino.cc/en/Reference/ServoWriteMicroseconds. 
  The map function is decribed further here at https://www.arduino.cc/reference/en/language/functions/math/map/.
  */

   myservo.writeMicroseconds(potOut); //If the switch state is low(actually high because of the inversion of INPUT_PULLUP), the servo will be set to the value of sensorOut(potentiometer)

  delay(25);// delay for 25 ms increases stability 
 
}
