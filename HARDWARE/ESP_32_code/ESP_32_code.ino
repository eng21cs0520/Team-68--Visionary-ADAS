#define ENA 6
#define ENB 5
#define IN1 7
#define IN2 3
#define IN3 4
#define IN4 2

void setup() {
    Serial.begin(115200); // Start Serial Monitor

    // Set all motor control pins as OUTPUT
    pinMode(ENA, OUTPUT);
    pinMode(ENB, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);

    // Enable the motors
    digitalWrite(ENA, HIGH);
    digitalWrite(ENB, HIGH);
    Serial.println("Motor Test Starting...");
}

void loop() {
    Serial.println("Testing LEFT Motor FORWARD...");
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    delay(2000);
    
    Serial.println("Testing LEFT Motor BACKWARD...");
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    delay(2000);
    
    Serial.println("Testing RIGHT Motor FORWARD...");
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    delay(2000);
    
    Serial.println("Testing RIGHT Motor BACKWARD...");
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    delay(2000);
    
    Serial.println("Stopping Motors...");
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    delay(3000); // Wait before restarting test
}
