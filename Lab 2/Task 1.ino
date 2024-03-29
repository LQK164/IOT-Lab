const int trigPin = 2;
const int echoPin = 13;
int ledPin = 6;
int lightSpeed = 1200;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);   
  pinMode(trigPin,OUTPUT);   
  pinMode(echoPin,INPUT); 
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1; //get dis
  if (distance >= 150)                        //dis >=150 -> Out
  {
    lightSpeed = 1500;
    Serial.println("No level: Out of range");
  }
  else if (distance < 150 && distance >= 120) //120 <= dis < 150 -> lv5
  {
    lightSpeed = 1000;
    Serial.print("Level 5: ");
    Serial.print(distance);
    Serial.println(" cm");
  }
  else if (distance < 120 && distance >= 90) //90 <= dis < 120 -> lv4
  {
    lightSpeed = 800;
    Serial.print("Level 4: ");
    Serial.print(distance);
    Serial.println(" cm");
  }
  else if (distance < 90 && distance >= 60) //60 <= dis < 90 -> lv3
  {
    lightSpeed = 600;
    Serial.print("Level 3: ");
    Serial.print(distance);
    Serial.println(" cm");
  }
  else if (distance < 60 && distance >= 30) //30 <= dis < 60 -> lv2
  {
    lightSpeed = 400;
    Serial.print("Level 2: ");
    Serial.print(distance);
    Serial.println(" cm");
  }
  else if (distance < 30 && distance >= 0) //0 <= dis < 30 -> lv1
  {
    lightSpeed = 200;
    Serial.print("Level 1: ");
    Serial.print(distance);
    Serial.println(" cm");
  }
  digitalWrite(ledPin, HIGH);
  delay(lightSpeed);
  digitalWrite(ledPin, LOW);
  delay(lightSpeed);
}
