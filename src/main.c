#include <pthread.h>
#include "controlDevice.h"
#include "inputCommand.h"
 
struct InputCommand *pcommandHead = NULL;				              //定义指令工厂初始链表头
 
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
        while(1){
            memset(voiceHandler->command,'\0',sizeof(voiceHandler->command));
            nread = voiceHandler->getCommand(voiceHandler);
            if(nread == 0){                                 //串口没有获取到指令
                printf("No voiceCommand received\n");
            }else{											//获取到指令
                printf("Get VoiceCommand -->%s\n",voiceHandler->command);        
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
 
    //指令工厂初始化
    pcommandHead = addVoiceControlToInputCommandLink(pcommandHead);
 
    //语音线程
    pthread_create(&voiceControl_thread,NULL,voiceControlThread,NULL);
 
    pthread_join(voiceControl_thread, NULL);		//主函数等待线程退出
 
    return 0;
}