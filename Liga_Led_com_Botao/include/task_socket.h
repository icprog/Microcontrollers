#ifndef ADRONE_SOCKET_H
#define ADRONE_SOCKET_H

#include <string.h>
#include <httpd/httpd.h>

#include <string.h>
#include <stdlib.h>
#include "system.h"

namespace adrone
{

	// GAMBIARRA  :#

	void websocket_cb(struct tcp_pcb *pcb, uint8_t *data, u16_t data_len, uint8_t mode)
	{
		//printf("[websocket_callback]:\n%.*s\n", (int) data_len, (char*) data);
		char response[64];
        int len;

		char * pch;
		pch = strtok ((char*) data,","); // split char
		
		if (pch != NULL) {
			switch ((uint8_t)pch[0]) {

				case 'O': //POWER
					if (asystem.power) {
		            	asystem.power = false;
		            	len = snprintf(response, sizeof (response), "Drone desligado");
		            } else {
		            	asystem.power = true;
		            	len = snprintf(response, sizeof (response), "Drone ligado");
		            }
			        
			        websocket_write(pcb, (unsigned char *) response, len, WS_TEXT_MODE);
	            	printf("%s\n", response);
				break;

				case 'P': // PITCH
					if (asystem.power) {
						pch = strtok (NULL,","); // split char, second part
						if (pch != NULL) {
							asystem.flight.gyro_x = atof(pch);
							//printf("Pitch: %f\n", asystem.flight.gyro_x);
						}
					}
				break;

				case 'R': // ROLL
					if (asystem.power) {
						pch = strtok (NULL,","); // split char, second part
						if (pch != NULL) {
							asystem.flight.gyro_y = atof(pch);
							//printf("Roll: %f\n", asystem.flight.gyro_y);
						}
					}
				break;

				case 'A': // ACCE_Z
					if (asystem.power) {
						pch = strtok (NULL,","); // split char, second part
						if (pch != NULL) {
							asystem.flight.acce_z = atof(pch);
							//printf("AcceZ: %f\n", asystem.flight.acce_z);
						}
					}
				break;

				case 'K': // CONFIG
					if (asystem.power) {
						double kp, ki, kd;
						kp = atof(strtok (NULL,",")); 
						ki = atof(strtok (NULL,",")); 
						kd = atof(strtok (NULL,","));
    					asystem.motor[0].pid.kpid(kp,ki,kd);

						kp = atof(strtok (NULL,",")); 
						ki = atof(strtok (NULL,",")); 
						kd = atof(strtok (NULL,",")); 
						asystem.motor[1].pid.kpid(kp,ki,kd);
    					
						kp = atof(strtok (NULL,",")); 
						ki = atof(strtok (NULL,",")); 
						kd = atof(strtok (NULL,",")); 
						asystem.motor[2].pid.kpid(kp,ki,kd);

						kp = atof(strtok (NULL,",")); 
						ki = atof(strtok (NULL,",")); 
						kd = atof(strtok (NULL,","));
						asystem.motor[3].pid.kpid(kp,ki,kd);

						//printf("%f,%f,%f|%f,%f,%f|%f,%f,%f|%f,%f,%f\n", asystem.motor[0].kp, asystem.motor[0].ki,asystem.motor[0].kd, asystem.motor[1].kp,asystem.motor[1].ki, asystem.motor[1].kd,asystem.motor[2].kp,asystem.motor[2].ki,asystem.motor[2].kd,asystem.motor[3].kp,asystem.motor[3].ki,asystem.motor[3].kd);
					}
				break;
			}
		}
	}

	void websocket_open_cb(struct tcp_pcb *pcb, const char *uri)
	{
	    //printf("WS URI: %s\n", uri);
	    /*if (!strcmp(uri, "/stream")) {
	        printf("request for streaming\n");
	    }*/
	}

	void httpd_task(void *pvParameters)
	{
	    websocket_register_callbacks(
	        (tWsOpenHandler) websocket_open_cb, 
	        (tWsHandler) websocket_cb
	    );

	    httpd_init();
	    
	    for (;;); 

	    vTaskDelete( NULL );
	}

}

#endif