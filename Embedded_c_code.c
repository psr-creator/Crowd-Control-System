#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int entryPin = 8;
int entryRead;
int exitPin = 9;
int exitRead;
byte NTCPin = A0;
#include <Wire.h>
#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
#define SERIESRESISTOR 10000
#define NOMINAL_RESISTANCE 10000
#define NOMINAL_TEMPERATURE 25
#define BCOEFFICIENT 3950
int incrementPin = 6;
int decrementPin = 7;
int setPin = 10;
int setCount;

void setup() {
  pinMode (entryPin, INPUT);
  pinMode (exitPin, INPUT);
  lcd.begin(16, 2);
  mlx.begin();
  Serial.begin(9600);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(10, INPUT);
}

void loop() {
  setCount = 0;
  int x = 1;
  while (x == 1) {
    int increment = digitalRead(incrementPin);
    int decrement = digitalRead(decrementPin);
    int set = digitalRead(setPin);
    if (increment == HIGH) {
      delay(1000);
      setCount = setCount + 1;
      lcd.clear();
    }
    if (decrement == HIGH) {
      delay(1000);
      setCount = setCount - 1;
      lcd.clear();
    }
    if (set == HIGH) {
      x = x + 1;
      lcd.clear();
    }
    lcd.setCursor(0, 0);
    lcd.print("SetCount:");
    lcd.print(setCount);
    }
lcd.clear();
int count = 0;
while (1)
{
  entryRead = digitalRead(entryPin);
  exitRead = digitalRead(exitPin);
  if (exitRead == LOW) {
    if (count == setCount)
    {
      lcd.clear();
    }
    count = count - 1;
    delay(1000);
  }
  if (count < setCount)
  {
    if (entryRead == LOW)
    {
      count = count + 1;
      lcd.setCursor(0, 1);
      lcd.print("Wait");
      delay(2000);
      lcd.print("Temp: ");
      lcd.print(mlx.readObjectTempC());
      lcd.print("C");
      delay(2000);
      lcd.clear();
    }
    }
    if (count >= setCount) {
      lcd.setCursor(0, 1);
      lcd.print("NO ENTRY");
}
   lcd.setCursor(0, 0);
    lcd.print("Count:");
    lcd.print(count);
 }
}
