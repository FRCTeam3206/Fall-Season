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

motor 4 wiring
green = top left ground
blue = PWM port 3

motor 3 wiring
green = right ground
blue = PWM port 6

downclimb wiring
B4 = CH1
*/
#include<Servo.h>       // include 

Servo myservoStarboard;          // initializes object "myservoStarboard" as a Servo Motor object on the right side of the car facing forward
Servo myservoPort;              //  initliazes object "myservoPort" as a Servo Motor object on the left side of the car facing forward
Servo myservoClimb;

int clockwise = 1575;          // sets PWM microsecond value for clockwise motor rotation
int counterclockwise = 1425; // sets PWM microsecond value for counterclockwise motor rotation
int passNum=0;
int analogPin=1;
int val=0;
long ch1;
long ch2;
long ch3;
double autostarttime;

double timeperinch = 54.11;//time in milliseconds
double timeperfoot = 649.33;//time in milliseconds
#define RIGHT_PIN      3  // right channel from RC receiver
#define LEFT_PIN      2 // left channel from RC receiver
#define CLIMB_PIN           4  // climb channel from RC receiver
#define LEFT_MOTOR_PIN    9  // confirmed pin  9 is pwm output
#define RIGHT_MOTOR_PIN  10  // confirmed pin 10 is pwm output
#define CLIMB_MOTOR_PIN    11  // confirmed pin 11 is pwm output
#define PULSE_WIDTH_DEADBAND  40      // pulse width difference from 1500 us (microseconds) to ignore (to compensate for control centering offset)
#define K_right            0.50    // speed multiplier to decrease right sensitivity.  0.65 gives about a 4" turn radius at max left
#define K_SPEED               8.0    // Useful range 2 < 32.  16 is sluggish.  no tipping with 8.0  const accel multiplier to decrease max accel in a different way. 

const int MAX_SPEED = 500;        // This corresponds to a range of 1000 to 2000
const bool debugOn = false;       // The overhead required by serial and delays would be bad for RC control. 
                                  // Make it easy to disable.
long accelLimitedleft;        // Range will be +/- 500.  No real value to give it an initial value?

int left_speed;
int right_speed;
int l_speed; 
int r_speed;

void setup() {
  Serial.begin(9600);                  // initialize serial communication at 9600 bits per second - don't change this
  myservoStarboard.attach(10);                  //assigns the servo to pin 6 (PWM) 
  myservoStarboard.writeMicroseconds(1500);    //This sets servo to mid-point of mapped range. Described better in void loop.
  myservoPort.attach(9);                  //assigns the servo to pin 3 (PWM) 
  myservoPort.writeMicroseconds(1500);   //This sets servo to mid-point of mapped range. Described better in void loop.
  myservoClimb.attach(11);
  myservoClimb.writeMicroseconds(1500);
  /* pinMode(3, INPUT);                    // Sets the pins for the inputs for the RC controller
  pinMode(5, INPUT);
  pinMode(6, INPUT); */
}

void forward () {
      myservoStarboard.writeMicroseconds(counterclockwise);      // 
      myservoPort.writeMicroseconds(counterclockwise);
      //myservoStarboard.writeMicroseconds(counterclockwise);      // 
      //myservoPort.writeMicroseconds(clockwise); // 
}

void reverse () {
      myservoStarboard.writeMicroseconds(counterclockwise);      // 
      myservoPort.writeMicroseconds(clockwise);
      /*myservoStarboard.writeMicroseconds(clockwise);      // 
      myservoPort.writeMicroseconds(counterclockwise);*/// 
}

void pause (){
  myservoStarboard.writeMicroseconds(1500);
  myservoPort.writeMicroseconds(1500);
  delay(3000);
}

void timedelay(double distance) {
  //delay(distance * timeperinch);
  delay(distance * timeperfoot);

}

void Starboard (){
  myservoStarboard.writeMicroseconds(clockwise);
  myservoPort.writeMicroseconds(clockwise);
  /*myservoStarboard.writeMicroseconds(counterclockwise);
  myservoPort.writeMicroseconds(counterclockwise);*/
}

void Port (){
  myservoStarboard.writeMicroseconds(clockwise);//range of 700-1499
  myservoPort.writeMicroseconds(counterclockwise);//range of 1501-2200
  /*myservoStarboard.writeMicroseconds(clockwise);
  myservoPort.writeMicroseconds(clockwise);*/
}

