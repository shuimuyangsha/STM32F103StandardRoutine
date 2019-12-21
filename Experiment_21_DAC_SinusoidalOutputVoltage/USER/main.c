#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 
#include "rtc.h" 
#include "wkup.h"
#include "adc.h"	 
#include "dac.h"
#include "timer.h"
#include "usmart.h"

 
/************************************************
 ALIENTEKս��STM32������ʵ��21
 PWM DAC ʵ��  
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 �������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/



//���������ѹ
//vol:0~330,����0~3.3V
void PWM_DAC_Set(u16 vol)
{
	float temp=vol;
	temp/=100;
	temp=temp*256/3.3;
	TIM_SetCompare1(TIM1,temp);
}
 int main(void)
 {	 
	u16 adcx;
	float temp;
 	u8 t=0;	 
	u16 pwmval=0;
	u8 key;
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
	KEY_Init();				  //KEY��ʼ��
 	LED_Init();			     //LED�˿ڳ�ʼ��
	usmart_dev.init(72);	//��ʼ��USMART	
	LCD_Init();			 	 //LCD��ʼ��
  Adc_Init();		  		//ADC��ʼ��
	TIM1_PWM_Init(255,0);	//TIM1 PWM��ʼ��, Fpwm=72M/256=281.25Khz.
  TIM_SetCompare1(TIM1,100);//��ʼֵΪ0	
	     

 	POINT_COLOR=RED;//��������Ϊ��ɫ 
	LCD_ShowString(60,50,200,16,16,"WarShip STM32");	
	LCD_ShowString(60,70,200,16,16,"PWM DAC TEST");	
	LCD_ShowString(60,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(60,110,200,16,16,"2015/1/15");	
	LCD_ShowString(60,130,200,16,16,"WK_UP:+  KEY1:-");	
	//��ʾ��ʾ��Ϣ											      
	POINT_COLOR=BLUE;//��������Ϊ��ɫ
	LCD_ShowString(60,150,200,16,16,"PWM VAL:");	      
	LCD_ShowString(60,170,200,16,16,"DAC VOL:0.000V");	      
	LCD_ShowString(60,190,200,16,16,"ADC VOL:0.000V");
	
	TIM_SetCompare1(TIM1,pwmval);//��ʼֵ	    	      
	while(1)
	{
		t++;
		key=KEY_Scan(0);			  
		if(key==WKUP_PRES)
		{		 
			if(pwmval<250)pwmval+=10;
			TIM_SetCompare1(TIM1,pwmval); 		//���
		}else if(key==KEY1_PRES)	
		{
			if(pwmval>10)pwmval-=10;
			else pwmval=0;
			TIM_SetCompare1(TIM1,pwmval); 		//���
		}	 
		if(t==10||key==KEY1_PRES||key==WKUP_PRES) 		//WKUP/KEY1������,���߶�ʱʱ�䵽��
		{	  
			adcx=TIM_GetCapture1(TIM1);
			LCD_ShowxNum(124,150,adcx,4,16,0);     	//��ʾDAC�Ĵ���ֵ
			temp=(float)adcx*(3.3/256);				//�õ�DAC��ѹֵ
			adcx=temp;
 			LCD_ShowxNum(124,170,temp,1,16,0);     	//��ʾ��ѹֵ��������
 			temp-=adcx;
			temp*=1000;
			LCD_ShowxNum(140,170,temp,3,16,0x80); 	//��ʾ��ѹֵ��С������
 			adcx=Get_Adc_Average(ADC_Channel_1,20);  		//�õ�ADCת��ֵ	  
			temp=(float)adcx*(3.3/4096);			//�õ�ADC��ѹֵ
			adcx=temp;
 			LCD_ShowxNum(124,190,temp,1,16,0);     	//��ʾ��ѹֵ��������
 			temp-=adcx;
			temp*=1000;
			LCD_ShowxNum(140,190,temp,3,16,0x80); 	//��ʾ��ѹֵ��С������
			t=0;
			LED0=!LED0;	   
		}	    
		delay_ms(10);	

	}
 }
