#include <LiquidCrystal.h>

const int rs = 8, en = 9, d4 = 10, d5 = 11, d6 = 12, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int ir1 = A0;
int ir2 = A1;
int ir3 = A4;
int rly1 = 2;
boolean charging = false;

void setup() {
  lcd.begin(16, 2);
  pinMode(rly1, OUTPUT);
  digitalWrite(rly1, LOW); // Ensure relay is initially off
}

// Function to convert any time duration to milliseconds
unsigned long convertToMilliseconds(int time, char unit) {
  switch(unit) {
    case 's': // seconds
      return time * 1000UL;
    case 'm': // minutes
      return time * 60UL * 1000UL;
    case 'h': // hours
      return time * 3600UL * 1000UL;
    default:
      return 0; // Invalid unit
  }
}

void loop() {
  int ob1 = digitalRead(ir1);
  int ob2 = digitalRead(ir2);
  int ob3 = digitalRead(ir3);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Insert the coin");
  lcd.setCursor(4, 1);
  lcd.print("1:");
  lcd.print(ob1);
  lcd.setCursor(8, 1);
  lcd.print("2:");
  lcd.print(ob2);
  lcd.setCursor(0, 2);
  lcd.print("3:");
  lcd.print(ob3);
  
  delay(500);
  
  if (!charging && (ob1 == LOW || ob2 == LOW || ob3 == LOW)) {
    charging = true;
    digitalWrite(rly1, HIGH); // Start charging
    
    // Set your desired charging duration here
    unsigned long charging_duration = convertToMilliseconds(3, 'm'); // 3 minutes
    
    delay(charging_duration); // Charging duration
    
    // Check sensor readings after charging
    int afterCharge_ob1 = digitalRead(ir1);
    int afterCharge_ob2 = digitalRead(ir2);
    int afterCharge_ob3 = digitalRead(ir3);
    
    if (afterCharge_ob1 == LOW || afterCharge_ob2 == LOW || afterCharge_ob3 == LOW) {
      // Coin still present, continue charging
      digitalWrite(rly1, LOW);
    } else {
      // Coin not present, stop charging
      charging = false;
      digitalWrite(rly1, LOW);
    }
  }
}