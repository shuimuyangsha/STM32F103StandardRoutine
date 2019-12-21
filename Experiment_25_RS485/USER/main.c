#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 
#include "rs485.h"
 
/************************************************
 ALIENTEKս��STM32������ʵ��25
 485ͨ��ʵ�� 
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/

 				 	
 int main(void)
 {	 
	u8 key;
	u8 i=0,t=0;
	u8 cnt=0;
	u8 rs485buf[5]; 
	 
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
	LCD_Init();			   	//��ʼ��LCD 	
	KEY_Init();				//������ʼ��		 	 
	RS485_Init(9600);	//��ʼ��RS485
 	POINT_COLOR=RED;//��������Ϊ��ɫ 
	LCD_ShowString(30,50,200,16,16,"WarShip STM32");
	LCD_ShowString(30,70,200,16,16,"RS485 TEST");	
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,110,200,16,16,"2015/1/15");	
	LCD_ShowString(30,130,200,16,16,"KEY0:Send");	//��ʾ��ʾ��Ϣ		
 
 	POINT_COLOR=BLUE;//��������Ϊ��ɫ	  
	LCD_ShowString(30,150,200,16,16,"Count:");			//��ʾ��ǰ����ֵ	
	LCD_ShowString(30,170,200,16,16,"Send Data:");		//��ʾ���͵�����	
	LCD_ShowString(30,210,200,16,16,"Receive Data:");	//��ʾ���յ�������		
 									  
	while(1)
	{
		key=KEY_Scan(0);
		if(key==KEY0_PRES)//KEY0����,����һ������
		{
			for(i=0;i<5;i++)
			{
				rs485buf[i]=cnt+i;//��䷢�ͻ�����
				LCD_ShowxNum(30+i*32,190,rs485buf[i],3,16,0X80);	//��ʾ����
 			}
			RS485_Send_Data(rs485buf,5);//����5���ֽ� 									   
		}		 
		RS485_Receive_Data(rs485buf,&key);
		if(key)//���յ�������
		{
			if(key>5)key=5;//�����5������.
 			for(i=0;i<key;i++)LCD_ShowxNum(30+i*32,230,rs485buf[i],3,16,0X80);	//��ʾ����
 		}
		t++; 
		delay_ms(10);
		if(t==20)
		{
			LED0=!LED0;//��ʾϵͳ��������	
			t=0;
			cnt++;
			LCD_ShowxNum(30+48,150,cnt,3,16,0X80);	//��ʾ����
		}		   
	} 
}


