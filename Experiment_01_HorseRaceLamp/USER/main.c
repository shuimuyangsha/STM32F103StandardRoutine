#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "extreme3d.h"
 
 
/************************************************
 ALIENTEK战舰STM32开发板实验1
 跑马灯实验 
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/


// int main(void)
// {	
//	delay_init();	    //延时函数初始化	  
//	LED_Init();		  	//初始化与LED连接的硬件接口
//	while(1)
//	{
//		LED0=0;
//		LED1=1;
//		delay_ms(300);	 //延时300ms
//		LED0=1;
//		LED1=0;
//		delay_ms(300);	//延时300ms
//	}
// }
//int DebugLED[2][2];
 int main(void)
 {	
	delay_init();	    //延时函数初始化	  
	LED_Init();		  	//初始化与LED连接的硬件接口
	while(1)
	{
//		if (extreme3d.joystickRotationZ.getJoystickState > 32770) {
//			Compass = (extreme3d.joystickRotationZ.getJoystickState-32768) / 182;
//		}
//		else if (extreme3d.joystickRotationZ.getJoystickState < 32766) {
//			Compass = (extreme3d.joystickRotationZ.getJoystickState + 32768) / 182 ;
//		}
//		else {
//			Compass = 0;
//		}

//		//Compass = extreme3d.joystickRotationZ.getJoystickState/182/3;

//		debugLED0.setState = extreme3d.buttons0.getButtonsState;
//		debugLED1.setState = extreme3d.buttons1.getButtonsState;

//		LED0 = debugLED0.setState >> 7;
//		LED1 = debugLED1.setState >> 7;

//		debugLED0.getState = GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_5);
//		debugLED1.getState = GPIO_ReadOutputDataBit(GPIOE, GPIO_Pin_5);

//		//DebugLED[0][0] = 1;
//		//delay_ms(300);	 //延时300ms

//		//LED1 = debugLED1.setState;
//		//DebugLED[0][0] = 0;
//		//delay_ms(300);	//延时300ms

		debugLED1.setState = 1;
		LED1 = 1;
		delay_ms(300);	 //延时300ms

		debugLED1.setState = 0;
		LED1 = 0;
		delay_ms(300);	//延时300ms
	}
 }

 /**
 *****************下面注视的代码是通过调用库函数来实现IO控制的方法*****************************************
int main(void)
{ 
 
	delay_init();		  //初始化延时函数
	LED_Init();		        //初始化LED端口
	while(1)
	{
			GPIO_ResetBits(GPIOB,GPIO_Pin_5);  //LED0对应引脚GPIOB.5拉低，亮  等同LED0=0;
			GPIO_SetBits(GPIOE,GPIO_Pin_5);   //LED1对应引脚GPIOE.5拉高，灭 等同LED1=1;
			delay_ms(300);  		   //延时300ms
			GPIO_SetBits(GPIOB,GPIO_Pin_5);	   //LED0对应引脚GPIOB.5拉高，灭  等同LED0=1;
			GPIO_ResetBits(GPIOE,GPIO_Pin_5); //LED1对应引脚GPIOE.5拉低，亮 等同LED1=0;
			delay_ms(300);                     //延时300ms
	}
} 
 
 ****************************************************************************************************
 ***/
 

	
/**
*******************下面注释掉的代码是通过 直接操作寄存器 方式实现IO口控制**************************************
int main(void)
{ 
 
	delay_init();		  //初始化延时函数
	LED_Init();		        //初始化LED端口
	while(1)
	{
     GPIOB->BRR=GPIO_Pin_5;//LED0亮
	   GPIOE->BSRR=GPIO_Pin_5;//LED1灭
		 delay_ms(300);
     GPIOB->BSRR=GPIO_Pin_5;//LED0灭
	   GPIOE->BRR=GPIO_Pin_5;//LED1亮
		 delay_ms(300);

	 }
 }
**************************************************************************************************
**/

