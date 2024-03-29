#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
int level = 1;
int second = (4 - level) * 1000;
int score = 0;
int valuetrue = 0;   //the value from right button after clicking time
int valuefalse1 = 0; // the value from other 
int valuefalse2 = 0; // 2 wrong buttons


void turnONlight(int number) // for 'number' is the number of lights that turn ON
{
  int start = 13 - number + 1;
  for (int i = start; i <= 13; i++)
  {
    digitalWrite(i, HIGH);
  }
}

void turnOFFalllight()
{
  for (int i = 4; i <= 13; i++)
  {
    digitalWrite(i, LOW);
  }
}

void Getresult(int number)
{
  int rightanswer = number % 3;
  Serial.println(rightanswer);
  delay(second); // delay seconds for clicking
  switch (rightanswer) {
  case 0: // x%3 = 0 -> button left is correct
    valuetrue = digitalRead(A0);
    valuefalse1 = digitalRead(A1);
    valuefalse2 = digitalRead(A2);
    break;
  case 1: // button middle is correct
    valuefalse1 = digitalRead(A0);
    valuetrue = digitalRead(A1);
    valuefalse2 = digitalRead(A2);
    break;
  case 2: //button right is correct
    valuefalse1 = digitalRead(A0);
    valuefalse2 = digitalRead(A1);
    valuetrue = digitalRead(A2);
    break;
  }
}

void Checkresult(int valtrue, int valfalse1, int valfalse2)
{
  if(valtrue == 1) //clicked correctly
  {
    score++;
    if (level < 3)
    {
      level++;
    }
    // if level is 3 do nothing about Level
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(String("Lv ") + String(level) + String(". Score: ") + String(score));
    lcd.setCursor(0, 1);
    lcd.print("CORRECT!!!");
  }
  else //right button is not clicked
  {
    score--;
    if (valfalse1 == 0 && valfalse2 == 0) //both wrong buttons are not clicked
    {
      if (level > 1)
      {
        level--;
      }
      //if level is 1 do nothing about Level
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(String("Lv ") + String(level) + String(". Score: ") + String(score));
      lcd.setCursor(0, 1);
      lcd.print("TIME OUT!!!");
    }
    else // click wrong button
    {
      level = 1;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(String("Lv ") + String(level) + String(". Score: ") + String(score));
      lcd.setCursor(0, 1);
      lcd.print("INCORRECT!!!");
    }  
  }
  // set new delay seconds
  second = (4 - level) * 1000;
  // reset check value for 3 buttons
  valuetrue = 0;
  valuefalse1 = 0;
  valuefalse2 = 0;
}

void setup(){
  lcd.init();
  lcd.begin(16,2);
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print(String("Lv ") + String(level) + String(". Score: ") + String(score));
  lcd.setCursor(0, 1);
  lcd.print("READY");
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT); 
  pinMode(A2, INPUT);
  for (int i = 4; i <= 13; i++)
  {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(String("Lv ") + String(level) + String(". Score: ") + String(score));
  lcd.setCursor(0, 1);
  lcd.print("GO!!!");
  int number = random(1, 11); //number of ON light random from 1 to 10
  turnONlight(number);
  Getresult(number);
  Checkresult(valuetrue, valuefalse1, valuefalse2);
  //lcd.clear();
  turnOFFalllight();
}
