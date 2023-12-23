#include "controlDevice.h"			//自定义设备类的文件
 
int bathroomLightInit(int pinNum)           //C语言必须要传参，JAVA不用，可直接访问变量的值
{
	pinMode(pinNum,OUTPUT);					//配置引脚为输出模式
	digitalWrite(pinNum,HIGH);				//引脚置高电平，断开继电器
}
 
int bathroomLightOpen(int pinNum)
{
	digitalWrite(pinNum,LOW);				//引脚置低电平，闭合继电器
}
 
int bathroomLightClose(int pinNum)
{
	digitalWrite(pinNum,HIGH);				//引脚置高电平，断开继电器
}
 
int bathroomLightStatus(int status)
{
	
}
 
struct Devices bathroomLight = {			//定义浴室灯（对象）
	.deviceName = "bathroomLight",			//名字
	.pinNum = 2,							//香橙派 2号(wPi)引脚
	.Init = bathroomLightInit,				//指定初始化函数
	.open = bathroomLightOpen,				//指定“打开灯”函数
	.close = bathroomLightClose,			//指定“关闭灯”函数
    .changeStatus = bathroomLightStatus
};
 
struct Devices* addBathroomLightToDeviceLink(struct Devices *phead)		//浴室灯（对象）加入设备链表函数
{
	if(phead == NULL){
		return &bathroomLight;
	}else{
		bathroomLight.next = phead;  //以前的头变成.next
		phead = &bathroomLight;      //更新头
		return phead;
	}
}