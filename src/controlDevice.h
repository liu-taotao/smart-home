#include <wiringPi.h>					//wiringPi库
#include <stdio.h>
#include <stdlib.h>
 
struct Devices                          //设备类
{
    char deviceName[128];               //设备名
    int status;                         //状态
    int pinNum;							//引脚号
 
    int (*Init)(int pinNum);			//“初始化设备”函数指针
	int (*open)(int pinNum);			//“打开设备”函数指针
	int (*close)(int pinNum);			//“关闭设备”函数指针
    int (*readStatus)(int pinNum);		//“读取设备状态”函数指针  为火灾报警器准备
	int (*changeStatus)(int status);	//“改变设备状态”函数指针
 
    struct Devices *next;
};
 
struct Devices* addBathroomLightToDeviceLink(struct Devices *phead);		//“浴室灯”加入设备链表函数声明
struct Devices* addBedroomLightToDeviceLink(struct Devices *phead);	        //“卧室灯”加入设备链表函数声明
struct Devices* addRestaurantLightToDeviceLink(struct Devices *phead);		//“餐厅灯”加入设备链表函数声明
struct Devices* addLivingroomLightToDeviceLink(struct Devices *phead);		//“客厅灯”加入设备链表函数声明
struct Devices* addSmokeAlarmToDeviceLink(struct Devices *phead);           //“烟雾报警器”加入设备链表函数声明
struct Devices* addBuzzerToDeviceLink(struct Devices *phead);		        //“蜂鸣器”加入设备链表函数声明