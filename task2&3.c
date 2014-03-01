#include <winsock2.h>
#include <sys/stat.h>
#include <iostream>
using namespace std;
#define SERVER_PORT 8080         //自定义的服务端口
#define HOSTLEN 256           //主机名长度
#define BACKLOG 10           //同时等待的连接个数

int main()
{
 WORD wVersionRequested;
 WSADATA wsaData;
 int err;
  
 wVersionRequested = MAKEWORD( 1, 1 );
  
 err = WSAStartup( wVersionRequested, &wsaData );
 if ( err != 0 ) {
  return 0;
 }
  
 if ( LOBYTE( wsaData.wVersion ) != 1 ||
        HIBYTE( wsaData.wVersion ) != 1 ) {
  WSACleanup( );
  return 0;
 }
 SOCKET sockSrv=socket(AF_INET,SOCK_STREAM,0);
 
 SOCKADDR_IN addrSrv;
 addrSrv.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
 addrSrv.sin_family=AF_INET;
 addrSrv.sin_port=htons(8080);
  
 bind(sockSrv,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));
 
 listen(sockSrv,5);
 
 SOCKADDR_IN addrClient;
 int len=sizeof(SOCKADDR);
 while(1)
 {
  SOCKET sockConn=accept(sockSrv,(SOCKADDR*)&addrClient,&len);
  char sendBuf[50];
  sprintf(sendBuf,"Welcome %s to here!",inet_ntoa(addrClient.sin_addr));
  send(sockConn,sendBuf,strlen(sendBuf)+1,0);
  char recvBuf[50];
  recv(sockConn,recvBuf,50,0);
  printf("%s\n",recvBuf);
  closesocket(sockConn);
 }
 return 0;
}
