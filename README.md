# EE 401 Capstone Project, Thrust Reverser for Model Jet Engine
This is the arduino code and circuit layout for the JetCat P100 RX engine measurement system.

There are two arduinos that are used to monitor the jet engine, the Thrust Arduino, and the RPM/Pressure Arduino.

In order to set this up on your system either git clone this repo, or download the zip file and move both the JetThrust and JetRPMPressure folders to your Arduino folder.
(Arduino folder can be found under `~/Aruino/` if you are on a Linux based system or `C:\Users\youruser\Documents\Arduino` once you've installed the Arduino IDE.)

# Arduino IDE Setup
First is to download and install the ![Arduino IDE](https://www.arduino.cc/en/software) (Ver 2.2.1 or later).
Next we need to install the needed libraries. Go to Sketch > Include Library > Manage Libraries
![AddLibrary](https://github.com/lharlan/capstone-arduino/assets/75159044/be6f3403-4bb0-4dc2-901d-68982d43cc70)

Then we want to search and add the following libraries:
- LiquidCrystal I2C
- HX711 Arduino Library


You'll know if they've been sucessfully added when they look like this:
![LibrarySelection](https://github.com/lharlan/capstone-arduino/assets/75159044/c62a0c7f-9327-48bc-80e9-71b182b4eae2)


Now the required libraries are installed

# Thrust Measurement Arduino
![Screenshot_80](https://github.com/lharlan/capstone-arduino/assets/75159044/893fe27c-b5fb-4aea-a239-a8ecf2bd7d20)

