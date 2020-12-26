#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "extreme3d.h"
#include "math.h"

#define NUM_POINT 500
float debugX[NUM_POINT];
float debugY[NUM_POINT];

int i;

float x;
float step = 0;
 int main(void)
 {	
	delay_init();	    //延时函数初始化	  
	LED_Init();		  	//初始化与LED连接的硬件接口
	while(1)
	{
		for (i = 0.1,x=0; i < NUM_POINT;i++,x += 0.1) {
			//debugX[i] = i;

			//debugY[i] = i;

			debugX[i] = x;

			debugY[i] = 5 * sin(x);
		}

		//step += 0.2;
		//if (step > 10) { step = 0; }
		//delay_ms(100);


		//debugX[0] = debugY[0] = 10;
		//debugX[1] = debugY[1] = 20;
		//debugX[2] = debugY[2] = 30;
		//debugX[3] = debugY[3] = 40;
		//debugX[4] = debugY[4] = 50;

		//LED0=0;
		//LED1=1;
		//delay_ms(300);	 //延时300ms
		//LED0=1;
		//LED1=0;
		//delay_ms(300);	//延时300ms
	}
 }
