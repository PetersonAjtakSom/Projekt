// Půdní vlhkoměr

#define analogPin A0
#define digitalPin 3
#define vccPin 4
#define cerpadloPin 6 
unsigned long cas = 0;

void setup() {
  Serial.begin(9600);
  pinMode(analogPin, INPUT);
  pinMode(digitalPin, INPUT);
  pinMode(vccPin, OUTPUT);
  pinMode(cerpadloPin, OUTPUT);
  digitalWrite(vccPin, LOW);
}

void loop() {
  if (millis() - cas > 3000) {
    digitalWrite(vccPin, HIGH);
    delay(100);
    int analog = analogRead(analogPin);
    bool digit = digitalRead(digitalPin);
    Serial.print("Analogovy vstup: ");
    Serial.print(analog);
    if (digit == LOW) {
      Serial.print(" | Detekovano prekroceni hranice!");
    }
    Serial.println();
    digitalWrite(vccPin, LOW);
    cas = millis();

    if (analog <= 800){
      digitalWrite(cerpadloPin, HIGH);
    }
    else {
        digitalWrite(cerpadloPin, LOW);
    }
    
  }
}
