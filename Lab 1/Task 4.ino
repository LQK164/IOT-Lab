#include "SevSeg.h"
SevSeg sevseg;

int timedelay = 1000;
int red1Pin = 13;
int yellow1Pin = 12;
int green1Pin = 2;
const int red2Pin = A0;
const int yellow2Pin = A1;
const int green2Pin = A2;

//display number
void displayNum(int number) 
{
  sevseg.setNumber(number);
  sevseg.refreshDisplay(); 
  delay(timedelay);
} 

void HandleRed1stSecond()
{
  digitalWrite(red1Pin, HIGH); //red1 ON
  analogWrite(red2Pin, 0); //red2 OFF
  digitalWrite(yellow1Pin, LOW); //yellow1 OFF
  analogWrite(green2Pin, 255); //green2 ON
}

void HandleRed6thsecond()
{
  analogWrite(yellow2Pin, 255); //yellow2 ON
  analogWrite(green2Pin, 0); //green2 OFF
}

void HandleYellow1stSecond()
{
  digitalWrite(yellow1Pin, HIGH); //yellow1 ON
  digitalWrite(green1Pin, LOW); //green1 OFF
}

void HandleGreen1stsecond()
{
  digitalWrite(red1Pin, LOW); //red1 OFF
  analogWrite(red2Pin, 255); //red2 ON
  analogWrite(yellow2Pin, 0); //yellow2 OFF
  digitalWrite(green1Pin, HIGH); //green1 ON
}

void StartRed()
{
  HandleRed1stSecond();
  displayNum(9);
  
  displayNum(8);
  
  displayNum(7);
  
  displayNum(6);
  
  displayNum(5);
  
  displayNum(4);
  
  displayNum(3);
  
  HandleRed6thsecond();
  displayNum(2);
  
  displayNum(1);
  
  displayNum(0);
}

void StartYellow()
{
  HandleYellow1stSecond();
  displayNum(3);
  
  displayNum(2);
  
  displayNum(1);
  
  displayNum(0);
}

void StartGreen()
{
  HandleGreen1stsecond();
  displayNum(6);
  
  displayNum(5);
  
  displayNum(4);
  
  displayNum(3);
  
  displayNum(2);
  
  displayNum(1);
  
  displayNum(0);
}

void setup() 
{ 
  //Set to 1 for single digit display
  byte numDigits = 1;
  //defines common pins while using multi-digit display. Left empty as we have a single digit display
  byte digitPins[] = {};
  //Defines arduino pin connections in order: A, B, C, D, E, F, G, DP
  byte segmentPins[] = {7, 6, 5, 11, 10, 8, 9, 4};
  bool resistorsOnSegments = true;
  //Initialize sevseg object. Uncomment second line if you use common cathode 7 segment
  sevseg.begin(COMMON_ANODE, numDigits, digitPins, segmentPins, resistorsOnSegments);
  //sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(90);
  int i;
  for(i=2;i<=13;i++)
  {
    pinMode(i,OUTPUT);
  }
  pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);
  pinMode(A2,OUTPUT);
} 
void loop() 
{
  StartGreen();
  StartYellow();
  StartRed();
}
