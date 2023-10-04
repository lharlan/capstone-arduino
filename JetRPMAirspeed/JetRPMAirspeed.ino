#include <Wire.h> 				      // Library for I2C communication
#include <LiquidCrystal_I2C.h> 	// Library for LCD
#include <SPI.h>
#include <stdio.h>
#include <string.h>

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);
String kpa = " kPa";

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
 TCCR1B |= (1 << CS12);   //Prescaler 256
 TIMSK1 |= (1 << TOIE1);  //enable timer overflow
 pinMode(2, INPUT);
 attachInterrupt(0, RPM, FALLING);
}

ISR(TIMER1_OVF_vect) {
 tooslow = 1;
}

void loop() {
  
  // Read Airspeed value
  int kPaValue = analogRead(A0);
  String skPaValue = String(kPaValue);
  skPaValue = skPaValue + kpa;

  lcd.setCursor(0, 0);
  lcd.print("Pressure");

  lcd.setCursor(3, 1);
  lcd.print(skPaValue);

  rpmfloat = 120 / (rpmtime/ 31250.00);
  rpm = round(rpmfloat);

  lcd.setCursor(0, 2);
  lcd.print("RPM");

  lcd.setCursor(3, 4);
  lcd.print(rpm);


  delay(1000);

}

void RPM () {
 rpmtime = TCNT1;
 TCNT1 = 0;
 tooslow = 0;
}
