#include <Arduino.h>
#include <Ultrasonic.h>
#include <Servo.h>

// Define PIR sensor pin
const int pirPin = 2; // Replace with the actual pin number
int pirState = 0;

// Define ultrasonic sensor pins
const int trigPin = 3; // Replace with the actual pin number
const int echoPin = 4; // Replace with the actual pin number
Ultrasonic ultrasonic(trigPin, echoPin);
int ultrasonicState = 0;

// Define servo and LED pins
Servo myservo;
const int servoPin = 5; // Replace with the actual pin number
const int ledPin = 6;   // Replace with the actual pin number

// Define LED state
int ledState = LOW; // LOW means LED is off initially
unsigned long ledStartTime = 0;
const long ledDuration = 5000; // 5 seconds

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);

  // Initialize PIR sensor pin as input
  pinMode(pirPin, INPUT);
 
  // Initialize ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Initialize servo and LED pins
  myservo.attach(servoPin);
  pinMode(ledPin, OUTPUT);

  // Initialize PIR and ultrasonic states
  pirState = 0;
  ultrasonicState = 0;
}

void loop() {
  // Read PIR sensor state
  pirState = digitalRead(pirPin);

  // Read ultrasonic sensor distance in centimeters
  int distance = ultrasonic.read();
  
  // Determine ultrasonic state based on distance
  if (distance < 5) {
    ultrasonicState = 1;
  } else {
    ultrasonicState = 0;
  }

  // Print the PIR and ultrasonic states
  Serial.print("PIR State: ");
  Serial.println(pirState);
  Serial.print("Ultrasonic State: ");
  Serial.println(ultrasonicState);

  // Check if either sensor is triggered (1)
  if (pirState == 1 or ultrasonicState == 1) {
    myservo.write(90); // Open the servo to 90 degrees
    digitalWrite(ledPin, LOW); // Turn off the LED
    ledStartTime = millis(); // Reset the LED start time
  } else {
    // Both sensors are not triggered (0, 0)
    myservo.write(0);  // Close the servo to 0 degrees
    
    // Check if it's time to turn on the LED
    unsigned long currentMillis = millis();
    if (currentMillis - ledStartTime <= ledDuration) {
      ledState = HIGH; // Turn on the LED
    } else {
      ledState = LOW; // Turn off the LED
    }
    digitalWrite(ledPin, ledState);
  }

  // Optional delay to prevent rapid state changes
  delay(1000); // Adjust as needed
}



