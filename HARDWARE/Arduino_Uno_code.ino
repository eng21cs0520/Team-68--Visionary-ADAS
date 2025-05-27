#include <IRremote.h>
#include <Servo.h>

// Define IR Receiver Pin
#define IR_RECEIVE_PIN 11
#define DECODE_NEC  // Ensure we use NEC protocol

// Motor Driver L298N Pins
#define ENA 5
#define IN1 6
#define IN2 7
#define IN3 10
#define IN4 8
#define ENB 9

// Ultrasonic Sensor Pins
#define TRIG_PIN 3
#define ECHO_PIN 2

// Line Tracker Sensors
#define LEFT_SENSOR A0
#define MID_SENSOR A1
#define RIGHT_SENSOR A2

// Servo Motor Pin
#define SERVO_PIN 4
Servo ultrasonicServo;

// IR Remote Codes
#define UP_ARROW  0xE718FF00
#define DOWN_ARROW 0xAD52FF00
#define RIGHT_ARROW 0xA55AFF00
#define LEFT_ARROW 0xF708FF00
#define OK_BUTTON  0xE31CFF00

int lastDistance = 100;  // Variable to store the last measured distance

void setup() {
    Serial.begin(9600);

    // IR Remote Setup
    IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);

    // Motor Pins as Output
    pinMode(ENA, OUTPUT);
    pinMode(ENB, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);

    // Ultrasonic Sensor Pins
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    // Line Sensors as Input
    pinMode(LEFT_SENSOR, INPUT);
    pinMode(MID_SENSOR, INPUT);
    pinMode(RIGHT_SENSOR, INPUT);

    // Attach Servo & Set to Center
    ultrasonicServo.attach(SERVO_PIN);
    delay(500);
    ultrasonicServo.write(90);  // Center the servo

    Serial.println("Setup Complete!");
}

// Function to Read Distance
int getDistance() {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    long duration = pulseIn(ECHO_PIN, HIGH);
    int distance = duration * 0.034 / 2;  // Convert to cm

    // Check if the object is approaching too fast
    if (lastDistance - distance > 10) {  
        Serial.println("AIRBAG DEPLOYED!");
    }

    // Store current distance for next reading comparison
    lastDistance = distance;

    // Print danger alert if distance is below threshold
    if (distance < 20) {
        Serial.println("DANGER: Obstacle too close!");
    }

    return distance;
}

// Function to Move Motors
void moveForward() {
    Serial.println("Moving Forward...");
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENA, 150);
    analogWrite(ENB, 150);
}

void moveBackward() {
    Serial.println("Moving Backward...");
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(ENA, 150);
    analogWrite(ENB, 150);
}

void turnLeft() {
    Serial.println("Turning Left...");
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENA, 150);
    analogWrite(ENB, 150);
}

void turnRight() {
    Serial.println("Turning Right...");
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(ENA, 150);
    analogWrite(ENB, 150);
}

void stopMotors() {
    Serial.println("Motors Stopped.");
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
}

// Function to Handle Obstacle Avoidance
void avoidObstacles() {
    int distance = getDistance();
    if (distance < 20) {
        stopMotors();
        delay(500);

        ultrasonicServo.write(180);
        delay(500);
        int leftDistance = getDistance();

        ultrasonicServo.write(150);
        delay(500);
        int rightDistance = getDistance();

        ultrasonicServo.write(160);  // Reset to center
        delay(500);

        if (leftDistance > rightDistance) {
            turnLeft();
            delay(500);
        } else {
            turnRight();
            delay(500);
        }
    } else {
        moveForward();
    }
}

// Function to Handle Line Tracking
void followLine() {
    int left = digitalRead(LEFT_SENSOR);
    int mid = digitalRead(MID_SENSOR);
    int right = digitalRead(RIGHT_SENSOR);

    if (mid == HIGH) {
        Serial.println("Following Line...");
        moveForward();
    } else if (left == HIGH) {
        Serial.println("Line detected on left! Adjusting...");
        turnLeft();
    } else if (right == HIGH) {
        Serial.println("Line detected on right! Adjusting...");
        turnRight();
    } else {
        Serial.println("No line detected! Stopping...");
        stopMotors();
    }
}

// Function to Handle Remote Control Commands
void remoteControl() {
    if (IrReceiver.decode()) {
        uint32_t command = IrReceiver.decodedIRData.decodedRawData;
        Serial.print("Detected Code: ");
        Serial.print(command, HEX);

        switch (command) {
            case UP_ARROW:
                Serial.println(" - Moving Forward!");
                moveForward();
                break;
            case DOWN_ARROW:
                Serial.println(" - Moving Backward!");
                moveBackward();
                break;
            case LEFT_ARROW:
                Serial.println(" - Turning Left!");
                turnLeft();
                break;
            case RIGHT_ARROW:
                Serial.println(" - Turning Right!");
                turnRight();
                break;
            case OK_BUTTON:
                Serial.println(" - Stopping!");
                stopMotors();
                break;
            default:
                Serial.println(" - Unknown Command");
                break;
        }
        IrReceiver.resume();
    }
}

void loop() {
    remoteControl();
    avoidObstacles();
    followLine();
}
