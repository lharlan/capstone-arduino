#include <stdio.h>
#include <string.h>
#include <Wire.h> 				      // Library for I2C communication
#include <LiquidCrystal_I2C.h> 	// Library for LCD
#include <HX711.h> 				      // load cell library

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);

String lbs = " lbs      ";
float maxT = -1.00;
float maxRT = -1.00;

// HX711 wiring
  // Thrust scale
const int LOADCELL_TDT_PIN = 6;
const int LOADCELL_TSCK_PIN = 7;

  // Reverse thrust scale
const int LOADCELL_RTDT_PIN = 4;
const int LOADCELL_RTSCK_PIN = 3;

HX711 scaleThrust;
HX711 scaleRThrust;

float thrustVal;
float rthrustVal;

void setup() {
  
  Serial.begin(9600);
  // Initialize the display
  lcd.init();
  lcd.backlight();

  // Initialize the Load Cells
  scaleThrust.begin(LOADCELL_TDT_PIN, LOADCELL_TSCK_PIN);
  scaleRThrust.begin(LOADCELL_RTDT_PIN, LOADCELL_RTSCK_PIN);

  scaleThrust.tare(); //Reset the scale to 0
  scaleRThrust.tare(); //Reset the scale to 0

  // Print Static Wording

  lcd.setCursor(0, 0);
  lcd.print("Thrust");

  lcd.setCursor(16, 0);
  lcd.print("Max");

  lcd.setCursor(0, 2);
  lcd.print("Reverse Thrust");

  lcd.setCursor(16, 2);
  lcd.print("Max");

}

void loop() {

  // Set the calibration values
  scaleThrust.set_scale(46000);    // 20kg scale
  scaleRThrust.set_scale(180000);  // 5 kg scale
  
  thrustVal = scaleThrust.get_units();
  rthrustVal = scaleRThrust.get_units();

  String sthrustVal = String(thrustVal);
  String srthrustVal = String(rthrustVal);

  // Finding Max Values

  if (thrustVal > maxT) {
	  maxT = thrustVal; }
  else {
    maxT = maxT;}

  if (rthrustVal > maxRT) {
	  maxRT = rthrustVal; }
  else {
	  maxRT = maxRT; }
  
  String smaxT = String(maxT);
  String smaxRT = String(maxRT);


  // Add "lbs" to the end of the thrust

  sthrustVal = sthrustVal + lbs;
  srthrustVal = srthrustVal + lbs;

  // Normal Print

  lcd.setCursor(3, 1);
  lcd.print(sthrustVal);

  lcd.setCursor(15, 1);
  lcd.print(smaxT);

  // Reverse Print

  lcd.setCursor(3, 3);
  lcd.print(srthrustVal);

  lcd.setCursor(15, 3);
  lcd.print(smaxRT);

  delay(2000);

}
