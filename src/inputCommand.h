#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>      
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <wiringPi.h>
#include <wiringSerial.h>
 
struct InputCommand
{
    char commandName[128];                              //“控制方式”名
    char deviceName[128];               
    char command[32];                                   //存放指令
    int fd;                                             //存放文件描述符（串口/网络）
    int s_fd;									        //存放服务器套接字描述符
    char port[12];								        //存放端口号
    char ipAdress[32];							        //存放 IP地址
    char log[1024];                                     //日志
    int (*Init)(struct InputCommand *voice);            //“初始化”函数指针
    int (*getCommand)(struct InputCommand *voice);      //“获取指令”函数指针
 
 
    struct InputCommand *next;
};
 
struct InputCommand* addSocketControlToInputCommandLink(struct InputCommand *phead);