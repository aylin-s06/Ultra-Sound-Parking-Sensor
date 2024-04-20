// Define pin numbers for components
const int led1 = 4;         // Pin for the green LED
const int led2 = 5;         // Pin for the red LED
const int echoPin = 2;      // Pin for the echo pin of the ultrasonic sensor
const int trigPin = 3;      // Pin for the trigger pin of the ultrasonic sensor
const int buzzerPin = 6;    // Pin for the buzzer
const int nThreshold = 30;  // Threshold distance in centimeters

// Variables for storing duration and distance
long nDuration;
int nDistance;

void setup() {
  // Set pin modes for components
  pinMode(led1, OUTPUT);     // Set led1 pin as output
  pinMode(led2, OUTPUT);     // Set led2 pin as output
  pinMode(trigPin, OUTPUT);  // Set trigPin as output
  pinMode(echoPin, INPUT);   // Set echoPin as input
  pinMode(buzzerPin, OUTPUT);// Set buzzerPin as output
  
  // Start serial communication
  Serial.begin(9600);
  
  // Print starting message
  Serial.println("Starting ultrasonic detector...");
}

void loop() {
  // Send trigger signal to ultrasonic sensor
  digitalWrite(trigPin, HIGH);      // Set trigPin high
  delayMicroseconds(10);             // Wait for 10 microseconds
  digitalWrite(trigPin, LOW);       // Set trigPin low
  
  // Measure duration of echo signal
  nDuration = pulseIn(echoPin, HIGH);  // Measure pulse duration from echoPin
  
  // Calculate distance based on duration
  nDistance = nDuration * (0.034 / 2); // Convert duration to distance in cm (speed of sound is 0.034 cm/μs)
  
  // Print distance to serial monitor
  Serial.print(nDistance);             // Print distance value
  Serial.println(" cm");               // Print units
  
  // Check if distance is less than threshold
  if (nDistance < nThreshold) {
    // Activate buzzer and red LED
    tone(buzzerPin, 2000);             // Produce tone on buzzer pin
    digitalWrite(led2, HIGH);          // Turn on red LED
    delay(400);                         // Wait for 400 milliseconds
    noTone(buzzerPin);                 // Turn off buzzer
    delay(300);                        // Wait for 300 milliseconds
    digitalWrite(led2, LOW);           // Turn off red LED
  } else {
    // Activate green LED
    digitalWrite(led1, HIGH);          // Turn on green LED
    delay(400);                         // Wait for 400 milliseconds
    digitalWrite(led1, LOW);           // Turn off green LED
  }
}
