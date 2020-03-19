/*
  Reads an analog input on pin 9, prints the result to the Serial Monitor. Meant to run a motor. 
  More info on motor(PWM)values at "sensorValue=sensorValue" line.
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.
  http://www.arduino.cc/en/Tutorial/AnalogReadSerial

  Definition:
   - myservo --> servo motor class (servo is a type of motor)
   - Microsecond values - 700 is fully counter-clockwise and 2200 is fully clockwise

  Notes:
   - Open the Serial Monitor under the Tools bar once the program is running and you can see the values of the potentiometer at various point 
   - Pulse Width Modulation (PWM) is better described at https://www.arduino.cc/en/Tutorial/PWM.
   - For more info on microseconds and the map function look here at https://www.arduino.cc/en/Reference/ServoWriteMicroseconds. 
   - The map function is decribed further here at https://www.arduino.cc/reference/en/language/functions/math/map/.

   
*/

#include<Servo.h>       // include 

Servo myservoStarboard;          // initializes object "myservoStarboard" as a Servo Motor object on the right side of the car facing forward
Servo myservoPort;              //  initliazes object "myservoPort" as a Servo Motor object on the left side of the car facing forward

int clockwise = 2200;          // sets PWM microsecond value for clockwise motor rotation
int counterclockwise = 700; // sets PWM microsecond value for counterclockwise motor rotation

void setup() {
  Serial.begin(9600);                  // initialize serial communication at 9600 bits per second - don't change this
  myservo.attach(10);                  //assigns the servo to pin 10 (PWM) 
  myservo.writeMicroseconds(1500);    //This sets servo to mid-point of mapped range. Described better in void loop.
  
}

void forward () {
      myservoStarboard.writeMicroseconds(clockwise);      // 
      myservoPort.writeMicroseconds(counterclockwise);    // 
}

void reverse () {
      myservoStarboard.writeMicroseconds(counterclockwise);      // 
      myservoPort.writeMicroseconds(clockwise);    // 
}

void pause (){
  myservoStarboard.writeMicroseconds(1500);
  myservoPort.writeMicroseconds(1500);
  delay(1000);
}

void loop() {

reverse();

delay(2000);

pause();

forward();

delay(2000);

  //Serial.println(SwitchState);// remove the two forward slashes in the front if you would like to see the state of ther switch, but comment out the other Serial.println then.
  Serial.println(sensorOut); //Prints out the final value of the potentiometer to the Serial Monitor. 
  delay(25);// delay for 25ms in between helps with stability 
}


