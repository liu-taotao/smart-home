#include "controlDevice.h"
 
int bedroomLightInit(int pinNum)            //C语言必须要传参，JAVA不用，可直接访问变量的值
{
	pinMode(pinNum,OUTPUT);					//配置引脚为输出模式
	digitalWrite(pinNum,HIGH);				//引脚置高电平，断开继电器
}
 
int bedroomLightOpen(int pinNum)
{
	digitalWrite(pinNum,LOW);				//引脚置低电平，闭合继电器
}
 
int bedroomLightClose(int pinNum)
{
	digitalWrite(pinNum,HIGH);				//引脚置高电平，断开继电器
}
 
int bedroomLightStatus(int status)
{
	
}
 
struct Devices bedroomLight = {			//定义卧室灯（对象）
	.deviceName = "bedroomLight",		//名字
	.pinNum = 8,						//香橙派 8号(wPi)引脚
	.Init = bedroomLightInit,			//指定初始化函数
	.open = bedroomLightOpen,			//指定“打开灯”函数
	.close = bedroomLightClose,			//指定“关闭灯”函数
    .changeStatus = bedroomLightStatus
};
 
struct Devices* addBedroomLightToDeviceLink(struct Devices *phead)		//卧室灯（对象）加入设备链表函数
{
	if(phead == NULL){
		return &bedroomLight;
	}else{
		bedroomLight.next = phead;  //以前的头变成.next
		phead = &bedroomLight;      //更新头
		return phead;
	}
}