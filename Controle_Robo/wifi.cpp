#include "wifi.h"


wifi::wifi(){}

void wifi::init()
{
	sdk_wifi_set_opmode(SOFTAP_MODE);
    struct ip_info ap_ip;
    IP4_ADDR(&ap_ip.ip, 192, 168, 0, 100);
    IP4_ADDR(&ap_ip.gw, 0, 0, 0, 0);
    IP4_ADDR(&ap_ip.netmask, 255, 255, 0, 0);
    sdk_wifi_set_ip_info(1, &ap_ip);

    strcpy((char *)ap_config.ssid, AP_SSID);
    ap_config.ssid_hidden = 0;
    ap_config.channel = 3;
    ap_config.ssid_len = strlen(AP_SSID);
    ap_config.authmode = AUTH_WPA_WPA2_PSK;
    strcpy((char *)ap_config.password, AP_PSK);
    ap_config.max_connection = 3;
    ap_config.beacon_interval = 100;
    sdk_wifi_softap_set_config(&ap_config);

    ip_addr_t first_client_ip;
    IP4_ADDR(&first_client_ip, 192, 168, 0, 101);
    dhcpserver_start(&first_client_ip, 4);
}