void Climb (double direction){
  myservoClimb.writeMicroseconds(direction);
  /*myservoStarboard.writeMicroseconds(counterclockwise);
  myservoPort.writeMicroseconds(counterclockwise);*/
}

void pauseClimb (){
  myservoClimb.writeMicroseconds(1500);
  delay(1000);
}

void autonomous() {
  unsigned long startedAt = millis();
  while(millis() - startedAt < 10000){
    
  Climb(1100);
  timedelay(4); 
  pauseClimb();
  
  forward();
  timedelay(1);

  Climb(1750);
  timedelay(4);
  pauseClimb();
  
  //pause();

  forward();
  timedelay(18);

  pause();
  }
  }
  void rcControl() {
//-----------------------------------------------Below this line is all the RC controlling code for the robot-------------------------------------------------------------------------
  while(val > 400){ //this loop will wait until the button has been pressed and then will exit

  int leftMotor = pulseIn(A3, HIGH);  // Read left input.  Normally 1000 to 2000
  int rightMotor = pulseIn(A4, HIGH);  // Read right input.  Normally 1000 to 2000
  int climbMotor = pulseIn(A2, HIGH);            // Read climb input.  Either ~1000 or ~2000 (basically binary)

  //ch1 = pulseIn(2, HIGH);
  //ch2 = pulseIn(3, HIGH);
  //ch3 = pulseIn(A4, HIGH, 25000);
  //Serial.print("Channel 1: " + ch1);
  //Serial.print("Channel 2: " + ch2);
  //Serial.print("Channel 3: " + climbMotor);
  //delay(10); 
//Serial.println("made it");
  myservoPort.write(leftMotor);       
  myservoStarboard.write(rightMotor);
  myservoClimb.writeMicroseconds(climbMotor);
 /* if ((900 < left)&& (left < 2100) && (900 < right) && (right < 2100)){
     Serial.println("Yay!");

    
     // Normalize left and right to the range of -500 to +500.
     long leftNorm = left - 1500;
     long rightNorm = right - 1500;
    if (debugOn) Serial.println(rightNorm);    

   
     rightNorm = rightNorm * K_right;                                 // Apply simple scaling to keep right reasonable
     accelLimitedleft = (accelLimitedleft/K_SPEED*(K_SPEED-1.0)) + leftNorm/K_SPEED;   
    
    if (debugOn) Serial.println(K_SPEED);    
    if (debugOn) Serial.println(rightNorm);    
    if (debugOn) Serial.println(K_right);    
 

     // Mix left and right inputs to obtain left & right motor speeds
     left_speed = accelLimitedleft - rightNorm;
     right_speed = accelLimitedleft + rightNorm;

     // Cap speeds to max
     left_speed = min(max(left_speed, -MAX_SPEED), MAX_SPEED);  // max is 500
     right_speed = min(max(right_speed, -MAX_SPEED), MAX_SPEED); // max is 500

     // All good.
     // Values are now +/- 500 and need to be mapped to "servo" style outputs for motor controller
  }
  else     // At least one RC signal is not good
   {
    if (debugOn) Serial.println("Sad face");    
    left_speed = 0;
    right_speed = 0;
   }

    if (abs(left_speed) > PULSE_WIDTH_DEADBAND){
       l_speed = map(left_speed, -500, 500, 1000, 2000); 
    }
    else{
       l_speed = 1500; // This should be neutral, no speed.  If it is in the deadband then call it neutral.
    }

    if (abs(right_speed) > PULSE_WIDTH_DEADBAND){
       r_speed = map(right_speed, -500, 500, 1000, 2000); 
    }
    else{
       r_speed = 1500; // This should be neutral, no speed
    }

    if (debugOn) {
      Serial.print("left_speed = ");
      Serial.print(l_speed);
      Serial.print(", right_speed = ");
      Serial.println(r_speed);     
    }

    myservoPort.writeMicroseconds(l_speed);       
    myservoStarboard.writeMicroseconds(r_speed);
   */   
  
   }
  }
 /* void print() {
val=analogRead(analogPin); 
  Serial.print(val);
  delay(25);
}
*/
void loop() {
/*
while(1==1) {
  print();
  
}
*/

while(val < 400){ //this loop will wait until the button has been pressed and then will begin the next autonomous sequence
  //Serial.print("waiting to start...");
  val=analogRead(analogPin);
  Serial.print(val);
  delay(25);
} 
//--------------------------------------------------------this is the start of autonomous------------------------------------------------------------------------------------
autonomous();
rcControl();
}
