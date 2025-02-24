/**
*  @file       m6046.c
*  @brief    LCD driver for M6046A(160x160) using 8080 parallel interface.
*
*  @details Implents low-level display functions:
*                          - LCD initialization
*                          - Command and data writing
*                          - Address setting(page & column)
*
*  @author   Jeff Zhong
*  @date      02/24/2025 
*
*  @hardware
*                          - MCU: 8051-based
*                          - LCD: M6046A(UC1638 driver)
*                          - Interface: 8080 Parallel£¨D0-D7£¬ WR0, CS, CD, RST£©
*
*  @usage
*                          1. Call Init_UC1538() to initialize.
*                          2. Use write_cmd() for command, use write_dat() for data.
*                          3. Set display address with Set_Page_Address() and Set_Column_Address().
*                          4. Display logic.
*/

# include "m6046.h"

void delay_ms(int ms) {
    int i, j;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < 125; j++) { 
        }
    }
}

void Init_UC1538()
{	
    RST=1;		
    delay_ms(5);
    RST=0;
    delay_ms(50);
    RST=1;
    delay_ms(200);
	
    write_cmd(0x30);
    delay_ms(10);

    write_cmd(0xE1);      //system reset
    write_cmd(0xE2); 
    delay_ms(10); 
    write_cmd(0xEb);	  //Set LCD Bias Ratio   
    write_cmd(0x2D);	  //Set Pump Control 
    write_cmd(0x81);
    write_dat(171);	  //Set VBias Potentiometer           
    write_cmd(0x24);	  //Set Temperature  Compensation
    write_cmd(0x40);      //set scroll line LSB
    write_cmd(0x50);      //Set Scroll Line MSB    
	
    write_cmd(0x84);	  //Set Partial Display Control   
    write_cmd(0x86);	  //Set Com Scan Function
    write_cmd(0x89);	  //Set RAM Address Control     
    write_cmd(0x95); 	  //Set Display mode
    write_cmd(0xA2);	  //Set Line Rate         
    write_cmd(0xA4);	  //Set All Pixels On   
    write_cmd(0xA6);	  //Set Inverse Display  
    write_cmd(0xC4);	  //Set LCD Mapping Control      

    write_cmd(0xC8);	  //N-LINE
    write_dat(0x20);	  //Set N-Line Inverse    
	
    write_cmd(0xF1);
    write_dat(159);	  //Set Com End 
	
    write_cmd(0x60);      //set page address  LSB
    write_cmd(0x70);	  //Set page Address  MSB
	
    write_cmd(0xD4);

    write_cmd(0x04);
    write_dat(0);         //Set Column Address     
	
    write_cmd(0xC9);
    write_dat(0xAD);      //Set Display Enable 
    delay_ms(10);
}

// Send command to the LCD.
void write_cmd(uint8_t cmd) {
    CS = 0;
    CD = 0;          // Send command.
    DATA_PORT = cmd;
    WR0 = 0;          // WR0 LOW to HIGH.
	delay_ms(10);
    WR0 = 1;
    CS = 1;
}

// Send display content data to the LCD.
void write_dat(uint8_t dat) {
    CS = 0;
    CD = 1;           // Data mode
    DATA_PORT = dat;
    WR0 = 0;          // WR0 LOW to HIGH.
	delay_ms(10);
    WR0 = 1;
    CS = 1;  
}

void Set_Page_Address(uint8_t page) {
    // Page address setting command.
    write_cmd(0x60 | (page & 0x0F));
	
	write_cmd(0x70 | ((page >> 4) & 0x03));
}

void Set_Column_Address(uint8_t column) {
    // Column addres setting command.
    write_cmd(0x04);
	write_dat(column & 0xFF);
}
