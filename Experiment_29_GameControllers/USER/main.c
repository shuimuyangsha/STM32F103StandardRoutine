#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"
#include "joypad.h" 

 
/************************************************
 ALIENTEK战舰STM32开发板实验29
 游戏手柄 实验   
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/


const u8*JOYPAD_SYMBOL_TBL[8]=
{"Right","Left","Down","Up","Start","Select","A","B"};//手柄按键符号定义
 int main(void)
 {	 
	u8 key;
	u8 t=0,i=0;	
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(115200);	 	//串口初始化为115200
	LED_Init();		  		//初始化与LED连接的硬件接口
	LCD_Init();			   	//初始化LCD 	
	JOYPAD_Init();			//手柄初始化
 	POINT_COLOR=RED;//设置字体为红色 
	LCD_ShowString(30,50,200,16,16,"WarShip STM32");	
	LCD_ShowString(30,70,200,16,16,"JOYPAD TEST");	
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,110,200,16,16,"2015/1/16");
  LCD_ShowString(30,130,200,16,16,"KEYVAL:");	      
  LCD_ShowString(30,150,200,16,16,"SYMBOL:");	      
 	POINT_COLOR=BLUE;//设置字体为红色 
	while(1)
	{
		key=JOYPAD_Read();
		if(key)
		{
			LCD_ShowNum(116,130,key,3,16);//显示键值
			for(i=0;i<8;i++)
			{
				if(key&(0X80>>i))
				{
					LCD_Fill(30+56,150,30+56+48,150+16,WHITE);//清除之前的显示
					LCD_ShowString(30+56,150,200,16,16,(u8*)JOYPAD_SYMBOL_TBL[i]);//显示符号
				}		
			}		    
		}
	 	delay_ms(10);
		t++;
		if(t==20)
		{
			t=0;
			LED0=!LED0;
		}
	}
}




