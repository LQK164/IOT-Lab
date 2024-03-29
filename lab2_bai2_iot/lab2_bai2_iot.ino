#include "SevSeg.h"
SevSeg sevseg;
int trigPin = 3;
int echoPin = 2;

//display number for 1 second
void DisplayNum(int number) 
{
  sevseg.setNumber(number);
  sevseg.refreshDisplay();
  
  if (number == 0)
  {
    Serial.println("Out of range");
  }
  else
  {
    Serial.println(number);
  }
  delay(600);
} 

void setup() 
{ 
  Serial.begin(9600);
  //Set to 1 for single digit display
  byte numDigits = 1;
  //defines common pins while using multi-digit display. Left empty as we have a single digit display
  byte digitPins[] = {};
  //Defines arduino pin connections in order: A, B, C, D, E, F, G, DP
  byte segmentPins[] = {5, 4, 7, 8, 9, 10, 11, 6};
  bool resistorsOnSegments = true;
  //Initialize sevseg object. Uncomment second line if you use common cathode 7 segment
  sevseg.begin(COMMON_ANODE, numDigits, digitPins, segmentPins, resistorsOnSegments);
  //sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(90);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
} 

// Get distance in cm
long GetDis()
{
  long duration, distance;
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  Serial.print("Distance: ");
  Serial.println(distance);
  return distance;
}

// Check distance value and return the respective LED number
int GetLEDNum(long distance)
{
  if (distance >= 0 && distance < 20) // 0 <= dis < 20 -> LED = 1
  {
    return 1;
  }
  else if (distance >= 20 && distance < 40) // 20 <= dis < 40 -> LED = 2
  {
    return 2;
  }
  else if (distance >= 40 && distance < 60) // 40 <= dis < 60 -> LED = 3
  {
    return 3;
  }
  else if (distance >= 60 && distance < 80) // 60 <= dis < 80 -> LED = 4
  {
    return 4;
  }
  else if (distance >= 80 && distance < 100) // 80 <= dis < 100 -> LED = 5
  {
    return 5;
  }
  else if (distance >= 100 && distance < 120) // 100 <= dis < 120 -> LED = 6
  {
    return 6;
  }
  else if (distance >= 120 && distance < 140) // 120 <= dis < 140 -> LED = 7
  {
    return 7;
  }
  else if (distance >= 140 && distance < 160) // 140 <= dis < 160 -> LED = 8
  {
    return 8;
  }
  else if (distance >= 160 && distance <= 180) // 160 <= dis <= 180 -> LED = 9
  {
    return 9;
  }
  else if (distance > 180) // 180 < dis -> LED = 0
  {
    return 0;
  }
}

void loop()
{
  long distance = GetDis();
  int LedNum = GetLEDNum(distance);
  DisplayNum(LedNum);
}
