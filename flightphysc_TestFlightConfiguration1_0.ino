/*
  FlightPhysc_TestFlightConfiguration1_0

  Flight Software for Glowstone GLST-LVI Launch Vehicle.

  modified 20 April 2022
  by sLab Aerospace

  This code is in the public domain under Creative Commons lisence.

  https://slabaerospace.co/avionics/software/flightphysc1_0
*/

// include libraries
#include <SPI.h>
#include <SD.h>
#include <SFE_BMP180.h>
#include <Wire.h>
#include "I2Cdev.h"
#include "MPU6050.h"

File flightRecorder;
SFE_BMP180 barometer;
MPU6050 mpu;


// define variables
#define ALTITUDE 1655.0 

int16_t ax, ay, az;
int16_t gx, gy, gz;
int valx , valy , valz;
int valgx , valgy , valgz;

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);

  // flight recorder memory initialization
  Serial.println("Initializing Flight recorder memory.");

  if (!SD.begin(4)) {
    Serial.println("Flight recorder memory Initialization failed.");
    while (1);
  }
  Serial.println("Flight recorder memory Initialized.");

  delay(1000);

  // barometer initialization
  Serial.println("Initializing Barometer.");
  if (barometer.begin())
    Serial.println("Barometer Initialized.");
  else
  {
    Serial.println("Barometer Initialization failed.");
    while(1); 
  }

  // mpu initialization
  Serial.println("Initializing MPU");
  mpu.initialize();
  Serial.println(mpu.testConnection() ? "Connected" : "Connection failed");

	delay(100);

  // open the flight recorder memory. 
  flightRecorder = SD.open("flight.txt", FILE_WRITE);

  // write flight recorder memory header.
  if (flightRecorder) {
    Serial.println("writing flight recorder memory header");

    flightRecorder.println("FlightPhysc 1.0_TestFlightConfiguration - UTF-8");
    flightRecorder.println("Glowstone Flight Test 1 Flight Recorder");

    flightRecorder.print(millis());
    flightRecorder.println(" R (T+,PALT,TEMP,APRS,SPRS,CALT,AXX,AXY,AXZ,ACX,ACY,ACZ)");
    // close the flight recorder memory.
    flightRecorder.close();
    

  } else {
    // print an error if flight recorder memory failed:
    Serial.println("unable to write on flight recorder memory");
  }

  // re-open the file for reading:
  flightRecorder = SD.open("flight.txt");
  if (flightRecorder) {
    Serial.println("flight.txt:");

    // read from the file until there's nothing else in it:
    while (flightRecorder.available()) {
      Serial.write(flightRecorder.read());
    }
    // close the file:
    flightRecorder.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening flight.txt");
  }
}

void loop() {
  flightRecorder = SD.open("flight.txt", FILE_WRITE);
  digitalWrite(LED_BUILTIN, HIGH);
  if (flightRecorder) {

  char status;
  double T,P,p0,a;
  
  Serial.println();
  Serial.print("provided altitude: ");
  Serial.print(ALTITUDE,0);
  Serial.println(" meters");

  flightRecorder.print(millis());
  flightRecorder.print(",");
  flightRecorder.print(ALTITUDE,0);
  flightRecorder.print(",");
  

  status = barometer.startTemperature();
  if (status != 0)
  {

    delay(status);

    status = barometer.getTemperature(T);
    if (status != 0)
    {

      Serial.print("temperature: ");
      Serial.print(T,2);
      Serial.println(" degC");

      flightRecorder.print(T,2);
      flightRecorder.print(",");
      
      status = barometer.startPressure(3);
      if (status != 0)
      {

        delay(status);

        status = barometer.getPressure(P,T);
        if (status != 0)
        {

          Serial.print("absolute pressure: ");
          Serial.print(P,2);
          Serial.println(" millibar");

          flightRecorder.print(P,2);
          flightRecorder.print(",");

          p0 = barometer.sealevel(P,ALTITUDE); 
          Serial.print("relative (sea-level) pressure: ");
          Serial.print(p0,2);
          Serial.println(" millibar, ");

          flightRecorder.print(p0,2);
          flightRecorder.print(",");

          a = barometer.altitude(P,p0);
          Serial.print("computed altitude: ");
          Serial.print(a,0);
          Serial.println(" meters");

          flightRecorder.print(a,0);
          flightRecorder.print(",");
          

        }
        else Serial.println("error retrieving pressure measurement\n");
      }
      else Serial.println("error starting pressure measurement\n");
    }
    else Serial.println("error retrieving temperature measurement\n");
  }
  else Serial.println("error starting temperature measurement\n");

  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  valx = map(ax, -17000, 17000, 0, 179);
  valy = map(ay, -17000, 17000, 0, 179);
  valz = map(az, -17000, 17000, 0, 179);
  valgx = map(gx, -17000, 17000, -7, 7);
  valgy = map(gy, -17000, 17000, -7, 7);
  valgz = map(gz, -17000, 17000, -7, 7);

  Serial.print("axisX: ") ; 
  Serial.print(valx) ; 
  flightRecorder.print(valx);
  flightRecorder.print(",");

  Serial.print(" axisY: ") ; 
  Serial.print(valy) ; 
  flightRecorder.print(valy);
  flightRecorder.print(",");

  Serial.print(" axisZ: ") ; 
  Serial.print(valz) ;
  flightRecorder.print(valz);
  flightRecorder.print(",");

  Serial.print(" accX: ") ; 
  Serial.print(valgx) ; 
  flightRecorder.print(valgx);
  flightRecorder.print(",");

  Serial.print(" accX: ") ; 
  Serial.print(valgy) ; 
  flightRecorder.print(valgy);
  flightRecorder.print(",");

  Serial.print(" accX: ") ; 
  Serial.println(valgz) ; 
  flightRecorder.println(valgz);

  flightRecorder.close();

  delay(325);
  digitalWrite(LED_BUILTIN, LOW);

  } else {
    // print an error if flight recorder memory failed:
    Serial.println("unable to write on flight recorder memory");
  }
}