#define trigPin 2
#define echoPin 3
#define pump 8
#define buzzer 9

int range = 7; // Range in inches

void setup() {
    // Initialize serial communication
    Serial.begin(9600);

    // Initialize the sensor pins
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(pump, OUTPUT);
    pinMode(buzzer, OUTPUT);

    digitalWrite(pump, HIGH);   // Turn off pump initially
    digitalWrite(buzzer, LOW);  // Turn off buzzer initially
}

void loop() {
    long duration, inches, cm;

    // Trigger the sensor
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10); // Increased delay to ensure a clean high pulse
    digitalWrite(trigPin, LOW);

    // Measure the echo duration
    duration = pulseIn(echoPin, HIGH);

    // Convert duration to distance
    inches = microsecondsToInches(duration);
    cm = microsecondsToCentimeters(duration);

    // Print distance
    Serial.print(inches);
    Serial.print(" in, ");
    Serial.print(cm);
    Serial.print(" cm");
    Serial.println();

    // Check distance and perform actions
    if (inches < 7) {
        Serial.println("Hand detected");
        digitalWrite(pump, LOW);    // Activate pump
        digitalWrite(buzzer, HIGH); // Activate buzzer
        delay(600);
        digitalWrite(pump, HIGH);   // Turn off pump
        digitalWrite(buzzer, LOW);  // Turn off buzzer
        delay(1300);
    } else {
        Serial.println("No hand");
        digitalWrite(pump, LOW);   // Turn off pump
        digitalWrite(buzzer, LOW); // Turn off buzzer
        delay(50);
    }

    delay(200); // Small delay between readings
}

long microsecondsToInches(long microseconds) {
    // Speed of sound is approximately 74 microseconds per inch
    return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
    // Speed of sound is approximately 29 microseconds per centimeter
    return microseconds / 29 / 2;
}

