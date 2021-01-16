//Zavlažovací systém
//Knihovna pro komunikaci základní desky se sběrnicí I2C
#include <Wire.h> 
//Knihovna pro nastavování LCD displeje se sběrnicí I2C
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

//Nastavení čísel propojovacích pinů
#define analogPin A0
#define digitalPin 2
#define vccPin 4
#define motorPin 7
#define buttonPlus 3
#define buttonMinus 2

//Proměnná pro uložení času kontroly
unsigned long cas = 0; 
volatile byte state = LOW;
//Globální proměnná s hodnotou bodu zalévání (globální proto, aby fungovala i ve funkcích)
int zavlazovaciBod = 650;
int cislo = 0;
void setup() {
  
  //Nastavení datových pinů jako vstupů
  //A napájecího pinu jako výstupu
  pinMode(analogPin, INPUT);
  pinMode(digitalPin, INPUT);
  pinMode(vccPin, OUTPUT);
  pinMode(motorPin, OUTPUT);
  pinMode(buttonPlus, INPUT_PULLUP);
  //Nastavení tlačítek pro regulaci hodnoty
  attachInterrupt(digitalPinToInterrupt(buttonPlus), funkce_plus, RISING);
  pinMode(buttonMinus, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonMinus), funkce_minus, RISING);
  // vypnutí napájecího napětí pro modul
  digitalWrite(vccPin, LOW);
  digitalWrite(motorPin, LOW);
 
  //Rozjetí a nastavení LCD displeje
  lcd.begin();

  lcd.backlight();
  lcd.print("Pudni vlhkomer");
  lcd.setCursor(0, 1);
  lcd.print("S:"); //Data senzoru
  lcd.setCursor(2, 1);
  
  lcd.setCursor(10, 1);
  lcd.print("M:");//Zda je motor zapnutý či vypnutý
}
}

//Funkce, která se spustí při attachInterruptu - změní globální hodnotu, nehledě na stav kódu
void funkce_plus(){
    zavlazovaciBod+=50;
  }
//Stejná funkce
void funkce_minus(){
    zavlazovaciBod-=50;
  }

void loop() {
  //Pokud je rozdíl mezi aktuálním časem a posledním
  //Uloženým časem větší než 3000 ms, provede se měření
  if (millis() - cas > 3000) {
    //Zapneme napájecí napětí pro modul s krátkou pauzou pro ustálení
    digitalWrite(vccPin, HIGH);
    delay(100);
    //Načtení analogové a digitální hodnoty do proměnných
    int analog = analogRead(analogPin);
    bool digit = digitalRead(digitalPin);
    //Vypsání daných hodnot na displej
    lcd.setCursor(2, 1);
    lcd.print("    ");
    lcd.setCursor(2, 1);
    lcd.print(analog);

    //Funkce, která se spustí, když hodnota analogu je větší než bod zavlažování
    if(analog > zavlazovaciBod){
      digitalWrite(motorPin, HIGH);
      delay(3000);
      //Čerpadlo bude zapnuto 3 vteřiny a poté se vypne, po vypnutí se opět provede měření vlhkosti
      digitalWrite(motorPin,LOW);
      lcd.setCursor(12, 1);
      lcd.print("ON "); //Vypsání na displej, zda je čerpadlo zapnuto
    }else {
      //Pokud je analog menší než hodnota bodu zavlažování, funce se nespustí a čerpadlo zůstane vypnoté
      digitalWrite(motorPin, LOW);
      lcd.setCursor(12, 1);
      lcd.print("OFF"); //Vypsání na displej, zda je čerpadlo vypnuto
    }
    //Vypnutí napájecího napětí pro modul
    digitalWrite(vccPin, LOW);
    //Uložení aktuálního času do proměnné pro další kontrolu
    cas = millis();
  }
}
