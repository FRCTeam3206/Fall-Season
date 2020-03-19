/*
  Reads an analog input on pin 9, prints the result to the Serial Monitor. Meant to run a motor. 
  More info on motor(PWM)values at "sensorValue=sensorValue" line.
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.
  http://www.arduino.cc/en/Tutorial/AnalogReadSerial
  Definition:
   - rightMotor --> servo motor class (servo is a type of motor)
   - Microsecond values - 700 is fully counter-clockwise and 2200 is fully clockwise
  Notes:
   - Open the Serial Monitor under the Tools bar once the program is running and you can see the values of the potentiometer at various points 
   - Pulse Width Modulation (PWM) is better described at https://www.arduino.cc/en/Tutorial/PWM.
   - For more info on microseconds and the map function look here at https://www.arduino.cc/en/Reference/ServoWriteMicroseconds. 
   - The map function is decribed further here at https://www.arduino.cc/reference/en/language/functions/math/map/.
   
*/

#include <Adafruit_NeoPixel.h>
 
#define PIN 12
 
// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(8, PIN, NEO_GRB + NEO_KHZ800);
 



#include<Servo.h>       // include 

Servo rightMotor;          // initializes object "rightMotorStarboard" as a Servo Motor object on the right side of the car facing forward
Servo leftMotor;//  initliazes object "rightMotorPort" as a Servo Motor object on the left side of the car facing forward
Servo WinchMotor; // channel 3
//int PWM_PIN = 12; 
 //byte PWM_PIN2 = 2;
// byte PWM_PIN3 = 3; 
int clockwise = 1700;          // sets PWM microsecond value for clockwise motor rotation
int counterclockwise = 1300; // sets PWM microsecond value for counterclockwise motor rotation
int pwm_value;
int pwm_value2;
int pwm_value3;
int LeftControl = 11;
int RightControl = 10;
int ClimbControl = 9;
int timer = 0;
int one = 1;

void setup() {
  strip.begin();
  strip.setBrightness(30); //adjust brightness here
  strip.show(); // Initialize all pixels to 'off
  Serial.begin(9600);                  // initialize serial communication at 9600 bits per second - don't change this
  rightMotor.attach(6); 
  leftMotor.attach(5); //assigns the servo to pin 10 (PWM) 
  WinchMotor.attach(3);
  rightMotor.writeMicroseconds(1500);
  leftMotor.writeMicroseconds(1500); //This sets servo to mid-point of mapped range. Described better in void loop.
  WinchMotor.writeMicroseconds(1500);
  //pinMode(PWM_PIN, INPUT);
  //pinMode(PWM_PIN2, INPUT);
  //pinMode(PWM_PIN3, INPUT);
  
  
}
 /*\
{ pwm_value = pulseIn(PWM_PIN, HIGH);
pwm_value2 = pulseIn(PWM_PIN2, HIGH);
pwm_value3 = pulseIn(PWM_PIN3, HIGH);
Serial.println(pwm_value);
rightMotor.write(pwm_value);
Serial.println(pwm_value2);
leftMotor.write(pwm_value2);
Serial.println(pwm_value3);
WinchMotor.write(pwm_value3); */

  // Some example procedures showing how to display to the pixels:


 
 
 
 void foward() {
      rightMotor.writeMicroseconds(clockwise);      // 
      leftMotor.writeMicroseconds(clockwise);    // 
 }


void reverse () {
      rightMotor.writeMicroseconds(counterclockwise);      // 
       leftMotor.writeMicroseconds(counterclockwise);    // 
 }

 void pause (double seconds) {
   rightMotor.writeMicroseconds(1500);
   leftMotor.writeMicroseconds(1500);
  delay(seconds);
 }
 void turnRight () {
    leftMotor.writeMicroseconds(1592);
  rightMotor.writeMicroseconds(1408);
  delay(3); 
 }

void turnLeft () {
  leftMotor.writeMicroseconds(1570);
  rightMotor.writeMicroseconds(1430);
  delay(2);
}

void loop() {

if( timer < 1 ){
  
pause(5000);

WinchMotor.writeMicroseconds(1000); // detremine which way to spin to down climb
delay(1000);


foward();
delay(2000); // find actual values for delays and how long this all takes to figure out how much we should do before swicthing to atuomatic/the else loop
pause(100);
turnLeft();
foward();
delay(1000);
//turnRight();
//foward();
//delay(300);


timer++;
 }
 else{
  int throttle = pulseIn(LeftControl, HIGH);
  int steering = pulseIn(RightControl, HIGH);
  int climb = pulseIn(ClimbControl, HIGH);
  rightMotor.write(throttle);
  leftMotor.write(steering); //This sets servo to mid-point of mapped range. Described better in void loop.
  WinchMotor.write(climb);
 
 }



}



  //Serial.println(SwitchState);// remove the two forward slashes in the front if you would like to see the state of ther switch, but comment out the other Serial.println then.
 // Serial.println(sensorOut); //Prints out the final value of the potentiometer to the Serial Monitor. 
 // delay(25);// delay for 25ms in between helps with stability 
// }*/

