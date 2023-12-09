#include <Servo.h>

Servo servoMotor;  // Create a servo object

void setup() {
  Serial.begin(9600);  // Set up serial communication
  servoMotor.attach(9);  // Attach the servo to pin 9
}

void loop() {
// In the Arduino loop
if (Serial.available() > 0) {
  char receivedChar = Serial.read();  // Read the incoming data
  if (receivedChar == '1') {
    // Move the servo to position 1
    servoMotor.write(0);
    delay(2000);
    // Reset the servo position
    servoMotor.write(90);  // Adjust the angle as needed
  } else if (receivedChar == '2') {
    // Move the servo to a neutral position or the initial position
    servoMotor.write(90);  // Adjust the angle as needed
    delay(500);
  }
  // Clear the serial buffer
  while (Serial.available() > 0) {
    Serial.read();
  }
}
}
