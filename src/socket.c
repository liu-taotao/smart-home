#include "inputCommand.h"
 
int socketInit(struct InputCommand *socketMsg)
{
    int s_fd;                                       //套接字描述符
	struct sockaddr_in s_addr;
	memset(&s_addr,0,sizeof(struct sockaddr_in));   //数据清空
 
    //1.socket
	s_fd=socket(AF_INET,SOCK_STREAM,0);             //创建套接字,ipv4 tcp协议
	if(s_fd == -1){                                 //若创建套接字失败
		perror("socket:");
		exit(-1);
	}
 
    s_addr.sin_family = AF_INET;                        //ipv4
	s_addr.sin_port = htons(atoi(socketMsg->port));     //端口号，选择5000以上。honts返回网络字节序,atoi(argv[2])防止端口被占用
	inet_aton(socketMsg->ipAdress,&s_addr.sin_addr);    //转换为网络能识别的格式
 
    //2.bind
	bind(s_fd,(struct sockaddr *)&s_addr,sizeof(struct sockaddr_in));
 
    //3.listen
	listen(s_fd,10);//监听10个连接
    printf("socket Server listening ...\n");
 
    socketMsg->s_fd = s_fd;						    //发送套接字描述符
    return s_fd;
}
 
 
struct InputCommand socketControl = {
    .commandName = "socket",
    .command = '\0',
    .port = "8080",
    .ipAdress = "192.168.100.11",
    .Init = socketInit,
    .log = {'\0'},
    .next = NULL
};
 
struct InputCommand* addSocketControlToInputCommandLink(struct InputCommand *phead)
{
	if(phead == NULL){
		return &socketControl;
	}else{
		socketControl.next = phead;
		phead = &socketControl;
		return phead;
	}
}