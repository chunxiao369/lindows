#include "yun_socket.h"
void __yun_socket(void)
{
    return;
}

char* get_local_ip_address(void)
{
    static char host_name[64];
    static char host_address[64];
    HOSTENT *host_entry;
    WSADATA wsaData;

    WSAStartup(MAKEWORD(2, 2), &wsaData);
    memset(host_name, 0, 64);
    memset(host_address, 0, 64);
    gethostname(host_name, 64);
    host_entry = gethostbyname(host_name);
    WSACleanup();

    if (host_entry != 0) {
        sprintf(host_address,"%d.%d.%d.%d",
        (host_entry->h_addr_list[0][0]&0x00ff),
        (host_entry->h_addr_list[0][1]&0x00ff),
        (host_entry->h_addr_list[0][2]&0x00ff),
        (host_entry->h_addr_list[0][3]&0x00ff));
        return host_address;
    } else {
        return "127.0.0.1";
    }
}

