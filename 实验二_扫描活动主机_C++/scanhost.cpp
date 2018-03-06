//
// Created by mengzx on 2018/1/12.
//
#include "scanhost.h"

WSADATA wsadata;
SOCKET sockRaw;
struct sockaddr_in dest,from,end;

int fromlen=sizeof(from);
char *recvbuf=new char[MAX_PING_PACKET_SIZE];
unsigned int addr=0;
long ThreadNumCounter=0,ThreadNumLimit=20;
long *aa=&ThreadNumCounter;

int main(int argc,char *argv[]) {
    if(argc!=3){
        std::cout<<"输入格式错误:scanhost start_ip end_ip"<<std::endl;
        return 0;
    }
    if(WSAStartup(MAKEWORD(2,1),&wsadata)!=0){
        std::cout<<"WSAStartup failed: "<<GetLastError()<<std::endl;
        ExitProcess(STATUS_FALLED);
    }
    sockRaw=WSASocket(AF_INET,SOCK_RAW,IPPROTO_ICMP,NULL,0,WSA_FLAG_OVERLAPPED);
    if(sockRaw == INVALID_SOCKET){
        std::cout<<"WSASocket() failed :"<<WSAGetLastError()<<std::endl;
        ExitProcess(STATUS_FALLED);
    }

    int timeout=1000;
    int bread=setsockopt(sockRaw,SOL_SOCKET,SO_RCVTIMEO,(char*)&timeout, sizeof(timeout));
    if(bread==SOCKET_ERROR){
        std::cout<<"failed to set recv timeout: "<<WSAGetLastError()<<std::endl;
        ExitProcess(STATUS_FALLED);
    }
    timeout=1000;
    bread=setsockopt(sockRaw,SOL_SOCKET,SO_RCVTIMEO,(char*)&timeout, sizeof(timeout));
    if(bread==SOCKET_ERROR){
        std::cout<<"failed to set recv timeout: "<<WSAGetLastError()<<std::endl;
        ExitProcess(STATUS_FALLED);
    }

    memset(&dest,0,sizeof(dest));

    unsigned long startIP,endIP;
    dest.sin_family=AF_INET;
    dest.sin_addr.s_addr=inet_addr(argv[1]);
    startIP=inet_addr(argv[1]);
    end.sin_family=AF_INET;
    end.sin_addr.s_addr=inet_addr(argv[2]);
    endIP=inet_addr(argv[2]);
    HANDLE hThread;
    while(htonl(startIP)<=htonl(endIP)){
        if(ThreadNumCounter>ThreadNumLimit){
            Sleep(5000);
            continue;
        }
        DWORD ThreadID;
        sockaddr_in * pIPAddrTemp=new(sockaddr_in);
        if(!pIPAddrTemp){
            std::cout<<"memory alloc failed"<<std::endl;
            return 0;
        }
        *pIPAddrTemp=dest;

        clock_t start;
        start=clock();
        hThread=CreateThread(NULL,NULL,FindIP,(LPVOID)pIPAddrTemp,NULL,&ThreadID);
        long i=60000000L;
        while(i--);
        TerminateThread(hThread,0);
        InterlockedDecrement(aa);
        memset(&from,0,sizeof(from));
        startIP=htonl(htonl(startIP)+1);
        dest.sin_addr.s_addr=startIP;
    }
    while(ThreadNumCounter!=0){
        Sleep(2000);
        return 0;
    }
    return 0;
}

void fill_icmp_data(char * icmp_data,int datasize){
    IcmpHeader *icmp_hdr;
    char *datapart;
    icmp_hdr=(IcmpHeader*)icmp_data;
    icmp_hdr->type=ICMP_ECHO;
    icmp_hdr->id=(USHORT)GetCurrentThreadId();
    datapart=icmp_data+sizeof(IcmpHeader);
    memset(datapart,'A',datasize-sizeof(IcmpHeader));
}

void decode_resp(char *buf,int bytes, struct sockaddr_in *from){
    IpHeader *iphdr;
    IcmpHeader *icmphdr;
    unsigned short iphdrlen;
    iphdr = (IpHeader *)(buf);
    iphdrlen=iphdr->headlen *4;
    icmphdr=(IcmpHeader*)(buf+iphdrlen);

    if(bytes<iphdrlen+ICMP_MIN)
        return;
    if(icmphdr->type!=ICMP_ECHO_REPLY)
        return;
    if(icmphdr->id!=(USHORT)GetCurrentThreadId())
        return;
    std::cout<<"活动主机： "<<inet_ntoa(from->sin_addr)<<std::endl;
}

USHORT checksum(USHORT *buffer,int size){
    unsigned long cksum=0;
    while(size>1){
        cksum+=*buffer++;
        size -=sizeof(USHORT);
    }
    if(size){
        cksum+= *(UCHAR*)buffer;
    }
    cksum = (cksum>>16)+(cksum & 0xffff);
    cksum += (cksum>>16);
    return (USHORT)(~cksum);
}

DWORD WINAPI FindIP(LPVOID pIPAddrTemp){
    InterlockedIncrement(aa);

    char icmp_data[MAX_PACKET];
    memset(icmp_data,0,MAX_PACKET);
    int datasize=DEF_PACKET_SIZE;
    datasize+=sizeof(IcmpHeader);
    fill_icmp_data(icmp_data,datasize);
    ((IcmpHeader*)icmp_data)->checksum=0;
    ((IcmpHeader*)icmp_data)->seq=0;

    ((IcmpHeader*)icmp_data)->checksum=checksum((USHORT*)icmp_data,datasize);
    int bwrote = sendto(sockRaw,icmp_data,datasize,0,(
    struct sockaddr*)pIPAddrTemp,sizeof(dest));
    int n=0;
    if(bwrote==SOCKET_ERROR){
        if(WSAGetLastError()==WSAETIMEDOUT){
            std::cout<<"timed out"<<std::endl;
        }
        std::cout<<"sendto failed: "<<WSAGetLastError()<<std::endl;
        ExitProcess(STATUS_FALLED);
        n=1;
    }

    if(WSAGetLastError()==WSAETIMEDOUT){
        std::cout<<"timed out"<<std::endl;
        ExitProcess(STATUS_FALLED);
        n=1;
    }

    if(bwrote<datasize){
        std::cout<<"Wrote "<<bwrote<<" bytes"<<std::endl;
        ExitProcess(STATUS_FALLED);
        n=1;
    }
    int bread = recvfrom(sockRaw,recvbuf,MAX_PING_PACKET_SIZE,0,(struct sockaddr*) &from,&fromlen);

    if(bread==SOCKET_ERROR){

        if(WSAGetLastError()==WSAETIMEDOUT){
            std::cout<<"timed out"<<std::endl;
        }
        std::cout<<"recvfrom failed: "<<WSAGetLastError()<<std::endl;
        ExitProcess(STATUS_FALLED);
        n=1;
    }
    if(n==0){
        decode_resp(recvbuf,bread,&from);
    }
    InterlockedIncrement(aa);
    return 0;
}
