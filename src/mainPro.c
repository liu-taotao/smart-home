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
    char name[128];
    struct Devices *tmp = NULL;
 
    if (wiringPiSetup () == -1) { 
        fprintf (stdout, "Unable to start wiringPi: %s\n", strerror (errno)) ; 
        return 1 ; 
    }
 
    struct Devices *pdeviceHead = NULL;				                    //定义初始链表头
    pdeviceHead = addBathroomLightToDeviceLink(pdeviceHead);            //“浴室灯”加入设备链表
    pdeviceHead = addBedroomLightToDeviceLink(pdeviceHead);
    pdeviceHead = addRestaurantLightToDeviceLink(pdeviceHead);
    pdeviceHead = addLivingroomLightToDeviceLink(pdeviceHead);
 
    while(1){
        printf("Input:\n");
        scanf("%s",name);
        tmp = findDeviceByName(name, pdeviceHead);
        if(tmp != NULL){
            tmp->Init(tmp->pinNum);         //先初始化
            tmp->open(tmp->pinNum);
        }
    }
    return 0;
}