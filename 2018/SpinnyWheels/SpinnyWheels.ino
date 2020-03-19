

/*

Turns motor on if button is pressed. 

Arduino Board setup:
5V with pullup resistor attached to pin 7
PWM pin 9 to vexpro vector xp motor controller
Pin 7 to button red
GND to button black

By: Steve Olson. Jan 2017

*/

//output pin
int PWMpin=9;
double sensorValue=0;
int pin7 = 7; // button pin
bool pin7value= HIGH; // motor starts off

void setup() {
  // initialize serial communication at 9600 bits per second;
  Serial.begin(9600);
  pinMode(pin7, INPUT); //
 
}

// the loop routine runs over and over again forever:
void loop() {
  
// /191-254 is clockwise spin with red to green, white to black motor connection
  pin7value=digitalRead(pin7);
  if(pin7value == LOW){
    //Serial.println("I'm LOW");
  analogWrite(PWMpin,250);
  }
  else{
    analogWrite(PWMpin,185);
    //Serial.println("I'm HIGH");
  }

  //Serial.println(pin7);
  //Serial.println(pin4);
  //Serial.println(pin7value);

  
}
