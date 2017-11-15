#include "ota.h"


adrone::ota::ota()
{ }


void adrone::ota::init()
{
	// bootloader configurations
    rboot_config conf = rboot_get_config();
    printf("EPS8266 Basic OTA.\n");
    printf("Currently running on flash slot %d / %d.\n\n", (conf.current_rom + 1), conf.count);

    printf("Image addresses in flash:\n");
    for(int i = 1; i <= conf.count; i++)
    {
        printf("%c%d: offset 0x%08x\r\n", (i-1) == conf.current_rom ? '*':' ', i, conf.roms[i-1]);
    }

    printf("\nStarting TFTP server...\n");
    ota_tftp_init_server(69);
}