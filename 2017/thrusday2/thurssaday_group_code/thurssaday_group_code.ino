// hi hows life
#include <Servo.h>

byte leftPin = 11;
byte rightPin = 10;
byte climbPin = 9;

Servo left;  // these arent right but whatever
Servo right;
Servo climb;
// twelve servo objects can be created on most boards

int posl = 0;
int posr = 0;
int posc = 0;
// variable to store the servo positions

void setup() {
  left.attach(6);
  right.attach(5);
  climb.attach(3);

  pinMode(leftPin, INPUT);
  pinMode(rightPin, INPUT);
  pinMode(climbPin, INPUT);
  // pins (these arent right either)
}

void loop() {
  posl = pulseIn(leftPin, HIGH);
  posr = pulseIn(rightPin, HIGH);
  posc = pulseIn(climbPin, HIGH);

  left.write(posl);
  right.write(posr);
  climb.write(posc);
}
// hey but it works!
