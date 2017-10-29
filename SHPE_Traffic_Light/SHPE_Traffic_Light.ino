// Author: Alejandro Millan and Allen Aboytes
// Date:   October 21, 2017
// Description: Simulates a simple traffic light
// Senses when a "car" is close then changes lights

//Material: Proximety Sensor, RGB leds, 130 ohms resistors
//Update:  October 25, 2017

// Led Pin Indexes
#define RED 4
#define YELLOW 3
#define GREEN 2
// Sonic Sensor Pin Indexes
#define TRIG 0
#define ECHO 1
// Sensor Distance Ranges
#define threshold 15
#define ONE_SECOND 1000

int numOfPins = 5;
int pins[] = {5,6,9,10,11};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //Enables Serial  Communications
  // Enabling pins for output
  int i;
  for (i = 1; i < numOfPins; i++) {
    pinMode(pins[i], OUTPUT);     
  }
  
  pinMode(pins[ECHO],INPUT);
  pinMode(pins[TRIG], OUTPUT);
  
  // Initialize traffic light to red
  digitalWrite(pins[RED],HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:

  int distance = sensorDistance();
  
  if(distance <= threshold && distance != 0){
    digitalWrite(pins[RED], LOW);
    digitalWrite(pins[GREEN], HIGH);
  }
    else if(distance >= threshold && distance != 0){
      if(digitalRead(pins[GREEN]) == HIGH){
        digitalWrite(pins[GREEN],LOW);
        digitalWrite(pins[YELLOW],HIGH);
        delay(ONE_SECOND); // 1 sec delay
        digitalWrite(pins[YELLOW],LOW);
        digitalWrite(pins[RED],HIGH);
    }
  } 
  Serial.println(distance);
  delay(ONE_SECOND/2); 
}

int sensorDistance(void) {
  // Clears the trigger pin
  digitalWrite(pins[TRIG], LOW);
  delayMicroseconds(2);
  // Sets the trigger pin on HIGH state for 10 micro seconds
  digitalWrite(pins[TRIG], HIGH);
  delayMicroseconds(10);
  digitalWrite(pins[TRIG], LOW);
  // Reads the echo pin, returns the sound wave travel time in microseconds
  long duration = pulseIn(pins[ECHO], HIGH);
  // Calculating the distance
  int distance= duration*0.034/2;
  
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  

  return distance;
}
