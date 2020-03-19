#include <Servo.h>


// Servo Definitions

Servo shoulderMotor;  // Bag motor
Servo wristMotor;     // Bag motor
Servo gripperServo;   // Real servo


//Pin Definitions
// Wire RC 2 to Arduino pin 2, RC 3 to Arduino pin 3, RC 4 to Arduino 4.

// #define ch1      2  // RC controller 1, RC Controller RightX, channel (ch1) to Arduino input pin (7)
#define ch2         2  // RightY -- wrist motor
#define ch3         3  // LeftY  -- shoulder motor
#define ch4         4  // LeftX  -- gripper servo
// #define ch5      5  // RightKnob
// #define ch6      6  // LeftKnob


#define SHOULDER_MOTOR_PIN    9  
#define WRIST_MOTOR_PIN      10  
#define GRIPPER_SERVO_PIN    11  


// Constants

#define PULSE_WIDTH_DEADBAND    25    // Pulse width difference from 1500 us (microseconds) to ignore (to compensate for control centering offset)
const int MAX_SPEED = 500;            // This corresponds to a range of 1000 to 2000
const bool debugOn = false;           // The overhead required by serial and delays would be bad for RC control. Easy to disable.
const int NEUTRAL    = 1500;

#define K_SHOULDER  .50  
#define K_WRIST     1.0

void setup()
{
  // put your setup code here, to run once:
 if (debugOn) Serial.begin(9600);    // initialize serial communication at 9600 bits per second
 // leftFrontMotor.attach(LEFT_FRONT_MOTOR_PIN, 1000, 2000);  // 1000 = min value, 2000 = max value
  shoulderMotor.attach(SHOULDER_MOTOR_PIN, 1000, 2000);
  wristMotor.attach(WRIST_MOTOR_PIN, 1000, 2000);               
 // leftRearMotor.attach(LEFT_REAR_MOTOR_PIN, 1000, 2000); 
 // rightRearMotor.attach(RIGHT_REAR_MOTOR_PIN, 1000, 2000);               

}


