#ifndef ADRONE_WIFI_H
#define ADRONE_WIFI_H

#include <stdlib.h>  // atoi
#include <stdint.h>  // uint8_t; uint16_t
#include <string.h>  // strcpy
#include <stdbool.h> // bool

// #include "espressif/esp_common.h"
#include <espressif/esp_wifi.h>
#include <espressif/esp_softap.h>
#include <espressif/esp_sta.h>

#include <lwip/ip.h>
#include <dhcpserver.h>

#define AP_SSID "andre"
#define AP_PSK "andrefelipe"

class wifi
{
public:
    /**
     * Constructor sets the initial settings. Copy and move have been disabled
     * 
     * @param other wifi object
     */
	wifi();
    wifi(const wifi &other)  = delete;
	wifi(const wifi &&other) = delete;

   /**
     * Disable copy and move assignment operator
     * 
     * @param other wifi object
     */
	wifi& operator=(const wifi &other)  = delete;
	wifi& operator=(const wifi &&other) = delete;
    
    void init();    
private:
    struct sdk_softap_config ap_config;
	struct
    { 
        uint8_t dhcp_max;
        ip_addr_t dhcp_ip;
        struct ip_info addr;
    } _ap;

	struct sdk_station_config _station;
};

    

#endif