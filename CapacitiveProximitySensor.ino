
unsigned int sampleSize = 200;
unsigned long workingAverageLeft = 0;
unsigned long workingAverageRight = 0;
unsigned int samplesTaken = 0;
void setup() {
  Serial.begin(19200);
  //discharge
  pinMode(A0, OUTPUT);
  digitalWrite(A0, LOW);
  //discharge
  pinMode(A5, OUTPUT);
  digitalWrite(A5, LOW);
}

void loop() {

  //discharge
  pinMode(A0, OUTPUT);
  digitalWrite(A0, LOW);
  
  //reads the right sensor in pin A5
  int inputRight = readCapacitiveSensor(A5);
  //reads the left sensor in pin A0
  int inputLeft = readCapacitiveSensor(A0);
  
  //adds the current reading to the working average
  workingAverageLeft += constrain(map(inputLeft, 400, 500, 3000, 0), 0, 3000);
  workingAverageRight += constrain(map(inputRight, 410, 515, 3000, 0), 0, 3000);
  //increments number of samples taken
  samplesTaken++;
  
  //if we have taken enough samples, calculate the average and print it to Serial out.
  //these values can then be read from other programs.
  if (samplesTaken == sampleSize) {
    unsigned int averageLeft = workingAverageLeft / sampleSize;
    unsigned int averageRight = workingAverageRight / sampleSize;
    Serial.print(averageLeft);
    Serial.print(", ");
    Serial.println(averageRight);

    samplesTaken = 0;
    workingAverageLeft = 0;
    workingAverageRight = 0;
  }
  
  //delay 10 microseconds
  delayMicroseconds(10);
}

int readCapacitiveSensor(int sensorPin) {
  //discharge
  pinMode(sensorPin, OUTPUT);
  digitalWrite(sensorPin, LOW);
  //charge
  digitalWrite(sensorPin, HIGH);
  //read
  pinMode(sensorPin, INPUT);
  int input = analogRead(sensorPin);
  
  //discharge again at the end to avoid crosstalk
  //between capacitive plates. If there were only one
  //sensor this would no longer be necessary.
  pinMode(sensorPin, OUTPUT);
  digitalWrite(sensorPin, LOW);
  
  return input;
}
