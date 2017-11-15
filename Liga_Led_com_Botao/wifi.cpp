#include "wifi.h"


adrone::wifi::wifi()
{
	// get default configurations
	sdk_wifi_get_ip_info(1, &_ap.addr);
	sdk_wifi_softap_get_config(&_ap.config);

	// disable wifi
	sdk_wifi_set_opmode(NULL_MODE);

	// AP starting settins
	ap_auth(AUTH_OPEN);
	ap_network("172.16.0.1", "172.16.0.1", "255.255.0.0");
	ap_dhcp("172.16.0.2", 4);
}


void adrone::wifi::ap_access(const char *ssid, const char *password)
{
	if (strlen(ssid) > 0)
		strcpy((char *)_ap.config.ssid , ssid);

	if (strlen(password) > 0)
		strcpy((char *)_ap.config.password, password);

	_ap.config.ssid_len = strlen(ssid);
}

   
void adrone::wifi::ap_auth(const AUTH_MODE &auth)
{
	_ap.config.authmode = auth;
}


void adrone::wifi::ap_network(const char *ip, const char *gatway, const char *netmask)
{
	ipaddr_aton(ip     , &_ap.addr.ip     );
	ipaddr_aton(gatway , &_ap.addr.gw     );
	ipaddr_aton(netmask, &_ap.addr.netmask);
}


void adrone::wifi::ap_hidden(const bool &hide)
{
	_ap.config.ssid_hidden = hide;
}


void adrone::wifi::ap_channel(const uint8_t &channel)
{
	_ap.config.channel = channel;
}


void adrone::wifi::ap_connection(const uint8_t &max)
{
	_ap.config.max_connection  = max;
}


void adrone::wifi::ap_beacon(const uint16_t &millis)
{
	_ap.config.beacon_interval = millis;
}


void adrone::wifi::ap_dhcp(const char *start, const uint8_t &max)
{
	ipaddr_aton(start, &_ap.dhcp_ip);
	_ap.dhcp_max = max;
}


void adrone::wifi::station_access(const char *ssid, const char *password)
{
	if (strlen(ssid) > 0)
		strcpy((char *)_station.ssid , ssid);

	if (strlen(password) > 0)
		strcpy((char *)_station.password, password);

}


void adrone::wifi::phy_mode(const sdk_phy_mode &mode)
{
	sdk_wifi_set_phy_mode(mode);
}


void adrone::wifi::init(const uint8_t &opmode)
{
	sdk_wifi_set_opmode(opmode);

	if (opmode == SOFTAP_MODE || opmode == STATIONAP_MODE)
	{
		sdk_wifi_set_ip_info(1, &_ap.addr);
		sdk_wifi_softap_set_config(&_ap.config);
		dhcpserver_start(&_ap.dhcp_ip, _ap.dhcp_max);
	}

	if (opmode == STATION_MODE || opmode == STATIONAP_MODE)
	{
		sdk_wifi_station_set_config(&_station);
	}
}