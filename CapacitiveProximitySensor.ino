
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
  int inputRight = readCapacitiveSensor(A5);
  int inputLeft = readCapacitiveSensor(A0);
  
  workingAverageLeft += constrain(map(inputLeft, 400, 500, 3000, 0), 0, 3000);
  workingAverageRight += constrain(map(inputRight, 410, 515, 3000, 0), 0, 3000);
  samplesTaken++;
  
  if (samplesTaken == sampleSize) {
    unsigned int averageLeft = workingAverageLeft / sampleSize;
    unsigned int averageRight = workingAverageRight / sampleSize;
    Serial.print(averageLeft);
    Serial.print(", ");
    Serial.println(averageRight);
    //Serial.print(inputLeft);
    //Serial.print(", ");
    //Serial.println(inputRight);

    samplesTaken = 0;
    workingAverageLeft = 0;
    workingAverageRight = 0;
  }
  
  delayMicroseconds(10);
}

int readCapacitiveSensor(int sensorPin) {
  pinMode(sensorPin, OUTPUT);
  digitalWrite(sensorPin, LOW);
  //charge
  digitalWrite(sensorPin, HIGH);
  //read
  pinMode(sensorPin, INPUT);
  int input = analogRead(sensorPin);
  
  //discharge
  pinMode(sensorPin, OUTPUT);
  digitalWrite(sensorPin, LOW);
  
  return input;
}
