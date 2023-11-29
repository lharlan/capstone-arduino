#include <Wire.h> 				      // Library for I2C communication
#include <LiquidCrystal_I2C.h> 	// Library for LCD
#include <SPI.h>
#include <stdio.h>
#include <string.h>

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);

String kpa = " kPa    "; // 4 spaces to prevent overwrite
String RPMSpace = "       "; // 7 spaces to prevent overwrite
// JetCat engine RPM maxes out at 154000 RPM

// Tachometer Setup
int rpm = 0;
unsigned long millisBefore;
volatile int objects;


void setup() {
  // Initialize the display
  lcd.init();
  lcd.backlight();

  attachInterrupt(digitalPinToInterrupt(2), count, FALLING);
  pinMode(2, INPUT);
}

void loop() {
  
  // Read Airspeed value and Print
  int kPaValue = analogRead(A0);
  String skPaValue = String(kPaValue);
  skPaValue = skPaValue + kpa;

  lcd.setCursor(0, 0);
  lcd.print("Pressure");

  lcd.setCursor(1, 1);
  lcd.print(skPaValue);

  if (millis() - millisBefore > 1000) {
    rpm = (objects / 3.0)*60;
    objects = 0;
    millisBefore = millis();
  }

  String sRPM = String(rpm);
  sRPM = sRPM + RPMSpace;

  delay(100);

  lcd.setCursor(0, 2);
  lcd.print("RPM");

  lcd.setCursor(1, 3);
  lcd.print(sRPM);


  delay(1000);

}

void count() {
  objects++;
}


