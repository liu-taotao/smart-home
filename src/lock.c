#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <signal.h>
#include <wiringPi.h>
#include "controlDevice.h"

static int count = 0;
int angle;
int lockInit(int pinNum)         
{
	pinMode(pinNum,OUTPUT);					
	digitalWrite(pinNum,HIGH);				
 	system("sudo ./sg90/a.out 3");
}
 
int lockOpen(int pinNum)
{
   system("sudo ./sg90/a.out 1");
}
 
int lockClose(int pinNum)
{
   system("sudo ./sg90/a.out 3");

} 
int lockStatus(int status)
{
	
}
 
struct Devices lock = {			//定义客厅灯（对象）
	.deviceName = "lock",		//名字
	.pinNum = 10,							//香橙派 16号(wPi)引脚
	.Init = lockInit,			//指定初始化函数
	.open = lockOpen,			//指定“打开灯”函数
	.close = lockClose,			//指定“关闭灯”函数
  	.changeStatus = lockStatus
};
 
struct Devices* addLockToDeviceLink(struct Devices *phead)		//客厅灯（对象）加入设备链表函数
{
	if(phead == NULL){
		return &lock;
	}else{
		lock.next = phead;  //以前的头变成.next
		phead = &lock;      //更新头
		return phead;
	}
}
