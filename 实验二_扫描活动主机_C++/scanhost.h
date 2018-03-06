//
// Created by mengzx on 2018/1/12.
//

#ifndef SCANHOST_SCANHOST_H
#define SCANHOST_SCANHOST_H

#endif //SCANHOST_SCANHOST_H


#pragma pack(4)

#pragma comment (lib,"Ws2_32.lib")
#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sys/timeb.h>
#include <time.h>

typedef struct iphdr{
    unsigned int headlen:4;
    unsigned int version:4;
    unsigned char tos;
    unsigned short totallen;
    unsigned short id;
    unsigned short flag;
    unsigned char ttl;
    unsigned short checksum;

    unsigned int sourceIP;
    unsigned int destIP;
}IpHeader;

//ICMP header
typedef struct icmphdr{
    BYTE type;
    BYTE code;
    USHORT checksum;
    USHORT id;
    USHORT seq;
}IcmpHeader;

#define ICMP_ECHO 8         //请求回送
#define ICMP_ECHO_REPLY 0   //请求回应
#define ICMP_MIN 8          //ICMP包头长度
#define STATUS_FALLED 0xFFFF //错误码
#define DEF_PACKET_SIZE 32  //缺省数据报长度
#define MAX_PACKET 1024     //最大数据块长度
#define MAX_PING_PACKET_SIZE (MAX_PACKET + sizeof(IpHeader))

void fill_icmp_data(char *, int);       //填充ICMP包
USHORT checksum(USHORT *, int);         //校验和函数
void decode_resp(char *, int ,struct sockaddr_in *);
DWORD WINAPI FindIP(LPVOID pIPAddrTemp);


