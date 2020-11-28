#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define analogPin A0
#define digitalPin 3
#define vccPin 4
#define motorPin 7

unsigned long cas = 0;

void setup() {
  pinMode(analogPin, INPUT);
  pinMode(digitalPin, INPUT);
  pinMode(vccPin, OUTPUT);
  pinMode(motorPin, OUTPUT);

  digitalWrite(vccPin, LOW);
  digitalWrite(motorPin, LOW);

  lcd.begin();

  lcd.backlight();
  lcd.print("Pudni vlhkomer");
  lcd.setCursor(0, 1);
  lcd.print("S:");
  lcd.setCursor(2, 1);

  lcd.setCursor(10, 1);
  lcd.print("M:");
}

void loop() {
  
  if (millis() - cas > 3000) {
    digitalWrite(vccPin, HIGH);
    delay(100);
    int analog = analogRead(analogPin);
    bool digit = digitalRead(digitalPin);
    
    lcd.setCursor(2, 1);
    lcd.print("    ");
    lcd.setCursor(2, 1);
    lcd.print(analog);
    if(analog > 600){
      digitalWrite(motorPin, HIGH);
      lcd.setCursor(12, 1);
      lcd.print("ON ");
    }else {
      digitalWrite(motorPin, LOW);
      lcd.setCursor(12, 1);
      lcd.print("OFF");
    }
    
    digitalWrite(vccPin, LOW);
    cas = millis();
  }
}
