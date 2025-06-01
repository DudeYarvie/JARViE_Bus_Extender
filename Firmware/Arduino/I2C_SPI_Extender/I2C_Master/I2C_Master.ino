//I2C_Master.ino
//Purpose:  Send communications from a controller to a peripheral over an I2C bus via the LTC43321
//Date:3/14/2025
//Written By: Jarvis Hill

#include <Wire.h>

/*GLOBALS*/
char trans_data_buf[20] = "JARViE";
unsigned int a = 0;

//LTC43321 CNTRL REGS
#define CONFIG      0x00
#define STATUS      0x01
#define EVENT       0x02
#define ALERT_EN    0x03
#define FAULT       0x04
#define SCRATCH     0x05
#define ADDR_TRANS  0x06
#define CTRL        0x07

#define DEVICE_ADDR 15
#define LTC4331_LOCAL_ADDR  0x3E
#define LTC4331_REMOTE_ADDR 0x3F

char msg_buf[20] = "";
uint8_t trans_addr;


// /*Disable I2C pull-ups*/
// void disable_i2c_pullups(){
//   int SDA = A4;
//   int SCL = A5;
//   pinMode(SDA,LOW);  
//   pinMode(SCL,LOW);
// }

/*Send I2C message*/
void query_LTC4331_cntrl_reg( uint8_t ADDR, uint8_t REG){
  byte receivedData = 0xFF;                                   //Init data byte
  Wire.beginTransmission(ADDR);                               //Begin I2C transaction
  delay(1);               
  Wire.write(REG);                                            //Select to write LTC4331 CONFIG REG
  delay(1);
  Wire.endTransmission(false);                                //Send repeated start bit (required)
  Wire.requestFrom(ADDR, 1);                                  //Resend LTC4331 CNTRL REG address (required)
  delay(1);
                    
  if (Wire.available()) {                                     //Read register contents
    receivedData = Wire.read();
    sprintf(msg_buf,"REG: %d %d", REG, receivedData);         //Contrstruct a character buffer with register contents
    Serial.println(msg_buf);                                  //Print register contents to a connected serial terminal
  }
  delay(50);
                      
}

void write_rmt_device(uint8_t ADDR, uint8_t REG, uint8_t DATA){
  Wire.beginTransmission(ADDR);         //ADDRESS LT4331 CNTRL INTERFACE
  delay(1);               
  Wire.write(REG);                      //Select CNTRL REG
  delay(1);
  Wire.write(DATA);                     //Write REG data
  delay(1);
  Wire.endTransmission(ADDR);           //Stop transmission
  delay(50);
  //Serial.println(a);
  //a = 0;                              //Clear status data
  //delay(50);                             
}

void write_LTC4331_cntrl_reg(uint8_t ADDR, uint8_t REG, uint8_t DATA){
  Wire.beginTransmission(ADDR);         //ADDRESS LT4331 CNTRL INTERFACE
  delay(1);               
  Wire.write(REG);                      //Select CNTRL REG
  delay(1);
  Wire.write(DATA);                     //Write REG data
  delay(1);
  Wire.endTransmission(ADDR);           //Stop transmission
  delay(50);

}

/*MAIN*/
void setup()
{
  Serial.begin(9600);                                         //Init serial 
  delay(1);                                                   //Setup delay
  Wire.begin();                                               //Init I2C
  Wire.setClock(100000);                                      //Set I2C SCL frequency
  delay(100); 
  write_LTC4331_cntrl_reg(LTC4331_LOCAL_ADDR, EVENT, 0x00);   //LTC4331 config: clear faults in EVENT REG 
  delay(1000);
}

void loop()
{
    /*Send data to I2C device*/
    for (int i = 0; i <strlen(trans_data_buf); i++)
    { 
      Serial.println(trans_data_buf[i]);                                 //Print to serial monitor for debugging
  
      Wire.beginTransmission(DEVICE_ADDR);                               //Start I2C communications with device
      delay(1);
      Wire.write(trans_data_buf[i]);                                     //Send data to peripheral device
      delay(1);
      Wire.endTransmission(DEVICE_ADDR);                                 //Stop I2C transmission
      delay(1000);
    
  }
  
  /*Check for communication and link faults*/
  delay(1000);
  query_LTC4331_cntrl_reg(LTC4331_LOCAL_ADDR, CONFIG);
  delay(50);
  query_LTC4331_cntrl_reg(LTC4331_LOCAL_ADDR, STATUS);
  delay(50);
  query_LTC4331_cntrl_reg(LTC4331_LOCAL_ADDR, EVENT);
  delay(50);
  query_LTC4331_cntrl_reg(LTC4331_LOCAL_ADDR, ALERT_EN);
  delay(50);
  query_LTC4331_cntrl_reg(LTC4331_LOCAL_ADDR, FAULT);
  delay(50);
  query_LTC4331_cntrl_reg(LTC4331_LOCAL_ADDR, ADDR_TRANS);
  delay(50);
  write_LTC4331_cntrl_reg(LTC4331_LOCAL_ADDR, EVENT, 0x00);

}


