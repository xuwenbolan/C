#include "Port_Scan.h"

char sumBuf[TCP_HEADER_LEN + sizeof(struct psdHeader)];

int main()
{
	get_ip();
	printf("%s\n",local);
	scan_port();
}

void get_ip()
{
	int n;
    struct ifreq ifr;
    char array[] = "eth0";
 
    n = socket(AF_INET, SOCK_DGRAM, 0);
    ifr.ifr_addr.sa_family = AF_INET;
    strncpy(ifr.ifr_name , array , IFNAMSIZ - 1);
    ioctl(n, SIOCGIFADDR, &ifr);
    close(n);
	strcpy(local,inet_ntoa(( (struct sockaddr_in *)&ifr.ifr_addr )->sin_addr));
}

void scan_port()
{
	time_t start,end;
	start =time(NULL);
	int raw_sock = init_connect();
	struct timeval timeout = {0,500}; 
	setsockopt(raw_sock,SOL_SOCKET,SO_RCVTIMEO,(char *)&timeout,sizeof(struct timeval));
	init_buf();
	char msg[1024]={0};
	struct tcphdr* tcph;
	for(int i=1;i<=9000;i++)
	{
		tHeader->dest=htons(i);//dest port
		tHeader->check = 0;
		memcpy(sumBuf + sizeof(struct psdHeader), tHeader, TCP_HEADER_LEN);
		tHeader->check = htons(calcTCPCheckSum(sumBuf));//checksum
		// printf("%x\n",htons(calcTCPCheckSum(sumBuf)));
		memcpy(buf + IP_HEADER_LEN, tHeader, TCP_HEADER_LEN);
		send(raw_sock,buf,totalLen,0);
		int res = recv(raw_sock,msg,sizeof(msg),0);
		// printf("%d\n",res);
		if(res>0)
		printf("Port: %d is Open\n",i);
		// else printf("Port: %d is Close\n",i);
	}
	close(raw_sock);
	end = time(NULL);
	printf("time: %fs\n",difftime(end,start));
}

int init_connect()
{
	int raw_sock = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
	const int on = 1;
	setsockopt(raw_sock, IPPROTO_IP, IP_HDRINCL, &on, sizeof(on));
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(struct sockaddr_in));
	addr.sin_family = AF_INET;
    inet_pton(AF_INET,target, &addr.sin_addr.s_addr);
    socklen_t len = sizeof(struct sockaddr_in);
    connect(raw_sock,(struct sockaddr*)&addr,len);
	return raw_sock;
}

void init_buf()
{
	tHeader = (struct tcphdr*) malloc(sizeof(struct tcphdr));
	memset(tHeader, 0, TCP_HEADER_LEN);
	initTCPHeader(tHeader);
	struct ip* iHeader = (struct ip*) malloc(sizeof(struct ip));
	memset(iHeader, 0, IP_HEADER_LEN);
	initIPHeader(iHeader);
	struct psdHeader* pHeader = (struct psdHeader*) malloc(sizeof(struct psdHeader));
	initPsdHeader(pHeader, iHeader);
 
	memset(sumBuf, 0, TCP_HEADER_LEN + sizeof(struct psdHeader));
	memcpy(sumBuf, pHeader, sizeof(struct psdHeader));
 
	memcpy(buf, iHeader, IP_HEADER_LEN);
}

void initTCPHeader(struct tcphdr* header) 
{
	header->source = htons(20);
	header->dest = htons(0);
 
	header->doff = sizeof(struct tcphdr) / 4;
	header->syn = 1;
	header->window = htons(4096);
	header->check = 0;
	header->seq = htonl(1);
	header->ack_seq = 0;
}

void initPsdHeader(struct psdHeader* header, struct ip* iHeader) 
{
	header->srcIP = iHeader->ip_src.s_addr;
	header->destIP = iHeader->ip_dst.s_addr;
 
	header->zero = 0;
	header->proto = IPPROTO_TCP;
	header->totalLen = htons(0x0014);
}

unsigned short calcTCPCheckSum(const char* buf)
{
	size_t size = TCP_HEADER_LEN + sizeof(struct psdHeader);
	unsigned int checkSum = 0;
	for (int i = 0; i < size; i += 2) {
		unsigned short first = (unsigned short)buf[i] << 8;
		unsigned short second = (unsigned short)buf[i+1] & 0x00ff;
		checkSum += first + second;
	}
	while (1) {
		unsigned short c = (checkSum >> 16);
		if (c > 0) {
			checkSum = (checkSum << 16) >> 16;
			checkSum += c;
		} else {
			break;
		}
	}
	return ~checkSum;
}

void initIPHeader(struct ip* header)
{
	header->ip_v = IPVERSION;
	header->ip_hl = sizeof(struct ip) / 4;
	header->ip_tos = 0;
	header->ip_len = htons(IP_HEADER_LEN + TCP_HEADER_LEN);
	header->ip_id = 0;
	header->ip_off = 0;
	header->ip_ttl = MAXTTL; 
	header->ip_p = IPPROTO_TCP;
	header->ip_sum = 0;
	inet_pton(AF_INET, local, &header->ip_src.s_addr);
	inet_pton(AF_INET, target, &header->ip_dst.s_addr);
}