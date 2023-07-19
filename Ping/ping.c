#include <stdio.h>
#include <winsock2.h>
#include <windows.h>
#include <iphlpapi.h>
#include <icmpapi.h>

#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")

#define MAX_REPLY_SIZE 1024

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed.\n");
        return 1;
    }

    HANDLE hIcmpFile = IcmpCreateFile();
    if (hIcmpFile == INVALID_HANDLE_VALUE) {
        printf("IcmpCreateFile failed: %ld\n", GetLastError());
        WSACleanup();
        return 1;
    }

    char sendBuf[32] = "Hello, Ping!";
    LPVOID replyBuf = malloc(MAX_REPLY_SIZE);
    DWORD replySize = sizeof(ICMP_ECHO_REPLY) + MAX_REPLY_SIZE;

    IPAddr destIp;
    DWORD ip = inet_addr("192.168.101.1");
    destIp = *(IPAddr*)&ip;

    DWORD dwRetVal = IcmpSendEcho(hIcmpFile, destIp, sendBuf, sizeof(sendBuf), NULL, replyBuf, replySize, 1000);
    if (dwRetVal != 0) {
        PICMP_ECHO_REPLY pEchoReply = (PICMP_ECHO_REPLY)replyBuf;
        struct in_addr ReplyAddr;
        ReplyAddr.S_un.S_addr = pEchoReply->Address;

        printf("Ping Reply from %s: bytes=%ld time=%ldms TTL=%ld\n",
            inet_ntoa(ReplyAddr), pEchoReply->DataSize, pEchoReply->RoundTripTime, pEchoReply->Options.Ttl);
    } else {
        printf("Ping failed: %ld\n", GetLastError());
    }

    IcmpCloseHandle(hIcmpFile);
    free(replyBuf);
    WSACleanup();

    return 0;
}
