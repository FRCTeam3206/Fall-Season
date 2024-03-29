#include <Servo.h>

Servo leftMotor;  //wheel intake
Servo rightMotor;  //window motor
Servo servoMotor;    //servo hook

//Pin Definitions
#define STEERING_PIN      2  // steering channel from RC receiver  Knob
#define THROTTLE_PIN      3  // throttle channel from RC receiver  Trigger
#define AUX_PIN           4   //aux channel
#define RIGHT_PWM_0_PIN   9  // confirmed pin  9 is pwm output    wheel intake
#define RIGHT_MOTOR_PIN   10  // confirmed pin 10 is pwm output   window motor
#define AUX_MOTOR_PIN    7  // confirmed pin 11 is pwm output    servo

// Constants
#define PULSE_WIDTH_DEADBAND  40      // pulse width difference from 1500 us (microseconds) to ignore (to compensate for control centering offset)
#define K_THROTTLE            1.0    // speed multiplier to decrease steering sensitivity.  0.65 gives about a 4" turn radius at max throttle
#define K_STEERING            1.0    // speed multiplier to decrease steering sensitivity.  0.65 gives about a 4" turn radius at max throttle

int MAX_SPEED = 500;        // This corresponds to a range of 1000 to 2000
const bool debugOn = false;       // The overhead required by serial and delays would be bad for RC control. 
                                  // Make it easy to disable.

const bool RightReverse = true;  // Flips motor cw to ccw.
const bool LeftReverse = false;  // Flips motor cw to ccw.

// Variables
int left_speed;      //intake wheel
int right_speed;     //window
int l_speed; 
int r_speed;

void setup()                        
{
  if (debugOn) Serial.begin(9600);    // initialize serial communication at 9600 bits per second

  leftMotor.attach(RIGHT_PWM_0_PIN);     //intake wheels
  rightMotor.attach(RIGHT_MOTOR_PIN);     //window motor          
  servoMotor.attach(AUX_MOTOR_PIN);
 
//  pinMode(LED_BUILTIN, OUTPUT);  // pin 13 on the arduino    
}

void loop()
{   
/*  
 *   RC input
 */
  int throttle = pulseIn(THROTTLE_PIN, HIGH);  // Read throttle input.  Normally 1000 to 2000
  int steering = pulseIn(STEERING_PIN, HIGH);  // Read steering input.  Normally 1000 to 2000  
  int aux = pulseIn(AUX_PIN, HIGH);            // Read aux input.  Either ~1000 or ~2000 (basically binary)

  

/*  
 *   Print RC pulse widths to Serial Monitor
 */
  if (debugOn) {
    Serial.println("******");
    Serial.print("Throttle = ");
    Serial.print(throttle);
    Serial.print(", Steering = ");
    Serial.print(steering);
    Serial.print(", Aux = ");
    Serial.println(aux);
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

    if (aux > 1500)  {
      servoMotor.write(15);                 //command to rotate the servo to the specified angle 
    }
    else { 
      servoMotor.write(165);              //command to rotate the servo to the specified angle         
    }


    steeringNorm = steeringNorm * K_STEERING;      // Apply simple scaling to keep steering reasonable
    throttleNorm = throttleNorm * K_THROTTLE;

    if (debugOn) Serial.print("Throttle Norm = ");
    if (debugOn) Serial.print(throttleNorm);    
    if (debugOn) Serial.print("   Steering Norm = ");
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
         right_speed = -right_speed; 
       }
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

    leftMotor.writeMicroseconds(l_speed);       
    rightMotor.writeMicroseconds(r_speed);       
}
