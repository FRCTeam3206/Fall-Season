#include <Servo.h>

Servo leftFrontMotor;
Servo rightFrontMotor;
Servo leftRearMotor;
Servo rightRearMotor;

//Pin Definitions

 #define ch1      7  // RC controller 1, RC Controller RightX, channel (ch1) to Arduino input pin (7)
// #define ch2      2  // RightY isnt used 
#define ch3      3  // LeftY
#define ch4      4  // LeftX

#define LEFT_FRONT_MOTOR_PIN    9  // confirmed pin  9 is pwm output
#define RIGHT_FRONT_MOTOR_PIN  10  // confirmed pin 10 is pwm output
#define LEFT_REAR_MOTOR_PIN    11  // confirmed pin 11 is pwm output
#define RIGHT_REAR_MOTOR_PIN   12  // this pin is not PWM output; to do: confirm functionality 

// Constants
#define PULSE_WIDTH_DEADBAND    25    // Pulse width difference from 1500 us (microseconds) to ignore (to compensate for control centering offset)
const int MAX_SPEED = 500;            // This corresponds to a range of 1000 to 2000
const bool debugOn = false;           // The overhead required by serial and delays would be bad for RC control. Easy to disable.
const int NEUTRAL    = 1500;
void setup() {
  // put your setup code here, to run once:
 if (debugOn) Serial.begin(9600);    // initialize serial communication at 9600 bits per second
  leftFrontMotor.attach(LEFT_FRONT_MOTOR_PIN, 1000, 2000);  // 1000 = min value, 2000 = max value
  rightFrontMotor.attach(RIGHT_FRONT_MOTOR_PIN, 1000, 2000);               
  leftRearMotor.attach(LEFT_REAR_MOTOR_PIN, 1000, 2000); 
  rightRearMotor.attach(RIGHT_REAR_MOTOR_PIN, 1000, 2000);               

//  intakeMotor.attach(INTAKE_MOTOR_PIN, 1000, 2000);               

// Perform a quick motor check.  This setup is prone to wires falling out.  This will spin each
// gearbox briefly.
    leftFrontMotor.writeMicroseconds(1650);       
      delay(200);
    leftFrontMotor.writeMicroseconds(1500);       
      delay(500);
    rightFrontMotor.writeMicroseconds(1350);       
      delay(200);
    rightFrontMotor.writeMicroseconds(1500);       
      delay(500);
    leftRearMotor.writeMicroseconds(1650);       
      delay(200);
    leftRearMotor.writeMicroseconds(1500);       
      delay(500);
    rightRearMotor.writeMicroseconds(1350);       
      delay(200);
    rightRearMotor.writeMicroseconds(1500);
}

void loop() {
  // put your main code here, to run repeatedly:

  int RightX    = pulseIn(ch1, HIGH);       // Robot spin
//  int RightY    = pulseIn(ch2, HIGH); 
  int LeftY     = pulseIn(ch3, HIGH);       // Robot Y  
  int LeftX     = pulseIn(ch4, HIGH);       // Robot X

  LeftY = LeftY - NEUTRAL; // Normalizes to +/- 500
  LeftY = (-1) * LeftY; // Invert
  LeftY = LeftY + NEUTRAL;

/*  Important! The sw confirms communication to the controller before turning on any motors.
 *  If any input is bogus then stop motors. 
 *  This check isn't critical for "weapons" controller 2.
 *  
 */
int RightY = 1500;
int RightKnob = 1500;
int LeftKnob = 1500;

  if (( 900 < LeftX ) && 
      ( LeftX < 2100 ) && 
      ( 900 < LeftY ) && 
      ( LeftY < 2100 ) && 
      ( 900 < RightX ) && 
      ( RightX < 2100 ) // && 
       ){

//  Print RC pulse widths to Serial Monitor 
  if (debugOn) {
    Serial.print("Left Y = ");
    Serial.print(LeftY);
    Serial.print(", Left X = ");
    Serial.print(LeftX);
    Serial.print(", Right X = ");
    Serial.println(RightX);
//    Serial.print(", Right Y = ");
//    Serial.print(RightY);
    delay(2000);                        // delay between writes to serial monitor
  }

    float K_Drive_float = 1.0;
    float K_Strafe = 1.0;

    float drive   = K_Drive_float * (LeftY - NEUTRAL);  
    float strafe  = K_Strafe * (NEUTRAL - LeftX);

    float K_Rotate_float = 1.0;

    float rotate  = K_Rotate_float * (RightX - NEUTRAL);
    
    float front_left  = drive + strafe  + rotate;
    float front_right = drive - strafe  - rotate;
    float rear_left   = drive - strafe  + rotate;
    float rear_right  = drive + strafe  - rotate;

    // Cap speeds to max, +/- 500
     front_left  = min(max(front_left,  -MAX_SPEED), MAX_SPEED);
     front_right = min(max(front_right, -MAX_SPEED), MAX_SPEED);  
     rear_left   = min(max(rear_left,   -MAX_SPEED), MAX_SPEED); 
     rear_right  = min(max(rear_right,  -MAX_SPEED), MAX_SPEED); 

  if (debugOn) {
     Serial.print("Drive = ");
     Serial.print(drive);
     Serial.print(", Strafe = ");
     Serial.print(strafe);
     Serial.print(", Rotate = ");
     Serial.println(rotate);
     Serial.println("");

    Serial.print("front_left = ");
    Serial.print(front_left);
    Serial.print(", rear_left= ");
    Serial.print(rear_left);
    Serial.print(", front_right = ");
    Serial.print(front_right);
    Serial.print(", rear_right = ");
    Serial.println(rear_right);
    Serial.println("");

  }
     /*  Localize  to  motors
     *  It isn't entirely necessary to put bounds on the output because servo.attach has min, max arguments
     *  Something is operating very slowly in the loop.  Try updating just one of the outputs per cycle.
     */

        if (abs(front_left) < PULSE_WIDTH_DEADBAND) front_left = 0;
        leftFrontMotor.writeMicroseconds(front_left + NEUTRAL);  

        if (abs(front_right) < PULSE_WIDTH_DEADBAND) front_right = 0;
        rightFrontMotor.writeMicroseconds(NEUTRAL - front_right);

        if (abs(rear_left) < PULSE_WIDTH_DEADBAND) rear_left = 0;   
        leftRearMotor.writeMicroseconds(rear_left + NEUTRAL);

        if (abs(rear_right) < PULSE_WIDTH_DEADBAND) rear_right = 0;
        rightRearMotor.writeMicroseconds(NEUTRAL - rear_right);

  }
  else {
    leftFrontMotor.writeMicroseconds(NEUTRAL);
    rightFrontMotor.writeMicroseconds(NEUTRAL);
    leftRearMotor.writeMicroseconds(NEUTRAL);
    rightRearMotor.writeMicroseconds(NEUTRAL);
  }}
