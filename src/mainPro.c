#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "controlDevice.h"
 
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
 
int main()
{
    char *smokeName = "smokeAlarm";
    char *buzzerName = "buzzer";
    struct Devices *tmp = NULL;
    int smokeStatus;												//存放“烟雾传感器”状态
 
    if (wiringPiSetup () == -1) { 
        fprintf (stdout, "Unable to start wiringPi: %s\n", strerror (errno)) ; 
        return 1 ; 
    }
 
    struct Devices *pdeviceHead = NULL;				                    //定义初始链表头
    //pdeviceHead = addBathroomLightToDeviceLink(pdeviceHead);            //“浴室灯”加入设备链表
    //pdeviceHead = addBedroomLightToDeviceLink(pdeviceHead);
    //pdeviceHead = addRestaurantLightToDeviceLink(pdeviceHead);
    //pdeviceHead = addLivingroomLightToDeviceLink(pdeviceHead);
    pdeviceHead = addSmokeAlarmToDeviceLink(pdeviceHead);
    pdeviceHead = addBuzzerToDeviceLink(pdeviceHead);
 
    while(1){
        tmp = findDeviceByName(smokeName, pdeviceHead);
        if(tmp != NULL){
            tmp->Init(tmp->pinNum);
            smokeStatus = tmp->readStatus(tmp->pinNum);
            printf("state = %d\n", smokeStatus);
            tmp = findDeviceByName(buzzerName, pdeviceHead);
            if(tmp != NULL){
                if( smokeStatus == 0 ){
                    tmp->Init(tmp->pinNum);
                    tmp->open(tmp->pinNum);
                }else{
                    tmp->Init(tmp->pinNum);
                    tmp->close(tmp->pinNum);
                }           
            }
        }
    }
 
    return 0;
}