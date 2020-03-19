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
 
#define PIN 7
 
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
 //byte PWM_PIN = 1; 
 //byte PWM_PIN2 = 2;
// byte PWM_PIN3 = 3; 
int clockwise = 1600;          // sets PWM microsecond value for clockwise motor rotation
int counterclockwise = 1400; // sets PWM microsecond value for counterclockwise motor rotation
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
  rightMotor.attach(5); 
  leftMotor.attach(6); //assigns the servo to pin 10 (PWM) 
  WinchMotor.attach(3);
  rightMotor.writeMicroseconds(1500);
  leftMotor.writeMicroseconds(1500); //This sets servo to mid-point of mapped range. Described better in void loop.
  WinchMotor.writeMicroseconds(1500);
  //pinMode(PWM_PIN, INPUT);
  //pinMode(PWM_PIN2, INPUT);
  //pinMode(PWM_PIN3, INPUT);
  
  
}
/*void loop() { pwm_value = pulseIn(PWM_PIN, HIGH);
pwm_value2 = pulseIn(PWM_PIN2, HIGH);
pwm_value3 = pulseIn(PWM_PIN3, HIGH);
Serial.println(pwm_value);
rightMotor.write(pwm_value);
Serial.println(pwm_value2);
leftMotor.write(pwm_value2);
Serial.println(pwm_value3);
WinchMotor.write(pwm_value3); 
  // Some example procedures showing how to display to the pixels:
  colorWipe(strip.Color(255, 0, 0), 50); // Red
  colorWipe(strip.Color(0, 255, 0), 50); // Green
  colorWipe(strip.Color(0, 0, 255), 50); // Blue
  rainbow(20);
  rainbowCycle(20);
}
 
// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}
 
void rainbow(uint8_t wait) {
  uint16_t i, j;
 
  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}
 
// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;
 
  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}
 
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}*/
 
 
 
 void foward() {
      rightMotor.writeMicroseconds(clockwise);      // 
       leftMotor.writeMicroseconds(counterclockwise);    // 
 }


void reverse () {
      rightMotor.writeMicroseconds(counterclockwise);      // 
       leftMotor.writeMicroseconds(clockwise);    // 
 }

 void pause () {
   rightMotor.writeMicroseconds(1500);
   leftMotor.writeMicroseconds(1500);
  delay(1000);
 }
 void turnLeft () {
  rightMotor.writeMicroseconds(clockwise);
  leftMotor.writeMicroseconds(clockwise);
  delay(1000); 
 }

void turnRight () {
  rightMotor.writeMicroseconds(counterclockwise);
  leftMotor.writeMicroseconds(counterclockwise);
  delay(1000);
}

void loop() {
  delay(100);
if( timer < 1 ){
foward();
delay(2000);
pause();

/*turnRight();
delay(2000);
pause();

foward();
delay(2000);
pause();

turnRight();
delay(2000);
//pause();

foward();
delay(2000);
pause();

turnRight();
delay(2000);
pause();

foward();
delay(2000);
pause();

turnRight();
delay(2000);
pause();
*/


timer ++;
delay(1000);
 }
 else{
  int throttle = pulseIn(LeftControl, HIGH);
  int steering = pulseIn(RightControl, HIGH);
  int climb = pulseIn(ClimbControl, HIGH);
  rightMotor.write(steering);
  leftMotor.write(throttle); //This sets servo to mid-point of mapped range. Described better in void loop.
  WinchMotor.write(climb);
 }
 
}

  //Serial.println(SwitchState);// remove the two forward slashes in the front if you would like to see the state of ther switch, but comment out the other Serial.println then.
 // Serial.println(sensorOut); //Prints out the final value of the potentiometer to the Serial Monitor. 
 // delay(25);// delay for 25ms in between helps with stability 
// }*/
