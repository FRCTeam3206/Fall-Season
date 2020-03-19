#include <Servo.h>

Servo leftMotor;
Servo rightMotor;

//Pin Definitions
#define STEERING_PIN      2  // steering channel from RC ch 1 receiver  Knob
#define THROTTLE_PIN      3  // throttle channel from RC ch 2 receiver  Trigger
#define AUX_PIN           4  // aux channel from RC ch 3  
#define RIGHT_PWM_0_PIN   10  // confirmed pin  9 is pwm output
#define RIGHT_MOTOR_PIN   9  // confirmed pin 10 is pwm output  
// #define AUX_MOTOR_PIN    11  // confirmed pin 11 is pwm output

// Constants
#define PULSE_WIDTH_DEADBAND  40      // pulse width difference from 1500 us (microseconds) to ignore (to compensate for control centering offset)
#define K_THROTTLE            1    // speed multiplier to decrease steering sensitivity.  0.65 gives about a 4" turn radius at max throttle
#define K_STEERING            1    // speed multiplier to decrease steering sensitivity.  0.65 gives about a 4" turn radius at max throttle


int MAX_SPEED = 2000;        // This corresponds to a range of 1000 to 2000
const bool debugOn = false;       // The overhead required by serial and delays would be bad for RC control. 
                                  // Make it easy to disable.

const bool RightReverse = true;  // Flips motor cw .to ccw.
const bool LeftReverse = false;  // Flips motor cw to ccw.

// Variables
int left_speed;
int right_speed;
int l_speed; 
int r_speed;

void setup()                        
{
  if (debugOn) Serial.begin(9600);    // initialize serial communication at 9600 bits per second

  leftMotor.attach(RIGHT_PWM_0_PIN); 
  rightMotor.attach(RIGHT_MOTOR_PIN);               
//  auxMotor.attach(AUX_MOTOR_PIN);
//  pinMode(LED_BUILTIN, OUTPUT);  // pin 13 on the arduino    
}

void loop()
{   
/*  
 *   RC input
 */
  int throttle = pulseIn(THROTTLE_PIN, HIGH);  // Read throttle input.  Normally 1000 to 2000
  int steering = pulseIn(STEERING_PIN, HIGH);  // Read steering input.  Normally 1000 to 2000
//  int aux = pulseIn(AUX_PIN, HIGH);            // Read aux input.  Either ~1000 or ~2000 (basically binary)

  

/*  
 *   Print RC pulse widths to Serial Monitor
 */
  if (debugOn) {
    Serial.println("******");
    Serial.print("Throttle = ");
    Serial.print(throttle);
    Serial.print(", Steering = ");
    Serial.println(steering);
//    Serial.print(", Aux = ");
//    Serial.println(aux);
    delay(1000);        // delay between reads for stability; only necessary with serial
  }

/*
 * Important! The sw confirms communication to the controller before turning on any motors.
 */
 
  if ((900 < throttle)&& (throttle < 2100) && (900 < steering) && (steering < 2100)){
     if (debugOn) Serial.println("Yay!");

    
     // Normalize throttle and steering to the range of -500 to +500.
     long throttleNorm = throttle - 1500;
     long steeringNorm = steering - 1500; // Note steering magnitude is pretty small; consider multiplying by more than 1.x

    if (debugOn) Serial.println(throttleNorm);    
    if (debugOn) Serial.println(steeringNorm);    
 

     left_speed =  throttleNorm;
     right_speed =  steeringNorm;

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
       if (LeftReverse) {
         left_speed = -left_speed; 
       }
       l_speed = map(left_speed, -500, 500, 1000, 2000); 
    }
    else{
       l_speed = 1500; // This should be neutral, no speed.  If it is in the deadband then call it neutral.
    }

    if (abs(right_speed) > PULSE_WIDTH_DEADBAND){
       if (RightReverse) {
         right_speed = right_speed; 
       }
         r_speed = map(right_speed, -500, 500, 1000, 2000); 
    }
    else{
       r_speed = 1500; // This should be neutral, no speed
    }
//    if(
    if (debugOn) {
      Serial.print("left_speed = ");
      Serial.print(l_speed);
      Serial.print(", right_speed = ");
      Serial.println(r_speed);     
    }

    leftMotor.writeMicroseconds(l_speed);       
    rightMotor.writeMicroseconds(r_speed);       
}

