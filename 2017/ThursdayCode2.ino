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
/*
button wires
white (blue) = signal
black (green) = power
red (yellow) = ground
*/
#include<Servo.h>       // include 

Servo myservoStarboard;          // initializes object "myservoStarboard" as a Servo Motor object on the right side of the car facing forward
Servo myservoPort;              //  initliazes object "myservoPort" as a Servo Motor object on the left side of the car facing forward

int clockwise = 2000;          // sets PWM microsecond value for clockwise motor rotation
int counterclockwise = 1000; // sets PWM microsecond value for counterclockwise motor rotation
int passNum=0;
int analogPin=1;
int val=0;
int increment=0;
int LeftControl = 11;
int RightControl = 10;
int ClimbControl = 9;

void setup() {
  Serial.begin(9600);                  // initialize serial communication at 9600 bits per second - don't change this
  myservoStarboard.attach(6);                //assigns the servo to pin 10 (PWM) 
  myservoStarboard.writeMicroseconds(1500);    //This sets servo to mid-point of mapped range. Described better in void loop.
  myservoPort.attach(5);                  //assigns the servo to pin 9 (PWM) 
  myservoPort.writeMicroseconds(1500);
  
  
   // aux channel from RC receiver//This sets servo to mid-point of mapped range. Described better in void loop.
}

void forward () {
      myservoStarboard.writeMicroseconds(clockwise);      // 
      myservoPort.writeMicroseconds(counterclockwise);    // 
}
void turnLeft () {
      myservoStarboard.writeMicroseconds(clockwise);      // 
      myservoPort.writeMicroseconds(clockwise);    // 
}
void turnRight () {
      myservoStarboard.writeMicroseconds(counterclockwise);      // 
      myservoPort.writeMicroseconds(counterclockwise);    // 
}

void reverse () {
      myservoStarboard.writeMicroseconds(counterclockwise);      // 
      myservoPort.writeMicroseconds(clockwise);    // 
}

void pause (){
  myservoStarboard.writeMicroseconds(1500);
  myservoPort.writeMicroseconds(1500);
  delay(3000);
}

void Starboard (){
  myservoStarboard.writeMicroseconds(counterclockwise);
  myservoPort.writeMicroseconds(counterclockwise);
}

void Port (){
  myservoStarboard.writeMicroseconds(clockwise);
  myservoPort.writeMicroseconds(clockwise);
}
void loop() {
if(increment < 1){
  
  forward();
  delay(10000);
  pause();
  increment++;
  
}
else
{
  int throttle = pulseIn(LeftControl, HIGH);  // Read throttle input.  Normally 1000 to 2000
  int steering = pulseIn(RightControl, HIGH);  // Read steering input.  Normally 1000 to 2000
  int climb = pulseIn(ClimbControl, HIGH);            // Read aux input.  Either ~1000 or ~2000 (basically binary)

  }
  

  
  

 
}
  



