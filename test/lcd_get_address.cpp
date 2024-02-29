#include <Wire.h> // This library includes I2C communication functions 
#include <Arduino.h> // This library includes I2C communication functions 

 

void setup() {

Wire.begin();

Serial.begin(9600);

Serial.println("Scanning for I2C devices");

}

 

void loop() {

byte error_i2c, address_i2c;

int I2C_Devices;

Serial.println("Scanning started");

I2C_Devices = 0;

for(address_i2c = 1; address_i2c < 127; address_i2c++ )

{

Wire.beginTransmission(address_i2c);

error_i2c = Wire.endTransmission();

if (error_i2c == 0) {

Serial.print("I2C device found at address_i2c 0x");

if (address_i2c<16) 

{

Serial.print("0");

}

Serial.println(address_i2c,HEX);

I2C_Devices++;

}

else if (error_i2c==4) 

{

Serial.print("Unknow error_i2c at address_i2c 0x");

if (address_i2c<16) 

{

Serial.print("0");

}

Serial.println(address_i2c,HEX);

} 

}

if (I2C_Devices == 0) 

{

Serial.println("No I2C device connected \n");

}

else {

Serial.println("done I2C device searching\n");

}

delay(2000); 

}