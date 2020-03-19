/*
  Reads an analog input on pin 9, prints the result to the Serial Monitor. Meant to run a motor. 
  More info on motor(PWM)values at "sensorValue=sensorValue" line.
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  http://www.arduino.cc/en/Tutorial/AnalogReadSerial
*/
#include<Servo.h>
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;

double sensorValue = 0; //Doubled the sensor value so that you could get a reading on the Serial Monitor
int sensorOut = 0;//This variable reads the value of the potentiometer and will display it on the serial monitor
const int SwitchOnOff = 4;// This variable tells the switch what to do.
int SwitchState = 0;// This variable reads the state of the switch, whether it's high or low.

void setup() {
  Serial.begin(9600);  // initialize serial communication at 9600 bits per second
  //Open the Serial Monitor under the Tools bar once the program is running and you can see the values of the potentiometer at various point 
  servo1.attach(11); //assigns the servo called servo1 to pin 10, which is also a PWM pin. PWM is better described at https://www.arduino.cc/en/Tutorial/PWM.
  servo2.attach(10);
  servo3.attach(9);
  servo4.attach(6);
  servo5.attach(5);
  servo6.attach(3);
  
  servo1.writeMicroseconds(1500);  //This sets servo to mid-point of map range. Described better in void loop.
  servo2.writeMicroseconds(1500);
  servo3.writeMicroseconds(1500);
  servo4.writeMicroseconds(1500);
  servo5.writeMicroseconds(1500);
  servo6.writeMicroseconds(1500);
  
  pinMode(SwitchOnOff, INPUT_PULLUP); //This declares that the variable SwitchOnOff is an input_pullup. 
  //INPUT_PULLUP just inverts the high and low commands, meaning that high = off and low = on, not the other way around.
}


void loop() {
  sensorValue = analogRead(A0); // read the input on analog pin 0. This is your value from 0-1023.
  sensorOut = map(sensorValue, 0, 1023, 700, 2200); //This changes the PWM values from 0-1023 to microsecond values. 700 is fully counter-clockwise and 2200 is fully clockwise.
  /*For more info on microseconds and the map function look here at https://www.arduino.cc/en/Reference/ServoWriteMicroseconds. 
  The map function is decribed further here at https://www.arduino.cc/reference/en/language/functions/math/map/.
  */
  SwitchState = digitalRead(SwitchOnOff); //This line reads the state of the switch, whether it's high or low.
  
  if(SwitchState == LOW) {
    servo1.writeMicroseconds(sensorOut); //If the switch state is low(actually high because of the inversion of INPUT_PULLUP), the servo will be set to the value of sensorOut(potentiometer)
    servo2.writeMicroseconds(sensorOut);
    servo3.writeMicroseconds(sensorOut);
    servo4.writeMicroseconds(sensorOut);
    servo5.writeMicroseconds(sensorOut);
    servo6.writeMicroseconds(sensorOut);
    
  } else {
    servo1.writeMicroseconds(1500);// If the switch state is high(actually low because of the inversion of INPUT_PULLUP), the servo will be set to 1500, because 1500 is the neutral value.
    servo2.writeMicroseconds(1500);
    servo3.writeMicroseconds(1500);
    servo4.writeMicroseconds(1500);
    servo5.writeMicroseconds(1500);
    servo6.writeMicroseconds(1500);
  }

  //Serial.println(SwitchState);// remove the two forward slashes in the front if you would like to see the state of ther switch, but comment out the other Serial.println then.
  Serial.println(sensorOut); //Prints out the final value of the potentiometer to the Serial Monitor. 
  delay(25);// delay for 25ms in between helps with stability 
 
}
