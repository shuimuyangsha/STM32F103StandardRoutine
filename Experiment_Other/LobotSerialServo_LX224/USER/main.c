#include "delay.h"
#include "uart.h"
#include "LobotSerialServo.h"
#include "bool.h"

#define ID1 1
#define ID2 2

void keyInit()
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

int main(void)
{
	bool run = false;
	char step = 0;
	char mode = 0;
	int pos[4] = { 100, 200, 300, 400 };
	int pos1[4] = { 100, 200, 300, 400 };

	SystemInit();   //系统时钟等初始化
	delay_init(72);	//延时初始化
	keyInit();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uartInit(115200);//串口初始化为115200

	while (1) {
		//mode等于0，运行模式，按下按钮2，运行记录的动作，按下按钮1切换为录制模式?
		if (mode == 0)
		{
			if (run)
			{
				LobotSerialServoMove(ID1, pos[step], 500);
				LobotSerialServoMove(ID2, pos1[step++], 500);
				if (step == 4)
				{
					step = 0;
					run = false;
				}
				delay_ms(1000);
			}
			if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9)) //按钮2 按下
			{
				delay_ms(10);        //简单消抖
				if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9))
				{
					run = true; //运行
					step = 0;
					delay_ms(500);
				}
			}
			if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8)) //按钮1按下
			{
				delay_ms(10);  //简单消抖
				if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8))
				{
					LobotSerialServoUnload(ID1); //舵机卸载力矩，变为可以扭动
					LobotSerialServoUnload(ID2);
					mode = 1;
					step = 0;
					delay_ms(500);
				}
			}
		}
		//mode等于1， 录制模式， 按下按钮2，记录下当前位置，按下按钮1切换回运行模式
		if (mode == 1)
		{
			if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9)) //按钮2 被按下
			{
				delay_ms(10);  //简单消抖
				if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9))
				{
					pos[step] = LobotSerialServoReadPosition(ID1); //读取舵机当前位置，记录下来
					pos1[step++] = LobotSerialServoReadPosition(ID2);
					if (step == 4)
						step = 0;
					delay_ms(500);
				}
			}
			if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8)) //按钮1 被按下
			{
				delay_ms(10); //简单消抖
				if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8))
				{
					LobotSerialServoMove(ID1, LobotSerialServoReadPosition(ID1), 200); //读取当前位置，运动到当前位置，实现加载力矩
					LobotSerialServoMove(ID2, LobotSerialServoReadPosition(ID2), 200);
					//直接使用加载力矩的命令，会直接运动到卸载力矩前的最后位置，不会保持在当前位置。
					mode = 0;
					delay_ms(500);
				}
			}
		}
	}
}