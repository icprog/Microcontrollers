PROGRAM=main


#EXTRA_CFLAGS=-DLWIP_HTTPD_CGI=1 -DLWIP_HTTPD_SSI=1 -I./fsdata
EXTRA_C_CXX_FLAGS=-DLWIP_HTTPD_CGI=1 -DLWIP_HTTPD_SSI=1 -I./include/
EXTRA_CXXFLAGS=-std=c++11

#Enable debugging
#EXTRA_CFLAGS+=-DLWIP_DEBUG=1 -DHTTPD_DEBUG=LWIP_DBG_ON


EXTRA_COMPONENTS = \
extras/dhcpserver \
extras/httpd \
extras/mbedtls \
extras/i2c \
extras/rboot-ota 

LIBS ?= hal gcc c m


include /opt/espressif/esp-open-rtos/common.mk


run:
	$(FILTEROUTPUT) --port $(ESPPORT) --baud 115200 --elf $(PROGRAM_OUT)

ota: all
	atftp -p -l $(FW_FILE) -r firmware.bin --option "mode octet" 172.16.0.1 69
