#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 
#include "remote.h"

 
/************************************************
 ALIENTEKս��STM32������ʵ��28
 ����ң���� ʵ��  
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 �������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/


 int main(void)
 {	 
	u8 key;
	u8 t=0;	
 	u8 *str=0;

	delay_init();	    	 //��ʱ������ʼ��	  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
 	LED_Init();			     //LED�˿ڳ�ʼ��
	LCD_Init();	
	KEY_Init();	 	
	Remote_Init();			//������ճ�ʼ��		 	
 
 	POINT_COLOR=RED;		//��������Ϊ��ɫ 
	LCD_ShowString(30,50,200,16,16,"WarShip STM32");
	LCD_ShowString(30,70,200,16,16,"REMOTE TEST");	
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,110,200,16,16,"2015/1/15");

   	LCD_ShowString(30,130,200,16,16,"KEYVAL:");	
   	LCD_ShowString(30,150,200,16,16,"KEYCNT:");	
   	LCD_ShowString(30,170,200,16,16,"SYMBOL:");	  		 	  		    							  
	while(1)
	{
		key=Remote_Scan();	
		if(key)
		{	 
			LCD_ShowNum(86,130,key,3,16);		//��ʾ��ֵ
			LCD_ShowNum(86,150,RmtCnt,3,16);	//��ʾ��������		  
			switch(key)
			{
				case 0:str="ERROR";break;			   
				case 162:str="POWER";break;	    
				case 98:str="UP";break;	    
				case 2:str="PLAY";break;		 
				case 226:str="ALIENTEK";break;		  
				case 194:str="RIGHT";break;	   
				case 34:str="LEFT";break;		  
				case 224:str="VOL-";break;		  
				case 168:str="DOWN";break;		   
				case 144:str="VOL+";break;		    
				case 104:str="1";break;		  
				case 152:str="2";break;	   
				case 176:str="3";break;	    
				case 48:str="4";break;		    
				case 24:str="5";break;		    
				case 122:str="6";break;		  
				case 16:str="7";break;			   					
				case 56:str="8";break;	 
				case 90:str="9";break;
				case 66:str="0";break;
				case 82:str="DELETE";break;		 
			}
			LCD_Fill(86,170,116+8*8,170+16,WHITE);	//���֮ǰ����ʾ
			LCD_ShowString(86,170,200,16,16,str);	//��ʾSYMBOL
		}else delay_ms(10);	  
		t++;
		if(t==20)
		{
			t=0;
			LED0=!LED0;
		}
	}
}