void loop()
{
  // put your main code here, to run repeatedly:

  //int RightX    = pulseIn(2, HIGH);       // Robot spin
  int RightY    = pulseIn(ch2, HIGH);       // RC Right Y, wrist
  int LeftY     = pulseIn(ch3, HIGH);       // Robot Y    shoulder
  int LeftX     = pulseIn(ch4, HIGH);       // Robot X    gripper
  /*  int RightKnob = pulseIn(5, HIGH);       // K_Rotate
  int LeftKnob  = pulseIn(6, HIGH);       // K_Strafe */

/*  Important! The sw confirms communication to the controller before turning on any motors.
 *  If any input is bogus then stop motors. 
 *  This check isn't critical for "weapons" controller 2.
 *  
 */
 // int LeftX = 1500;   // These are dummys set to static values so the code compiles and works while building.
//  int LeftY = 1500;   // These are dummys set to static values so the code compiles and works while building.
//  int RightY = 1500;
  int RightX = 1500;
  int RightKnob = 1500;
  int LeftKnob = 1500;

  if (
      ( 900 < LeftX ) && 
      ( LeftX < 2100 ) && 
      ( 900 < LeftY ) && 
      ( LeftY < 2100 ) && 
      ( 900 < RightY ) && 
      ( RightY < 2100 ) // && 
      //    ( 900 < intakeRaw ) && 
      //    ( intakeRaw < 2100 )
      )
    {

      //  Print RC pulse widths to Serial Monitor 
      if (debugOn)
      {
        Serial.print("Left Y = ");
        Serial.print(LeftY);
        Serial.print(", Left X = ");
        Serial.print(LeftX);
        //Serial.print(", Right X = ");
        //Serial.println(RightX);
        Serial.print(", Right Y = ");
        Serial.println(RightY);
        //Serial.print(", Aux Knob Right = ");
        //Serial.print(RightKnob);
        //Serial.print(", Aux Knob Left = ");
        //Serial.print(LeftKnob);
        //    Serial.print(", IntakeRaw = ");
        //    Serial.println(intakeRaw);
        delay(1000);                        // delay between writes to serial monitor
      }

       int shoulder_motor_intermediate  = (RightY - NEUTRAL) * K_SHOULDER;
       int wrist_motor = (RightY - NEUTRAL) * -1 * K_WRIST;
       int gripper_servo = LeftX - NEUTRAL;
    
       
    if (debugOn) 
      {
        Serial.print("Shoulder Motor = ");
        Serial.print(shoulder_motor_intermediate);
        Serial.print(" Wrist Motor = ");
        Serial.print(wrist_motor);
        Serial.print(  "Gripper Servo = ");
        Serial.print(gripper_servo);
      }

    // Cap speeds to max, +/- 500
//     front_left  = min(max(front_left,  -MAX_SPEED), MAX_SPEED);
       wrist_motor = min(max(wrist_motor, -MAX_SPEED), MAX_SPEED);  
       shoulder_motor_intermediate = min(max(shoulder_motor_intermediate, -MAX_SPEED), MAX_SPEED);
       gripper_servo = min(max(gripper_servo, -MAX_SPEED), MAX_SPEED); 
//     rear_right  = min(max(rear_right,  -MAX_SPEED), MAX_SPEED); 
      //     intake      = min(max(intake,      -MAX_SPEED), MAX_SPEED); 


    if (debugOn) 
      {
        Serial.print("  Shoulder Motor = ");
        Serial.print(shoulder_motor_intermediate);
        Serial.print(" Wrist Motor = ");
        Serial.print(wrist_motor);
        Serial.print(" Gripper Servo = ");
        Serial.print(gripper_servo);
        // Serial.print(", Strafe = ");
        // Serial.print(strafe);
        // Serial.print(", K_Drive = ");
        // Serial.print(K_Drive_float);
        //    Serial.print(", Intake = ");
        //    Serial.println(intake);

        /*    Serial.print("front_left = ");
        Serial.print(front_left);
        Serial.print(", rear_left= ");
        Serial.print(rear_left);
        Serial.print(", front_right = ");
        Serial.print(front_right);
        Serial.print(", rear_right = ");
        Serial.println(rear_right);
        */ 
        // delay(500); 
      }
    /*  Localize  to  motors
    *  It isn't entirely necessary to put bounds on the output because servo.attach has min, max arguments
    *  Something is operating very slowly in the loop.  Try updating just one of the outputs per cycle.
    */

    /*       if (abs(front_left) < PULSE_WIDTH_DEADBAND) front_left = 0;
    leftFrontMotor.writeMicroseconds(front_left + NEUTRAL);  */

//    if (abs(front_right) < PULSE_WIDTH_DEADBAND) front_right = 0;
//    rightFrontMotor.writeMicroseconds(NEUTRAL - front_right);

    if (abs(shoulder_motor_intermediate) < PULSE_WIDTH_DEADBAND) shoulder_motor_intermediate = 0;   
    shoulderMotor.writeMicroseconds(shoulder_motor_intermediate + NEUTRAL);

    if (abs(wrist_motor) < PULSE_WIDTH_DEADBAND) wrist_motor = 0;
    wristMotor.writeMicroseconds(wrist_motor + NEUTRAL);

    if (abs(gripper_servo) < PULSE_WIDTH_DEADBAND) gripper_servo = 0;
    gripperServo.writeMicroseconds(gripper_servo + NEUTRAL);

    /*       if (abs(rear_right) < PULSE_WIDTH_DEADBAND) rear_right = 0;
    rightRearMotor.writeMicroseconds(NEUTRAL - rear_right);*/

    //        intake = NEUTRAL + intake;
        
            if (debugOn) {
              Serial.print(",   ShoulderFinal = ");
              Serial.println(shoulder_motor_intermediate);
              Serial.print("  Wrist Final = ");
              Serial.println(wrist_motor);
              Serial.print("  Gripper Final = ");
              Serial.println(gripper_servo);
            }

    //        if (abs(intake) < PULSE_WIDTH_DEADBAND) intake = 0;
    //        intakeMotor.writeMicroseconds(intake);
  }
  else
    {
//      leftFrontMotor.writeMicroseconds(NEUTRAL);
//      rightFrontMotor.writeMicroseconds(NEUTRAL);
//      leftRearMotor.writeMicroseconds(NEUTRAL);
//      rightRearMotor.writeMicroseconds(NEUTRAL);
        shoulderMotor.writeMicroseconds(NEUTRAL);
        wristMotor.writeMicroseconds(NEUTRAL);
        gripperServo.writeMicroseconds(NEUTRAL);
    }
  }
