#include <Wire.h>
#include <BH1750.h>
//SCL brown A5
//SDA orange A4
BH1750 lightMeter;
int buttonPin = 12;
int maxLED = 10;
int buttonState;
int previousbuttonState = LOW;
unsigned long starttime = 0;
unsigned long endtime = 0 ;
long debounceDelay = 700;
int buttoncount = 0;

void HandleFullPowerMode(int MAXPin)
{
  for (int i = 2; i <= MAXPin; i++)
  {
    digitalWrite(i, HIGH);
  }
  for (int i = MAXPin + 1; i <= 11; i++)
  {
    digitalWrite(i, LOW);
  }
}

void HandleSavePowerMode(int MAXPin)
{
  for (int i = 2; i <= MAXPin; i++)
  {
    digitalWrite(i, HIGH);
  }
  for (int i = MAXPin + 1; i <= 6; i++)
  {
    digitalWrite(i, LOW);
  }
  for (int i = 7; i <= 11; i++) // from 6th light to 11th light will always OFF
  {
    digitalWrite(i, LOW);
  }
}

void turnOFFlights(int maxlights, float value) //turn off a number of light base on sensor value
{
  if (value > 300) // if value too high -> reduce to max value that in the map's range
  {
    value = 300;
  }
  int LedNumOFF = map(value, 0, 300, 0, maxlights); // tính số đèn sẽ tắt trong 1 chế độ bất kỳ
  int LedNumON = maxlights - LedNumOFF; // tính số đèn sẽ bật trong 1 chế độ bất kỳ
  int maxPin = LedNumON + 1; // tính mã PIN cao nhất được phép bật trong mỗi chế độ
  switch (maxlights)
  {
    case 5:
      HandleSavePowerMode(maxPin);
      break;
    case 10:
      HandleFullPowerMode(maxPin);
      break;
    default:
      break;
  }
}

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  lightMeter.begin();
  for (int i = 2; i <= 11; i++)
  {
    pinMode(i,OUTPUT);
  }
  pinMode(buttonPin,INPUT);
}

void Checkbuttoncount(int count)
{
  switch(buttoncount){
    case 1:
      maxLED = 5;
      break;
    case 2:
      maxLED = 10;
      break;
    default:
      break;
  }
  buttoncount = 0;
  previousbuttonState = LOW;
}

void loop()
{
  buttonState = digitalRead(buttonPin);
  Serial.println(buttonState);
  if ((millis() - starttime) > debounceDelay) // Time multiclicks expired -> 1 click
  {
    Checkbuttoncount(buttoncount);
  }
  if(buttonState == HIGH && previousbuttonState == LOW) // first click
  {
    buttoncount++;
    previousbuttonState = HIGH;
    starttime = millis();
  }
  else if (buttonState == HIGH && previousbuttonState == HIGH) // click 2 times
  {
    buttoncount++;
    Checkbuttoncount(buttoncount);
  }
  

  //TurnMaxlights();
  
  float lux = lightMeter.readLightLevel();
  turnOFFlights(maxLED, lux);
  Serial.println(maxLED);
  
  delay(150);
}
