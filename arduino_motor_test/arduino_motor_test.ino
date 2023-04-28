// Wire Master Writer
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Writes data to an I2C/TWI slave device
// Refer to the "Wire Slave Receiver" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>

void setup() {
  Wire.begin(); // join I2C bus (timeCount optional for master)
  Wire.setWireTimeout();
  Wire.setClock(100000);
  Serial.begin(9600);  // start serial for output
  Serial.print("hello!\n");
}

byte x = 150;
byte timeCount =11;

byte addr = 0x29;

void loop() {
  /*Wire.requestFrom(0x29, 5);    // request 6 bytes from slave device #8
  Serial.print("values: ");
  while (Wire.available()) { // slave may send less than requested
    char c = Wire.read(); // receive a byte as character
    Serial.print(c,HEX);         // print the character
    Serial.print(" ");
  }
  Serial.print("\n");*/
  Wire.beginTransmission(addr); // transmit to device #8
  //Wire.write(byte(0xEE));       // sends five bytes
  Wire.write(x);              // sends one byte
  Wire.endTransmission();    // stop transmitting
  x++;
  timeCount+=1;
  if(timeCount>=10){
    timeCount = 0;
    
    Serial.write("set speed to: ");
    Serial.print(x&0xFF,DEC);
    Serial.print("\n");
    Wire.requestFrom(addr, 5);    // request 6 bytes from slave device #8
    Serial.print("values: ");
    int curVal = 0;
    while (Wire.available()) { // slave may send less than requested
      char c = Wire.read(); // receive a byte as character
      if (curVal == 0){
        Serial.print("current:");
      }
      if (curVal == 1){
        Serial.print("state:");
      }
      if (curVal == 2){
        Serial.print("temp:");
      }
      if (curVal == 3){
        Serial.print("rpm:");
      }
      if (curVal == 4){
        Serial.print("voltage:");
      }
      Serial.print(c&0xFF,DEC);         // print the character
      Serial.print(" ");
      curVal++;
    }
    Serial.print("\n");
  }

  
  delay(100);
}
