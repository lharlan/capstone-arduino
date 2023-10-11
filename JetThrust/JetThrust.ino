#include <stdio.h>
#include <string.h>
#include <Wire.h> 				      // Library for I2C communication
#include <LiquidCrystal_I2C.h> 	// Library for LCD
#include <HX711.h> 				      // load cell library

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);

String kg = " kg      ";

// HX711 wiring
  // Thrust scale
const int LOADCELL_TDT_PIN = 6;
const int LOADCELL_TSCK_PIN = 7;

  // Reverse thrust scale
const int LOADCELL_RTDT_PIN = 4;
const int LOADCELL_RTSCK_PIN = 3;

HX711 scaleThrust;
HX711 scaleRThrust;

int thrustVal;
int rthrustVal;

void setup() {
  
  Serial.begin(57600);
  // Initialize the display
  lcd.init();
  lcd.backlight();

  // Initialize the Load Cells
  scaleThrust.begin(LOADCELL_TDT_PIN, LOADCELL_TSCK_PIN);
  scaleRThrust.begin(LOADCELL_RTDT_PIN, LOADCELL_RTSCK_PIN);

  // Set the calibration values and reset the scale to zero
  scaleThrust.set_scale(-475);
  scaleRThrust.set_scale(-475);
  scaleThrust.tare();

}

void loop() {
  
  thrustVal = scaleThrust.read();
  rthrustVal = scaleRThrust.read();

  String sthrustVal = String(thrustVal);
  String srthrustVal = String(rthrustVal);

  sthrustVal = sthrustVal + kg;
  srthrustVal = srthrustVal + kg;

  lcd.setCursor(0, 0);
  lcd.print("Normal Thrust");

  lcd.setCursor(3, 1);
  lcd.print(sthrustVal);

  lcd.setCursor(0, 2);
  lcd.print("Reverse Thrust");

  lcd.setCursor(3, 3);
  lcd.print(srthrustVal);

  delay(2000);

}
