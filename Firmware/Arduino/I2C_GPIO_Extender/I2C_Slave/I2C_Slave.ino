//This is for I2C Slave 
//The Master will tell the slave to turn on and off an LED
//Date:06/06/13
//Written By: Jarvis Hill

#include <Wire.h>

//Globals


//Prototypes
void blink_led();


void disable_i2c_pullups()
{
  int SDA = 20;
  int SCL = 21;
  pinMode(SDA,LOW);  
  pinMode(SCL,LOW);  

}


void blink_led()
{
  while(Wire.available())  
  {
    
    char message = Wire.read();
    
    PORTB ^= (1 << PINB5);
    delay(1000);
    Serial.println(message);
    
  }
}



void setup()
{
  Wire.begin(15);
  delay(1);
  Serial.begin(9600);
  delay(1);
  disable_i2c_pullups();
  DDRB |= (1 << DDB5);
  Wire.onReceive(blink_led);

}

void loop()
{
  //
  
  
}
