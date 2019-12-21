#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 
#include "can.h" 
 
  
/************************************************
 ALIENTEKս��STM32������ʵ��26
 CANͨ��ʵ��
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
	u8 canbuf[8];
	u8 res;
	u8 mode=CAN_Mode_LoopBack;//CAN����ģʽ;CAN_Mode_Normal(0)����ͨģʽ��CAN_Mode_LoopBack(1)������ģʽ

	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
	LCD_Init();			   	//��ʼ��LCD	
	KEY_Init();				//������ʼ��		 	
   
	CAN_Mode_Init(CAN_SJW_1tq,CAN_BS2_8tq,CAN_BS1_9tq,4,CAN_Mode_LoopBack);//CAN��ʼ������ģʽ,������500Kbps    

// 	POINT_COLOR=RED;//��������Ϊ��ɫ 
//	LCD_ShowString(60,50,200,16,16,"WarShip STM32");	
//	LCD_ShowString(60,70,200,16,16,"CAN TEST");	
//	LCD_ShowString(60,90,200,16,16,"ATOM@ALIENTEK");
//	LCD_ShowString(60,110,200,16,16,"2015/1/15");
//	LCD_ShowString(60,130,200,16,16,"LoopBack Mode");	 
//	LCD_ShowString(60,150,200,16,16,"KEY0:Send WK_UP:Mode");//��ʾ��ʾ��Ϣ		
//	POINT_COLOR=BLUE;//��������Ϊ��ɫ	  
//	LCD_ShowString(60,170,200,16,16,"Count:");			//��ʾ��ǰ����ֵ	
//	LCD_ShowString(60,190,200,16,16,"Send Data:");		//��ʾ���͵�����	
//	LCD_ShowString(60,250,200,16,16,"Receive Data:");	//��ʾ���յ�������		
 	while(1)
	{
		
		for(i=0;i<8;i++)
		{
			canbuf[i]=cnt+i;//��䷢�ͻ�����
		}
		res=Can_Send_Msg(canbuf,8);//����8���ֽ� 
		
		
		
//		key=KEY_Scan(0);
//		if(key==KEY0_PRES)//KEY0����,����һ������
//		{
//			for(i=0;i<8;i++)
//			{
//				canbuf[i]=cnt+i;//��䷢�ͻ�����
//				if(i<4)LCD_ShowxNum(60+i*32,210,canbuf[i],3,16,0X80);	//��ʾ����
//				else LCD_ShowxNum(60+(i-4)*32,230,canbuf[i],3,16,0X80);	//��ʾ����
// 			}
//			res=Can_Send_Msg(canbuf,8);//����8���ֽ� 
//			if(res)LCD_ShowString(60+80,190,200,16,16,"Failed");		//��ʾ����ʧ��
//			else LCD_ShowString(60+80,190,200,16,16,"OK    ");	 		//��ʾ���ͳɹ�								   
//		}else if(key==WKUP_PRES)//WK_UP���£��ı�CAN�Ĺ���ģʽ
//		{	   
//			mode=!mode;
//  			CAN_Mode_Init(CAN_SJW_1tq,CAN_BS2_8tq,CAN_BS1_9tq,4,mode);//CAN��ͨģʽ��ʼ��, ������500Kbps 
//			POINT_COLOR=RED;//��������Ϊ��ɫ 
//			if(mode==0)//��ͨģʽ����Ҫ2��������
//			{
//				LCD_ShowString(60,130,200,16,16,"Nnormal Mode ");	    
//			}else //�ػ�ģʽ,һ��������Ϳ��Բ�����.
//			{
// 				LCD_ShowString(60,130,200,16,16,"LoopBack Mode");
//			}
// 			POINT_COLOR=BLUE;//��������Ϊ��ɫ 
//		}		 
//		key=Can_Receive_Msg(canbuf);
//		if(key)//���յ�������
//		{			
//			LCD_Fill(60,270,130,310,WHITE);//���֮ǰ����ʾ
// 			for(i=0;i<key;i++)
//			{									    
//				if(i<4)LCD_ShowxNum(60+i*32,270,canbuf[i],3,16,0X80);	//��ʾ����
//				else LCD_ShowxNum(60+(i-4)*32,290,canbuf[i],3,16,0X80);	//��ʾ����
// 			}
//		}
//		t++; 
		delay_ms(50);
//		if(t==20)
//		{
//			LED0=!LED0;//��ʾϵͳ��������	
//			t=0;
//			cnt++;
//			LCD_ShowxNum(60+48,170,cnt,3,16,0X80);	//��ʾ����
//		}		   
	}
}



