#include <Wire.h> 				      // Library for I2C communication
#include <LiquidCrystal_I2C.h> 	// Library for LCD
#include <SPI.h>
#include <stdio.h>
#include <string.h>

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);
String kpa = " kPa    "; // 4 spaces to prevent overwrite
String RPMSpace = "      "; // 6 spaces to prevent overwrite
// JetCat engine RPM maxes out at 154000 RPM

// Tachometer Setup
unsigned long rpmtime;
float rpmfloat;
unsigned int rpm;
bool tooslow = 1;

void setup() {
  // Initialize the display
  lcd.init();
  lcd.backlight();

  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1B |= (1 << CS12); //Prescaler 256
  TIMSK1 |= (1 << TOIE1); //enable timer overflow
  pinMode(2, INPUT);
  attachInterrupt(0, RPM, FALLING);
}

ISR(TIMER1_OVF_vect) {
 tooslow = 1;
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

  // RPM Stat and Print

  rpmfloat = 120 / (rpmtime/ 31250.00);
  rpm = round(rpmfloat);
  String sRPM = String(rpm);
  sRPM = sRPM + RPMSpace;

  lcd.setCursor(0, 2);
  lcd.print("RPM");

  lcd.setCursor(1, 3);
  lcd.print(sRPM);

  delay(1000);

}

void RPM () {
  rpmtime = TCNT1;
  TCNT1 = 0;
  tooslow = 0;
}
