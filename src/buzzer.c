#include "controlDevice.h"			//自定义设备类的文件
 
int buzzerInit(int pinNum)
{
	pinMode(pinNum,OUTPUT);						//配置引脚为输出模式
	digitalWrite(pinNum,HIGH);					//引脚置高电平，蜂鸣器关闭
}
 
int buzzerOpen(int pinNum)
{
	digitalWrite(pinNum,LOW);					//引脚置低电平，蜂鸣器开启
}
 
int buzzerClose(int pinNum)
{
	digitalWrite(pinNum,HIGH);					//引脚置高电平，蜂鸣器关闭
}
 
struct Devices buzzer = {						//定义蜂鸣器（对象）
	.deviceName = "buzzer",						//名字
	.pinNum = 9,								//香橙派 9号(wpi)引脚
	.Init = buzzerInit,							//指定初始化函数
	.open = buzzerOpen,							//指定“开启蜂鸣器”函数
	.close = buzzerClose,						//指定“关闭蜂鸣器”函数
};
 
 
struct Devices* addBuzzerToDeviceLink(struct Devices *phead)		//蜂鸣器（对象）加入设备链表函数
{
	if (phead == NULL) {
		return &buzzer;
	} else {
		buzzer.next = phead;
		phead = &buzzer;
		return phead;
	}
}