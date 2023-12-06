#include <Servo.h>
int s1,s2,s3;
int pos;
int var = 0;
Servo door;
Servo bidet;
bool userDetected = false; // Flag to track user detection
unsigned long detectionStartTime; // Timestamp when user is first detected
void setup() {
  door.attach(3); // Servo door
  pinMode(2,INPUT); // Entry IR
  pinMode(4,INPUT); // Exit IR
  bidet.attach(5);  // bidet Servo
  pinMode(6,INPUT); // bidet IR

}

void loop() {
s1 = digitalRead(2);
s2 = digitalRead(4);
s3 = digitalRead(6);

  if(s1==0 or s2==0) 
  {
    pos=0;
    //For opening gate from both sides
    door.write(pos);
      }
  if(s1==1 and s2==1)
  {
    pos=90;
    door.write(pos);
  } 
   if (s3 == 0) {
    // User is detected
    if (!userDetected) {
      // Record the time when the user is first detected
      detectionStartTime = millis();
      userDetected = true;
    }
   }
   else {
    // User is not detected
    userDetected = false;
  }
  // Check if the user has been detected for 3 seconds
  if (userDetected && (millis() - detectionStartTime >= 3000)) {
    bidet.write(90); // Turn on the bidet servo
  } 
  else {
    bidet.write(0); // Turn on the bidet servo
  }

}