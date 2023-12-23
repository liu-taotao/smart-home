#include "controlDevice.h"			//自定义设备类的文件
 
int restaurantLightInit(int pinNum)         //C语言必须要传参，JAVA不用，可直接访问变量的值
{
	pinMode(pinNum,OUTPUT);					//配置引脚为输出模式
	digitalWrite(pinNum,HIGH);				//引脚置高电平，断开继电器
}
 
int restaurantLightOpen(int pinNum)
{
	digitalWrite(pinNum,LOW);				//引脚置低电平，闭合继电器
}
 
int restaurantLightClose(int pinNum)
{
	digitalWrite(pinNum,HIGH);				//引脚置高电平，断开继电器
}
 
int restaurantLightStatus(int status)
{
	
}
 
struct Devices restaurantLight = {			//定义餐厅灯（对象）
	.deviceName = "restaurantLight",		//名字
	.pinNum = 13,							//香橙派 13号(wPi)引脚
	.Init = restaurantLightInit,			//指定初始化函数
	.open = restaurantLightOpen,			//指定“打开灯”函数
	.close = restaurantLightClose,			//指定“关闭灯”函数
    .changeStatus = restaurantLightStatus
};
 
struct Devices* addRestaurantLightToDeviceLink(struct Devices *phead)		//餐厅灯（对象）加入设备链表函数
{
	if (phead == NULL) {
		return &restaurantLight;
	} else {
		restaurantLight.next = phead;  //以前的头变成.next
		phead = &restaurantLight;      //更新头
		return phead;
	}
}