#include "sys.h"
#include "usart.h"	  
////////////////////////////////////////////////////////////////////////////////// 	 
//���ʹ��ucos,����������ͷ�ļ�����.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos ʹ��	  
#endif
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//����1��ʼ��		   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/8/18
//�汾��V1.5
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved
//********************************************************************************
//V1.3�޸�˵�� 
//֧����Ӧ��ͬƵ���µĴ��ڲ���������.
//�����˶�printf��֧��
//�����˴��ڽ��������.
//������printf��һ���ַ���ʧ��bug
//V1.4�޸�˵��
//1,�޸Ĵ��ڳ�ʼ��IO��bug
//2,�޸���USART_RX_STA,ʹ�ô����������ֽ���Ϊ2��14�η�
//3,������USART_REC_LEN,���ڶ��崮�����������յ��ֽ���(������2��14�η�)
//4,�޸���EN_USART1_RX��ʹ�ܷ�ʽ
//V1.5�޸�˵��
//1,�����˶�UCOSII��֧��
////////////////////////////////////////////////////////////////////////////////// 	  
 

//////////////////////////////////////////////////////////////////
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
_sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 

/*ʹ��microLib�ķ���*/
 /* 
int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (uint8_t) ch);

	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {}	
   
    return ch;
}
int GetKey (void)  { 

    while (!(USART1->SR & USART_FLAG_RXNE));

    return ((int)(USART1->DR & 0x1FF));
}
*/
 
#if EN_USART1_RX   //���ʹ���˽���
//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
u8 USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART_RX_STA=0;       //����״̬���	  
  
void uart_init(u32 bound){
  //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��
  
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9
   
  //USART1_RX	  GPIOA.10��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10  

  //Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  USART_Init(USART1, &USART_InitStructure); //��ʼ������1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���1 

}

//void USART1_IRQHandler(void)                	//����1�жϷ������
//{
//	u8 Res;
//#if SYSTEM_SUPPORT_OS 		//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
//	OSIntEnter();    
//#endif
//	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
//	{
//		Res =USART_ReceiveData(USART1);	//��ȡ���յ�������
//		
//		if((USART_RX_STA&0x8000)==0)//����δ���
//		{
//			if(USART_RX_STA&0x4000)//���յ���0x0d
//			{
//				if(Res!=0x0a)USART_RX_STA=0;//���մ���,���¿�ʼ
//				else USART_RX_STA|=0x8000;	//��������� 
//			}
//			else //��û�յ�0X0D
//			{	
//				if(Res==0x0d)USART_RX_STA|=0x4000;
//				else
//				{
//					USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
//					USART_RX_STA++;
//					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
//				}		 
//			}
//		}   		 
//     } 
//#if SYSTEM_SUPPORT_OS 	//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
//	OSIntExit();  											 
//#endif
//} 
//#endif	

#define USART1_DATA_LENGTH           10
char Usart1_New_Data_sing = 0;
uint16_t Usart1_Recv_Status = 0;                                             //���ڽ������ݱ�־

char usart1_recn_buf[10] = { 0 };                                              //��ʱ�洢���յ�������

int Is_get_pairing_info = 0;
char string1[50];

int Is_get_openIrLed = 0;
char string2[50];

int charging_pileID = 0;
int electrode_contact_state = 0;
char string3[50];


/************************************************************************
��������: void UART4_IRQHandler(void)
��������: �����жϷ����� (�Զ����)
�������:
�� �� ֵ:
************************************************************************/
void USART1_IRQHandler(void)
{
	unsigned char res;
	unsigned char i, sum;
	////	int kLengthPosition = 2;
	////	static unsigned char _data_length = 7;	//The shortest length //55 FF 07(length) 01(version) 09(sum) FF FE

#if SYSTEM_SUPPORT_OS 		//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
	OSIntEnter();
#endif
	if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		res = USART_ReceiveData(USART1);
		if ((Usart1_Recv_Status == 0 && res != 0x55) || (Usart1_Recv_Status == 1 && res != 0xFF)
			|| (Usart1_Recv_Status == USART1_DATA_LENGTH - 2 && res != 0xFF)
			|| (Usart1_Recv_Status == USART1_DATA_LENGTH - 1 && res != 0xFE))
		{
			Usart1_Recv_Status = 0;
			if (res == 0x55)
			{
				usart1_recn_buf[Usart1_Recv_Status] = res;
				++Usart1_Recv_Status;
			}
			goto end;
		}
		if (Usart1_Recv_Status == USART1_DATA_LENGTH - 3)
		{
			sum = 0;
			for (i = 2; i < USART1_DATA_LENGTH - 3; ++i)
			{
				sum += usart1_recn_buf[i];
			}
			if (res != sum)
			{
				Usart1_Recv_Status = 0;
				if (res == 0x55)
				{
					usart1_recn_buf[Usart1_Recv_Status] = res;
					++Usart1_Recv_Status;
				}
				goto end;
			}
		}
		if ((Usart1_Recv_Status & UART1_RECV_FRAME_DONE_FLAG) == 0)
		{
			if (Usart1_Recv_Status < USART1_DATA_LENGTH)
			{
				usart1_recn_buf[Usart1_Recv_Status] = res;
				++Usart1_Recv_Status;
				if (Usart1_Recv_Status == USART1_DATA_LENGTH)
				{
					Usart1_Recv_Status |= UART1_RECV_FRAME_DONE_FLAG; // indicate one frame receive
					Usart1_New_Data_sing = 1;       //��ǽ������
					Usart1_Recv_Status = 0;

					switch (usart1_recn_buf[2])
					{
					case 0x01:
						Is_get_pairing_info = usart1_recn_buf[4];
						if (Is_get_pairing_info == 0x01) {
							memset(string1, 0, sizeof(string1));
							strcpy(string1, "Received pairing request��"); /*�����鸳�ַ���*/

						}
						break;
					case 0x02:
						Is_get_openIrLed = usart1_recn_buf[4];

						if (Is_get_openIrLed == 0x03) {
							memset(string2, 0, sizeof(string2));
							strcpy(string2, "Light on command received..."); /*�����鸳�ַ���*/

						}
						else if(Is_get_openIrLed == 0x04) {
							memset(string2, 0, sizeof(string2));
							strcpy(string2, "Light off command received..."); /*�����鸳�ַ���*/
						}
						break;
					case 0x03:
						charging_pileID = usart1_recn_buf[3];
						electrode_contact_state = usart1_recn_buf[4];

						if (electrode_contact_state == 0x04) {
							memset(string3, 0, sizeof(string3));
							strcpy(string3, "Approaching the charging pile..."); /*�����鸳�ַ���*/
							
						}
						else if(electrode_contact_state == 0x02) {
							memset(string3, 0, sizeof(string3));
							strcpy(string3, "In charge..."); /*�����鸳�ַ���*/
						}
						break;
					case 0x04:

						break;
					case 0xF2:
						break;
					default:
						break;

					}
				}
			}
			else // receive more bytes than the frame length, but the flag bit is not set, there must be something bad.
			{
				Usart1_Recv_Status = 0;
				if (res == 0x55)
				{
					usart1_recn_buf[Usart1_Recv_Status] = res;
					++Usart1_Recv_Status;
				}
			}
		}
	}
end:;
#if SYSTEM_SUPPORT_OS 	//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
	OSIntExit();
#endif
}
#endif

