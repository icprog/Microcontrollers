#ifndef ADRONE_OTA_H
#define ADRONE_OTA_H

#include <ota-tftp.h>   // ota_tftp_init_server
#include <rboot-api.h>  // rboot_get_config


namespace adrone
{
	class ota
	{
	public:
		/**
         * Constructor sets the initial settings. Copy and move have been disabled
         * 
         * @param other ota object
         */
		ota();
	    ota(const ota &other)  = delete;
    	ota(const ota &&other) = delete; //only -std=c++11

       /**
         * Disable copy and move assignment operator
         * 
         * @param other ota object
         */
    	ota& operator=(const ota &other)  = delete;
    	ota& operator=(const ota &&other) = delete; //only -std=c++11

        /**
         * Start tftp server on port 69
         */
    	void init();
	};
}

#endif