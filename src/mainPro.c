#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "controlDevice.h"
 
struct Devices* findDeviceByName(char *name, struct Devices *phead)
{
    struct Devices *tmp = phead;
    if (phead == NULL) {
        return NULL;
    } else {
        while (tmp != NULL) {
            if (strcmp(tmp->deviceName, name)==0) {
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
 
    if (wiringPiSetup() == -1) {  // 初始化wiringPi库，如果初始化失败则打印
        fprintf (stdout, "Unable to start wiringPi: %s\n", strerror(errno)) ; 
        return 1 ; 
    }
 
    struct Devices *pdeviceHead = NULL;				                    //定义初始链表头
    pdeviceHead = addBathroomLightToDeviceLink(pdeviceHead);            //“浴室灯”加入设备链表
    pdeviceHead = addBedroomLightToDeviceLink(pdeviceHead);
    pdeviceHead = addRestaurantLightToDeviceLink(pdeviceHead);
    pdeviceHead = addLivingroomLightToDeviceLink(pdeviceHead);
 
    while (1) {
        printf("Input:\n");
        scanf("%s", name);
        tmp = findDeviceByName(name, pdeviceHead); // 在设备链表中根据名称查找设备，返回设备指针
        if (tmp != NULL) {
            tmp->Init(tmp->pinNum);         //先初始化
            tmp->open(tmp->pinNum);
            sleep(4);
            tmp->close(tmp->pinNum);
        }
    }
    return 0;
}