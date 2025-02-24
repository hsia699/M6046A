// Header file to summarize all functions used within this program.
// Author: Jeff Zhong
// Date: 02/24/2025

# ifndef M6046_H
# define M6046_H

# include <stdint.h>
# include <8052.h>

typedef uint8_t uchar;
typedef uint16_t uint;

#define WR0 P3_0    // SPI Clock
#define WR1 P3_1    // SPI Data Input
#define CS   P3_2    // Chip Select
#define CD   P3_4    // Command/Data Select
#define RST  P3_5    // Reset
#define DATA_PORT P1

void Init_UC1538();
void delay_ms(int ms);
void write_cmd(uint8_t cmd);
void write_dat(uint8_t dat);
void Set_Page_Address(uint8_t page);
void Set_Column_Address(uint8_t column);

# endif
