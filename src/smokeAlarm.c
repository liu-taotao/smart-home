#include "controlDevice.h"			        //自定义设备类的文件
 
int smokeAlarmInit(int pinNum)              //C语言必须要传参，JAVA不用，可直接访问变量的值
{
	pinMode(pinNum,INPUT);				    //配置引脚为输入模式
	//digitalWrite(pinNum,HIGH);			//引脚置高电平，断开继电器
}
 
int smokeAlarmReadStatus(int pinNum)
{
	return digitalRead(pinNum);
}
 
int smokeAlarmStatus(int status)
{
	
}
 
struct Devices smokeAlarm = {			//定义烟雾报警器（对象）
	.deviceName = "smokeAlarm",			//名字
	.pinNum = 6,						//香橙派 6号(wPi)引脚
	.Init = smokeAlarmInit,				//指定初始化函数
    .readStatus = smokeAlarmReadStatus,
    .changeStatus = smokeAlarmStatus
};
 
struct Devices* addSmokeAlarmToDeviceLink(struct Devices *phead)		//烟雾报警器（对象）加入设备链表函数
{
	if (phead == NULL) {
		return &smokeAlarm;
	} else {
		smokeAlarm.next = phead;  //以前的头变成.next
		phead = &smokeAlarm;      //更新头
		return phead;
	}
}