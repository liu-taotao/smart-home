#include <pthread.h>
#include "controlDevice.h"
#include "inputCommand.h"
 
struct InputCommand *pcommandHead = NULL;				              //定义指令工厂初始链表头
struct Devices      *pdeviceHead  = NULL;				              //定义设备工厂初始链表头
struct InputCommand *socketHandler = NULL;
 
struct Devices* findDeviceByName(char *name, struct Devices *phead)
{
    struct Devices *tmp =phead;
    if(phead == NULL){
        return NULL;
    }else{
        while(tmp != NULL){
            if(strcmp(tmp->deviceName,name)==0){
                return tmp;
            }
            tmp = tmp->next;
        }
        return NULL;
    }
}
 
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
 
void Command(struct InputCommand* CmdHandler)
{
    struct Devices *tmp =NULL;

    if(CmdHandler->command[0] == 48 || CmdHandler->command[0] == 0){
        tmp = findDeviceByName("smokeAlarm",pdeviceHead);
		if(tmp != NULL)  tmp->Init(tmp->pinNum);
		tmp = findDeviceByName("buzzer",pdeviceHead);
		if(tmp != NULL)  tmp->Init(tmp->pinNum);
		tmp = findDeviceByName("livingroomLight",pdeviceHead);
		if(tmp != NULL)  tmp->Init(tmp->pinNum); 
		tmp = findDeviceByName("restaurantLight",pdeviceHead);
		if(tmp != NULL)  tmp->Init(tmp->pinNum);
		tmp = findDeviceByName("bedroomLight",pdeviceHead);
		if(tmp != NULL)  tmp->Init(tmp->pinNum);
		tmp = findDeviceByName("bathroomLight",pdeviceHead);
		if(tmp != NULL)  tmp->Init(tmp->pinNum);
        tmp = findDeviceByName("lock",pdeviceHead);
		if(tmp != NULL)  tmp->Init(tmp->pinNum);
        printf("设备已全部初始化\n");
	}
	if(CmdHandler->command[0] == 1 || CmdHandler->command[0] == 49){
		tmp = findDeviceByName("livingroomLight",pdeviceHead);
        if(tmp != NULL){
            tmp->open(tmp->pinNum);
            printf("已打开客厅灯\n");
        }
	}
    if(CmdHandler->command[0] == 2 || CmdHandler->command[0] == 50){
		tmp = findDeviceByName("livingroomLight",pdeviceHead);
        if(tmp != NULL){
            tmp->close(tmp->pinNum);
            printf("已关闭客厅灯\n");
        }
	}
    if(CmdHandler->command[0] == 3 || CmdHandler->command[0] == 51){
		tmp = findDeviceByName("restaurantLight",pdeviceHead);
        if(tmp != NULL){
            tmp->open(tmp->pinNum);
            printf("已打开餐厅灯\n");
        }
	}
    if(CmdHandler->command[0] == 4 || CmdHandler->command[0] == 52){
		tmp = findDeviceByName("restaurantLight",pdeviceHead);
        if(tmp != NULL){
            tmp->close(tmp->pinNum);
            printf("已关闭餐厅灯\n");
        }
	}
    if(CmdHandler->command[0] == 5 || CmdHandler->command[0] == 53){
		tmp = findDeviceByName("bedroomLight",pdeviceHead);
        if(tmp != NULL){
            tmp->open(tmp->pinNum);
            printf("已打开卧室灯\n");
        }
	}
    if(CmdHandler->command[0] == 6 || CmdHandler->command[0] == 54){
		tmp = findDeviceByName("bedroomLight",pdeviceHead);
        if(tmp != NULL){
            tmp->close(tmp->pinNum);
            printf("已关闭卧室灯\n");
        }
	}
    if(CmdHandler->command[0] == 7 || CmdHandler->command[0] == 55){
		tmp = findDeviceByName("bathroomLight",pdeviceHead);
        if(tmp != NULL){
            tmp->open(tmp->pinNum);
            printf("已打开浴室灯\n");
        }
	}
    if(CmdHandler->command[0] == 8 || CmdHandler->command[0] == 56){
		tmp = findDeviceByName("bathroomLight",pdeviceHead);
        if(tmp != NULL){
            tmp->close(tmp->pinNum);
            printf("已关闭浴室灯\n");
        }
	}
	if(CmdHandler->command[0] == 97){
		tmp = findDeviceByName("lock",pdeviceHead);
		if(tmp != NULL){
			tmp->open(tmp->pinNum);
			printf("Open door.\n");
		}
	}
	if(CmdHandler->command[0] == 98){
		tmp = findDeviceByName("lock",pdeviceHead);
		if(tmp != NULL){
			tmp->close(tmp->pinNum);
			printf("Close door.\n");
		}
	}
    if(CmdHandler->command[0] == 9 || CmdHandler->command[0] == 57){
		tmp = findDeviceByName("livingroomLight",pdeviceHead);
		if(tmp != NULL)  tmp->open(tmp->pinNum);
		tmp = findDeviceByName("restaurantLight",pdeviceHead);
		if(tmp != NULL)  tmp->open(tmp->pinNum);
		tmp = findDeviceByName("bedroomLight",pdeviceHead);
		if(tmp != NULL)  tmp->open(tmp->pinNum);
		tmp = findDeviceByName("bathroomLight",pdeviceHead);
		if(tmp != NULL)  tmp->open(tmp->pinNum);
        printf("已打开所有灯\n");
    }
    if(CmdHandler->command[0] == 10 || CmdHandler->command[0] == 58){
		tmp = findDeviceByName("livingroomLight",pdeviceHead);
		if(tmp != NULL)  tmp->close(tmp->pinNum);
		tmp = findDeviceByName("restaurantLight",pdeviceHead);
		if(tmp != NULL)  tmp->close(tmp->pinNum);
		tmp = findDeviceByName("bedroomLight",pdeviceHead);
		if(tmp != NULL)  tmp->close(tmp->pinNum);
		tmp = findDeviceByName("bathroomLight",pdeviceHead);
		if(tmp != NULL)  tmp->close(tmp->pinNum);
        printf("已关闭所有灯\n");
	}
}
 
