#pragma comment(lib,"ws2_32.lib")
#include <io.h>
#include <fcntl.h>
#include <sys\stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#define SERVER_PORT 8080 //侦听端口


struct Data
{
 int number;
 int length;
 char sendMessage[2000];
 int fin;
}data;

int main()
{
 //struct Data data;
   FILE * fp;
   fp=fopen("1.jpeg","rb+");
   WORD wVersionRequested;
   WSADATA wsaData;
   int ret;
   SOCKET sClient; //连接套接字
   struct sockaddr_in saServer; //地址信息
   char *ptr;
   BOOL fSuccess = TRUE;
 
   fseek(fp,0,SEEK_END);
   int end = ftell(fp);
   fseek(fp,0,0);
   //WinSock初始化
   wVersionRequested = MAKEWORD(2, 2); //希望使用的WinSock DLL的版本
   ret = WSAStartup(wVersionRequested, &wsaData);
   if(ret!=0)
   {
        printf("WSAStartup() failed!\n");
        return 0;
   }
   //确认WinSock DLL支持版本2.2
   if(LOBYTE(wsaData.wVersion)!=2 || HIBYTE(wsaData.wVersion)!=2)
   {
        WSACleanup();
        printf("Invalid WinSock version!\n");
        return 0;
   }
   //创建Socket,使用TCP协议
   sClient = socket(AF_INET, SOCK_STREAM,0);
   if (sClient == INVALID_SOCKET)
   {
        WSACleanup();
        printf("socket() failed!\n");
        return 0;
   }
   //构建服务器地址信息
   saServer.sin_family = AF_INET; //地址家族
   saServer.sin_port = htons(SERVER_PORT); //注意转化为网络节序
   saServer.sin_addr.S_un.S_addr = inet_addr("192.168.1.111");
   //连接服务器
   ret = connect(sClient, (struct sockaddr *)&saServer, sizeof(saServer));
   if (ret == SOCKET_ERROR)
   {
        printf("connect() failed!\n");
        closesocket(sClient); //关闭套接字
        WSACleanup();
        return 0;
   }
 char sendMessage[2000];
 int sum=0;
 int times=0;
 char flag='0';
   while(end>0)
   {
    memset(data.sendMessage,'0',sizeof(data.sendMessage));
    fread(data.sendMessage,1024,1,fp);
    if(end>=1024) //剩余很多信息
    {
   data.fin = 0;
   data.length = 1024;  
    }
    else
    {
     data.fin = 1;
     data.length = end;
     //flag = '1';
    }
    ret = send(sClient, (char *)&data,sizeof(struct Data),0); 
    if (ret == SOCKET_ERROR)
    {
   printf("send() failed!\n");
    }
    else
   //printf("client info has been sent!");
    //sum+=1024;
    end -= 1024;
    //ret = send(sClient, (char *)&flag,1,0);
   }
    while(1);
   closesocket(sClient); //关闭套接字
   WSACleanup();
    return 0;
}
