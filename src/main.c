#include <pthread.h>
#include "controlDevice.h"
#include "inputCommand.h"
 
struct InputCommand *pcommandHead = NULL;				              //定义指令工厂初始链表头
struct InputCommand *socketHandler = NULL;
 
struct InputCommand* findCommandByName(char *name, struct InputCommand *phead)
{
    struct InputCommand *tmp =phead;
    if(phead == NULL){
        return NULL;
    }else{
        while(tmp != NULL){
            if(strcmp(tmp->commandName,name)==0){
                return tmp;
            }
            tmp = tmp->next;
        }
        return NULL;
    }
}

void *socketReadThread(void *data)				//“读取tcp端口指令线程”执行的函数
{
    int n_read;
    printf("Connect success\n");
    while(1){
        memset(socketHandler->command,'\0',sizeof(socketHandler->command));
        n_read=read(socketHandler->fd,socketHandler->command,sizeof(socketHandler->command));
        if(n_read == -1){
            perror("read:");
        }else{
            printf("Get SocketCommand-->%s\n",socketHandler->command);
        }
    }
}
 
 
void *socketControlThread(void *data)           //“网络控制线程”执行的函数
{   
    int c_fd;                           //文件描述符
    struct sockaddr_in c_addr;
    memset(&c_addr,0,sizeof(struct sockaddr_in));
    int clen = sizeof(struct sockaddr_in);
 
    pthread_t socketRead_thread; //线程里面套线程，网络连接后信息通信
 
    socketHandler =  findCommandByName("socket", pcommandHead);
 
    if(socketHandler == NULL){
        printf("find socketHandler error\n");
        pthread_exit(NULL);
    }
    if(socketHandler->Init(socketHandler) < 0){   //“网络控制”功能初始化
        printf("socketControl init error\n");
        pthread_exit(NULL);
    }else{
        printf("socketControl init success\n");
    }
    while(1){
        //4.accept
		c_fd = accept(socketHandler->s_fd,(struct sockaddr *)&c_addr,&clen);	//接收连接请求，阻塞至有客户端完成三次握手
		socketHandler->fd = c_fd;					                            //将套接字描述符返回给“网络控制”链表节点
		pthread_create(&socketRead_thread,NULL,socketReadThread,NULL);			//创建新线程：用于读取TCP端口指令
    }
}
 
 
int main()
{
  
    if (wiringPiSetup () == -1) { 
        fprintf (stdout, "Unable to start wiringPi: %s\n", strerror (errno)) ; 
        return 1 ; 
    }
 
	pthread_t socketControl_thread;
 
    //指令工厂初始化
    pcommandHead = addSocketControlToInputCommandLink(pcommandHead);
     
    pthread_create(&socketControl_thread,NULL,socketControlThread,NULL);
 
	pthread_join(socketControl_thread, NULL);		//主函数等待线程退出
 
    return 0;
}