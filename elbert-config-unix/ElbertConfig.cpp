/*

Command-Line Elbert Configuration loader, for a substitute for the wx-based Windows ElbertConfig tool.
(see http://numato.com/elbert-spartan-3a-fpga-development-board)
 
Thanks to the Numato Guys @ numato.com for providing the original source!
 
Serial Programming has been completely rewritten, but the Antero-Stuff is pretty untouched (except for some
none-critical parts that dealt with the GUI handling).

This is no professional software, but rather a quick hack. But it runs smoothly und Ubuntu and OSX, and God knows where else ;-)
 
PL, 2014-03-17
 
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Antero.hpp"
#include "AnteroConfig.hpp"

#define FILESIZE 0xD588

static void check(int retcode) {
    if (retcode) {
        printf("FAILED with code %d\n", retcode);
        exit(1);
    }
}

int main (int argc, char **argv) {
	
    unsigned char configBuff[FILESIZE];
    unsigned char readBuff[FILESIZE];
	
	if (argc != 3) {
		printf("usage: %s <program file> <serial port>; e.g. %s myModule.bin /dev/tty.usbmodemf131\n", argv[0], argv[0]);
		exit(1);
	}
	
	Antero a;
	
    setbuf(stdout, NULL);  // unbuffering stdout for visual feedback on long operation

    printf("loading file... ");
    check(a.LoadFile(argv[1], configBuff, FILESIZE));
    printf("ok\n");
    
    printf("opening port... ");
    check(a.OpenPort(argv[2]));
    printf("ok\n");
    
    printf("configuring\n");
    check(a.SPISetIODirection(1, SPARTAN_3A_CONFIG_IO_PIN_PROGB, IO_DIRECTION_OUT));
    check(a.SPISetIOValue(1, SPARTAN_3A_CONFIG_IO_PIN_PROGB, 0));
    check(a.SPIOpen(1));
    check(a.ConfigureBoard(1, configBuff, FILESIZE));
    
    printf("verifying...\n");
    check(a.ReadFlashMemory(1, readBuff, 0, FILESIZE));
    printf("verification %s.\n", memcmp(configBuff, readBuff, FILESIZE) ? "FAILED" : "succeeded");

    printf("rebooting...\n");
    check(a.SPISetIODirection(1, SPARTAN_3A_CONFIG_IO_PIN_PROGB, IO_DIRECTION_OUT));
    check(a.SPISetIOValue(1, SPARTAN_3A_CONFIG_IO_PIN_PROGB, 1));
    printf("ready!\n");

}
