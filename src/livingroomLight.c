#include "controlDevice.h"			//自定义设备类的文件
 
int livingroomLightInit(int pinNum)         //C语言必须要传参，JAVA不用，可直接访问变量的值
{
	pinMode(pinNum,OUTPUT);					//配置引脚为输出模式
	digitalWrite(pinNum,HIGH);				//引脚置高电平，断开继电器
}
 
int livingroomLightOpen(int pinNum)
{
	digitalWrite(pinNum,LOW);				//引脚置低电平，闭合继电器
}
 
int livingroomLightClose(int pinNum)
{
	digitalWrite(pinNum,HIGH);				//引脚置高电平，断开继电器
}
 
int livingroomLightStatus(int status)
{
	
}
 
struct Devices livingroomLight = {			//定义客厅灯（对象）
	.deviceName = "livingroomLight",		//名字
	.pinNum = 16,							//香橙派 16号(wPi)引脚
	.Init = livingroomLightInit,			//指定初始化函数
	.open = livingroomLightOpen,			//指定“打开灯”函数
	.close = livingroomLightClose,			//指定“关闭灯”函数
    .changeStatus = livingroomLightStatus
};
 
struct Devices* addLivingroomLightToDeviceLink(struct Devices *phead)		//客厅灯（对象）加入设备链表函数
{
	if (phead == NULL) {
		return &livingroomLight;
	} else {
		livingroomLight.next = phead;  //以前的头变成.next
		phead = &livingroomLight;      //更新头
		return phead;
	}
}