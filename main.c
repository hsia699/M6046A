#include "TS-GG160160027W-Initialize.h"

void main() {
    uint8_t page;
    uint8_t column;

    Init_UC1538();

    while (1) {
        for (page = 0; page < 20; page++) {
		    Set_Page_Address(page);
			Set_Column_Address(0);
            write_cmd(0x01);
			for (column = 0; column <= 160; column++) {
			    if ((page + (column / 8)) % 2 == 0) {
                    write_dat(0xFF);  // All 8 pixels ON (black)
                } else {
                    write_dat(0x00);  // All 8 pixels OFF (white)
                }
			}
		}
		delay_ms(100);
    }
}
