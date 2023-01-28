#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <net/if.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <time.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <sys/ioctl.h>

#define IP_HEADER_LEN sizeof(struct ip)
#define TCP_HEADER_LEN sizeof(struct tcphdr)
int totalLen = IP_HEADER_LEN + TCP_HEADER_LEN;
char buf[40];

const char* target="113.100.153.2";
char local[16] = {0};
struct tcphdr* tHeader;

struct psdHeader 
{
	unsigned int srcIP;
	unsigned int destIP;
	unsigned short zero:8;
	unsigned short proto:8;
	unsigned short totalLen;
};

int init_connect();
void initTCPHeader(struct tcphdr* header);
void initPsdHeader(struct psdHeader* header, struct ip* iHeader);
unsigned short calcTCPCheckSum(const char* buf);
void initIPHeader(struct ip* header);
void init_buf();
void scan_port();
void get_ip();