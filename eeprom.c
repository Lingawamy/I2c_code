/*
External EEPROM 24C02 Test Program

FOSC = 12MHz                //Crystal Connected with the Board
CCLK = 60MHz                //FOSC X MSEL here MSEL = 5 hence Core is Running at 60MHz
PCLK = CCLK/4 = 15MHz
*/

#include <lpc214x.h>
#include "i2c.h"
#include "lcd.h"


/**************Function Prototypes************/
void EEPROM24C_Write();
unsigned char EEPROM24C_Read(unsigned char address);
/*********************************************/

int main()
{
	  unsigned int i;
    unsigned char msg1[] = "PRIYA\0";
	  unsigned char msg2[10];
    unsigned char read_eeprom;
    lcdinit();
    lcd_str("Writing...");
	  delay();
	  delay();
	  delay();
    EEPROM24C_Write();
	  I2C0_Write(0x00,0x28); 
    for (i=0; msg1[i]!='\0'; i++) 
          I2C0_Write(msg1[i],0x28);
    I2C0_Stop();
    cmdlcd(0xC0);
		lcd_str("Reading... ");
    EEPROM24C_Read(0x00);
	  for (i=0; i<9; i++) 
          msg2[i]=I2C0_Read();
	  I2C0_Stop();
//		datalcd(read_eeprom);
		
    
	 lcd_str(msg2);
    
	
    while(1);
}

/****************Function Definition**********/
void EEPROM24C_Write()
{
    I2C0_Init();
    I2C0_Start();   
    I2C0_Write(0xA0,0x18);   
//    I2C0_Write(address,0x28);   
//    I2C0_Write(data,0x28);
//    I2C0_Stop();
}
unsigned char EEPROM24C_Read(unsigned char address)
{
    unsigned char read;
    I2C0_Init();
    I2C0_Start();   
    I2C0_Write(0xA0,0x18);   
    I2C0_Write(address,0x28);
    I2C0_Stop();       
    I2C0_Start();   
    I2C0_Write(0xA1,0x40);   
//    read = I2C0_Read();
//    I2C0_Stop();
    return (read);
}
