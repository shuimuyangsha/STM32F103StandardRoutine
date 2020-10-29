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

	SystemInit();   //ϵͳʱ�ӵȳ�ʼ��
	delay_init(72);	//��ʱ��ʼ��
	keyInit();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uartInit(115200);//���ڳ�ʼ��Ϊ115200

	while (1) {
		//mode����0������ģʽ�����°�ť2�����м�¼�Ķ��������°�ť1�л�Ϊ¼��ģʽ?
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
			if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9)) //��ť2 ����
			{
				delay_ms(10);        //������
				if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9))
				{
					run = true; //����
					step = 0;
					delay_ms(500);
				}
			}
			if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8)) //��ť1����
			{
				delay_ms(10);  //������
				if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8))
				{
					LobotSerialServoUnload(ID1); //���ж�����أ���Ϊ����Ť��
					LobotSerialServoUnload(ID2);
					mode = 1;
					step = 0;
					delay_ms(500);
				}
			}
		}
		//mode����1�� ¼��ģʽ�� ���°�ť2����¼�µ�ǰλ�ã����°�ť1�л�������ģʽ
		if (mode == 1)
		{
			if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9)) //��ť2 ������
			{
				delay_ms(10);  //������
				if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9))
				{
					pos[step] = LobotSerialServoReadPosition(ID1); //��ȡ�����ǰλ�ã���¼����
					pos1[step++] = LobotSerialServoReadPosition(ID2);
					if (step == 4)
						step = 0;
					delay_ms(500);
				}
			}
			if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8)) //��ť1 ������
			{
				delay_ms(10); //������
				if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8))
				{
					LobotSerialServoMove(ID1, LobotSerialServoReadPosition(ID1), 200); //��ȡ��ǰλ�ã��˶�����ǰλ�ã�ʵ�ּ�������
					LobotSerialServoMove(ID2, LobotSerialServoReadPosition(ID2), 200);
					//ֱ��ʹ�ü������ص������ֱ���˶���ж������ǰ�����λ�ã����ᱣ���ڵ�ǰλ�á�
					mode = 0;
					delay_ms(500);
				}
			}
		}
	}
}