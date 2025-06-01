//The Master will tell the slave to turn on and off an LED
//Date:10/09/2022
//Written By: Jarvis Hill

#include <Wire.h>

//GLOBALS
char buf[20] = "JARViE";

void disable_i2c_pullups();


void setup()
{
  Serial.begin(9600);
  delay(1);
  Wire.begin();
  delay(1);
  //disable_i2c_pullups();
}

void loop()
{
 
  for (int i = 0; i <strlen(buf); i++)
  { 
    Serial.println(buf[i]);                                 //Print to serial monitor for debugging
  
    Wire.beginTransmission(15);
    delay(1);
    Wire.write(buf[i]);
    delay(1);
    Wire.endTransmission(15);
    //Serial.println("MASTER MESSAGE: Data Sent to slave.");  //Debugging
    delay(1000);
  }

}
