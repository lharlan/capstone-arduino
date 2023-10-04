#include <Wire.h> 				      // Library for I2C communication
#include <LiquidCrystal_I2C.h> 	// Library for LCD
#include <SPI.h>

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);

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
  int sensorValue = analogRead(A0);

  lcd.setCursor(0, 0);
  lcd.print("Pressure");

  lcd.setCursor(3, 1);
  lcd.print(sensorValue);

  rpmfloat = 120 / (rpmtime/ 31250.00);
  rpm = round(rpmfloat);



  delay(1000);

}

void RPM () {
 rpmtime = TCNT1;
 TCNT1 = 0;
 tooslow = 0;
}