void *voiceControlThread(void *data)			//“语音控制线程”执行函数
{   
    int nread;
    struct InputCommand *voiceHandler = NULL;
    voiceHandler =  findCommandByName("voice", pcommandHead);
 
    if(voiceHandler == NULL){
        printf("find voiceHandler error\n");
        pthread_exit(NULL);
    }else{
        if(voiceHandler->Init(voiceHandler) < 0){       //“语音控制”功能初始化
            printf("voiceControl init error\n");
            pthread_exit(NULL);
        }else{
            printf("voiceControl init success\n");
        }
        for( ; ; ){
            memset(voiceHandler->command,'\0',sizeof(voiceHandler->command));
            delay(100);
            nread = voiceHandler->getCommand(voiceHandler);
            if(nread == 0){                                 //串口没有获取到指令
                printf("No voiceCommand received\n");
            }else{											//获取到指令
                printf("voice Get VoiceCommand -->%d\n",voiceHandler->command[0]);
                Command(voiceHandler);
            }
        }   
    }
}
 
void *socketReadThread(void *data)				//“读取tcp端口指令线程”执行的函数
{
    int n_read;
    printf("Connect success\n");
    for ( ; ; ){
        memset(socketHandler->command,'\0',sizeof(socketHandler->command));
        n_read=read(socketHandler->fd,socketHandler->command,sizeof(socketHandler->command));
        send(socketHandler->fd, socketHandler->command, sizeof(socketHandler->command), 0);
        if(n_read == -1){
            perror("read:");
        }else{
            printf("socket Get SocketCommand-->%d\n",socketHandler->command[0]);
            Command(socketHandler);
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
    for ( ; ; ){
        //4.accept
		c_fd = accept(socketHandler->s_fd,(struct sockaddr *)&c_addr,&clen);	//接收连接请求，阻塞至有客户端完成三次握手
		socketHandler->fd = c_fd;
        delay(10);					                            //将套接字描述符返回给“网络控制”链表节点
		pthread_create(&socketRead_thread,NULL,socketReadThread,NULL);			//创建新线程：用于读取TCP端口指令
    }
}

void *smokeAlarmThread(void *data)               //“烟雾报警器线程”执行的函数
{
    int smokeStatus;												//存放“烟雾传感器”状态
    struct Devices *tmp = NULL;
    printf("smokeAlarmThread is ok\n");
    for ( ; ; ){
        tmp = findDeviceByName("smokeAlarm", pdeviceHead);
        if(tmp != NULL){
            smokeStatus = tmp->readStatus(tmp->pinNum);
            delay(100);
            tmp = findDeviceByName("buzzer", pdeviceHead);
            if(tmp != NULL){
                if( smokeStatus == 0 ){
                    tmp->open(tmp->pinNum);
                }else{
                    tmp->close(tmp->pinNum);
                }           
            }
        }
    }
}
 
int main()
{
    if (wiringPiSetup () == -1) { 
        fprintf (stdout, "Unable to start wiringPi: %s\n", strerror (errno)) ; 
        return 1 ; 
    }
    
    pthread_t voiceControl_thread;
	pthread_t socketControl_thread;
	pthread_t smokeAlarm_thread;
 
    //1.指令工厂初始化
    pcommandHead = addVoiceControlToInputCommandLink(pcommandHead);
    pcommandHead = addSocketControlToInputCommandLink(pcommandHead);
    
    //2.设备控制工厂初始化
    pdeviceHead = addBathroomLightToDeviceLink(pdeviceHead);            //“浴室灯”加入设备链表
    pdeviceHead = addBedroomLightToDeviceLink(pdeviceHead);
    pdeviceHead = addRestaurantLightToDeviceLink(pdeviceHead);
    pdeviceHead = addLivingroomLightToDeviceLink(pdeviceHead);
    pdeviceHead = addSmokeAlarmToDeviceLink(pdeviceHead);
    pdeviceHead = addBuzzerToDeviceLink(pdeviceHead);
    pdeviceHead = addLockToDeviceLink(pdeviceHead);
    //3.线程池建立  int pthread_create(pthread_t *restrict tidp, const pthread_attr_t *restrict attr, void *(*start_rtn)(void *), void *restrict arg); 
    //3.1 语音线程
    pthread_create(&voiceControl_thread,NULL,voiceControlThread,NULL);
    //3.2 socket线程
    pthread_create(&socketControl_thread,NULL,socketControlThread,NULL);
    //3.3 烟雾报警线程
    pthread_create(&smokeAlarm_thread,NULL,smokeAlarmThread,NULL);
    //3.4 摄像头线程
    printf("exit\n");
    pthread_join(voiceControl_thread, NULL);		//主函数等待线程退出
	pthread_join(socketControl_thread, NULL);		//主函数等待线程退出
	pthread_join(smokeAlarm_thread, NULL);			//主函数等待线程退出
 
    return 0;
}