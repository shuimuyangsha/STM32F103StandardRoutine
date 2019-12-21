#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "beep.h"
 
/************************************************
 ALIENTEK战舰STM32开发板实验3
 按键输入实验  
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/


 int main(void)
 {
 	vu8 key=0;	
	delay_init();	    	 //延时函数初始化	  
 	LED_Init();			     //LED端口初始化
	KEY_Init();          //初始化与按键连接的硬件接口
	BEEP_Init();         	//初始化蜂鸣器端口
	uart_init(115200);    	//串口波特率设置
	LED0=0;					//先点亮红灯
	while(1)
	{
 		key=KEY_Scan(0);	//得到键值
	   	if(key)
		{						   
			switch(key)
			{				 
				case WKUP_PRES:	//控制蜂鸣器
					BEEP=!BEEP;
					break;
				case KEY2_PRES:	//控制LED0翻转
					LED0=!LED0;
					printf("float_num的值为\r\n"); //串口打印结果
					break;
				case KEY1_PRES:	//控制LED1翻转	 
					LED1=!LED1;
					break;
				case KEY0_PRES:	//同时控制LED0,LED1翻转 
					LED0=!LED0;
					LED1=!LED1;
					break;
			}
		}else delay_ms(10); 
	}	 
}

