#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define analogPin A0
#define digitalPin 2
#define vccPin 4
#define motorPin 7
#define buttonPlus 3
#define buttonMinus 2


unsigned long cas = 0; 
volatile byte state = LOW;
int zavlazovaciBod = 650;
int cislo = 0;
void setup() {
  
  
  pinMode(analogPin, INPUT);
  pinMode(digitalPin, INPUT);
  pinMode(vccPin, OUTPUT);
  pinMode(motorPin, OUTPUT);
  pinMode(buttonPlus, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonPlus), funkce_plus, RISING);
  pinMode(buttonMinus, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonMinus), funkce_minus, RISING);
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

void funkce_plus(){
    zavlazovaciBod+=50;
  }

void funkce_minus(){
    zavlazovaciBod-=50;
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

  
    if(analog > zavlazovaciBod){
      digitalWrite(motorPin, HIGH);
      delay(3000);
      digitalWrite(motorPin,LOW);
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
