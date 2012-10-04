#include "yun_socket.h"
#define ETH "eth2"
char* get_local_ip_address(void)
{
	char* yun_interface = ETH;
	int inet_sock;
	char *value = NULL;
	struct ifreq ifr;

	memset(&ifr, 0, sizeof(ifr));
	inet_sock = socket(AF_INET, SOCK_DGRAM, 0);
	strcpy(ifr.ifr_name, yun_interface);
	memset(&ifr.ifr_hwaddr, 0, sizeof(struct sockaddr));
	if (ioctl(inet_sock, SIOCGIFADDR, &ifr) < 0) {
		//perror("ioctl");
		//if can not get, will use default instead
		value = "127.0.0.1";
	} else {
		struct sockaddr_in* temp_sockaddr_in = (struct sockaddr_in*)&(ifr.ifr_addr);
		value = inet_ntoa(temp_sockaddr_in->sin_addr);
	}
	return value;
}
