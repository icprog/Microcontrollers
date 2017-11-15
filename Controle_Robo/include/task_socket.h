#ifndef ADRONE_SOCKET_H
#define ADRONE_SOCKET_H

#include <string.h>
#include <httpd/httpd.h>

#include <string.h>
#include <stdlib.h>

void websocket_cb(struct tcp_pcb *pcb, uint8_t *data, u16_t data_len, uint8_t mode)
{
	//printf("[websocket_callback]:\n%.*s\n", (int) data_len, (char*) data);
	char response[128];
    int len;

	char * pch;
	pch = strtok ((char*) data,","); // split char
	
	if (pch != NULL) {
		switch ((uint8_t)pch[0]) {

			case 'O': //POWER
				
			break;
			case 'F':
    	    		len = snprintf(response, sizeof (response), "PWM");
    	    		websocket_write(pcb, (unsigned char *) response, len, WS_TEXT_MODE);
    	    		
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

#endif