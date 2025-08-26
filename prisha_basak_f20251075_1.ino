#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// LCD setup
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Servo motor
Servo gate;

// Pin definitions
#define pir 2
#define greenled 4
#define redled 5
#define servopin 9

void setup() {
  // Serial monitor
  Serial.begin(9600);

  // LCD
  lcd.init();
  lcd.backlight();

  // Servo
  gate.attach(servopin);
  gate.write(0);  // Gate open initially

  // PIR and LEDs
  pinMode(pir, INPUT);
  pinMode(greenled, OUTPUT);
  pinMode(redled, OUTPUT);

  Serial.println("Smart Parking System Initialized");
}

void loop() {
  int spot = digitalRead(pir);

  if (spot == HIGH) {  
    // Spot occupied
    digitalWrite(redled, HIGH);
    digitalWrite(greenled, LOW);

    Serial.println("Spot: OCCUPIED");
    lcd.setCursor(0, 0);
    lcd.print("Spot: OCCUPIED ");

    // Close gate
    gate.write(90);
  } else {  
    // Spot vacant
    digitalWrite(redled, LOW);
    digitalWrite(greenled, HIGH);

    Serial.println("Spot: VACANT");
    lcd.setCursor(0, 0);
    lcd.print("Spot: VACANT   ");

    // Open gate
    gate.write(0);
  }

  delay(500);
}
