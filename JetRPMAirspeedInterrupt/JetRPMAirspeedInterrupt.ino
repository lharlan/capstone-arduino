#include <Wire.h> 				      // Library for I2C communication
#include <LiquidCrystal_I2C.h> 	// Library for LCD
#include <SPI.h>
#include <stdio.h>
#include <string.h>

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);

String kpa = " kPa    "; // 4 spaces to prevent overwrite
String RPMSpace = "      "; // 6 spaces to prevent overwrite
// JetCat engine RPM maxes out at 154000 RPM

float value=0;
float rev=0;
int rpm;
int oldtime=0;
int newtime;

void isr() {
rev++;
}

void setup() {

  lcd.init ();
  lcd. backlight ();

  // Attaching the interrupt
  attachInterrupt(digitalPinToInterrupt(2),isr,RISING);
}

void loop() {

  delay(1000);

  // Airspeed Logic
  int kPaValue = analogRead(A0);
  String skPaValue = String(kPaValue);
  skPaValue = skPaValue + kpa;

  lcd.setCursor(0, 0);
  lcd.print("Pressure");

  lcd.setCursor(1, 1);
  lcd.print(skPaValue);  

  // RPM Logic
  detachInterrupt(0);         //detaches the interrupt
  newtime=millis()-oldtime;   //finds the time 
  int wings= 23;               // no of wings of rotating object, for disc object use 1 with white tape on one side
  int RPMnew = rev/wings;
  rpm=(RPMnew/newtime)*60000; //calculates rpm
  oldtime=millis();           //saves the current time
  rev=0;

  String sRPM = String(rpm);
  sRPM = sRPM + RPMSpace;

  lcd.setCursor(0, 2);
  lcd.print("RPM");

  lcd.setCursor(1, 3);
  lcd.print(sRPM);

  attachInterrupt(digitalPinToInterrupt(2),isr,RISING);
}
