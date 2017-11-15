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


namespace adrone
{
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

        /**
         * Sets network name and password to ap mode
         * 
         * @param ssid Network name
         * @param password Network password
         */
    	void ap_access(const char *ssid = "", const char *password = "");

        /**
         * Authentication Mode
         * 
         * @param auth AUTH_OPEN, AUTH_WEP, AUTH_WPA_PSK, AUTH_WPA2_PSK, AUTH_WPA_WPA2_PSK, AUTH_MAX
         */
    	void ap_auth(const AUTH_MODE &auth);

        /**
         * Network configuration
         * 
         * @param ip Network ip
         * @param gatway Network gateway
         * @param netmask Network mask
         */
    	void ap_network(const char *ip, const char *gatway, const char *netmask);

        /**
         * Hide wifi name
         * 
         * @param hide A boolean variable
         */
        void ap_hidden(const bool &hide);

        /**
         * Wifi channel selection
         * http://www.espressif.com/sites/default/files/esp8266_wi-fi_channel_selection_guidelines.pdf
         * 
         * @param channel Number from 1 to 14
         */
        void ap_channel(const uint8_t &channel);

        /**
         * Defines the total number of connections that the wifi in ap mode can have
         * 
         * @param max Number of connections between 1 and 255
         */
        void ap_connection(const uint8_t &max);

        /**
         * Periodically sent by the access point. It has the function of informing the clients that the network is present.
         * 
         * @param millis Time in milliseconds
         */
        void ap_beacon(const uint16_t &millis);

        /**
         * Set initial ip of the DHCP service
         * 
         * @param start Initial dhcp service ip
         * @param max Number of connections between 1 and 255
         */
        void ap_dhcp(const char *start, const uint8_t &max);

        /**
         * SSID & Password for STATION Mode
         */
        void station_access(const char *ssid = "", const char *password = "");

        /**
         * Sets the B/G/N operating mode of the wifi
         * 
         * @param mode PHY_MODE_11B, PHY_MODE_11G, PHY_MODE_11N
         */
        void phy_mode(const sdk_phy_mode &mode);

        /**
         * Starts the wifi operating in station, AP or AP + Station mode
         * 
         * @param opmode NULL_MODE, STATION_MODE, SOFTAP_MODE, STATIONAP_MODE, MAX_MODE
         */
    	void init(const uint8_t &opmode);

    private:
    	struct
        { 
            uint8_t dhcp_max;
            ip_addr_t dhcp_ip;
            struct ip_info addr;
            struct sdk_softap_config config;
        } _ap;

    	struct sdk_station_config _station;
	};

}
    

#endif