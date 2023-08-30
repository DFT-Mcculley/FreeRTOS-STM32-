#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "FreeRTOS.h"
#include "task.h"
#include "key.h"
#include "exti.h"
#include "timer.h"
#include "list.h"


//�������������
//�������ȼ�
#define START_TASK_PRIO		1
//�����ջ��С	
#define START_STK_SIZE 		128  
//������
TaskHandle_t StartTask_Handler;
//������
void Start_Task(void *pvParameters);//��������


//KEY������
//�������ȼ�
#define List_TASK_PRIO		2
//�����ջ��С	
#define List_STK_SIZE 		128
//������
TaskHandle_t List_Task_Handler;
//������
void List_Task(void *pvParameters);//��������


//����һ���б�������б���
List_t TestList;
ListItem_t ListItem1,ListItem2,ListItem3;


int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//����ϵͳ�ж����ȼ�����4
	delay_init(168);		//��ʼ����ʱ����
	uart_init(115200);     	//��ʼ������
	LED_Init();		        //��ʼ��LED�˿�
	//EXTIX_Init();
//	TIM3_Int_Init(10000-1,8400-1);
//	TIM5_Int_Init(10000-1,8400-1);
	xTaskCreate((TaskFunction_t )Start_Task,            //������
							(const char*    )"Start_Task",          //��������
							(uint16_t       )START_STK_SIZE,        //�����ջ��С
							(void*          )NULL,                  //���ݸ��������Ĳ���
							(UBaseType_t    )START_TASK_PRIO,       //�������ȼ�
							(TaskHandle_t*  )&StartTask_Handler);   //������             
	vTaskStartScheduler();          //�����������
}


//���������������
void Start_Task(void *pvParameters)//�������ݣ���Ϊ���񴴽��������ڴ��������������ֻ��ִ��һ�μ���ɾ��
{
    taskENTER_CRITICAL();           //�����ٽ��� 
    //����KEY����
    xTaskCreate((TaskFunction_t )List_Task,     	
                (const char*    )"List_Task",   	
                (uint16_t       )List_STK_SIZE, 
                (void*          )NULL,				
                (UBaseType_t    )List_TASK_PRIO,	
                (TaskHandle_t*  )&List_Task_Handler);   
    vTaskDelete(StartTask_Handler); //ɾ����ʼ���� //vTaskDelete(NULL);//ɾ���Լ� 
    taskEXIT_CRITICAL();            //�˳��ٽ���
}



//�б�������
void List_Task(void *pvParameters)
{
		//��ʼ��
		vListInitialise(&TestList);
		vListInitialiseItem(&ListItem1);
		vListInitialiseItem(&ListItem2);
		vListInitialiseItem(&ListItem3);

		ListItem1.xItemValue = 40;
		ListItem2.xItemValue = 60;
		ListItem3.xItemValue = 50;
		
		printf("/*******************�б���б����ַ*******************/\r\n");
		printf("��Ŀ                              ��ַ				    \r\n");
		printf("TestList                          %#x					\r\n",(int)&TestList);//�б�ĵ�ַ
		printf("TestList->pxIndex                 %#x					\r\n",(int)TestList.pxIndex);//��ǰ����ָ���ַ
		printf("TestList->xListEnd                %#x					\r\n",(int)(&TestList.xListEnd));//�����б��ַ
		printf("ListItem1                         %#x					\r\n",(int)&ListItem1);//��һ���б����ַ
		printf("ListItem2                         %#x					\r\n",(int)&ListItem2);//��һ���б����ַ
		printf("ListItem3                         %#x					\r\n",(int)&ListItem3);//��һ���б����ַ
		printf("/************************����**************************/\r\n");
		
		//����
		vListInsert(&TestList,&ListItem1);
		printf("/******************����б���ListItem1*****************/\r\n");
		printf("��Ŀ                              ��ַ				    \r\n");
		printf("TestList->xListEnd->pxNext        %#x					\r\n",(int)(TestList.xListEnd.pxNext));
		printf("ListItem1->pxNext                 %#x					\r\n",(int)(ListItem1.pxNext));
		printf("/*******************ǰ�������ӷָ���********************/\r\n");
		printf("TestList->xListEnd->pxPrevious    %#x					\r\n",(int)(TestList.xListEnd.pxPrevious));
		printf("ListItem1->pxPrevious             %#x					\r\n",(int)(ListItem1.pxPrevious));
		printf("/************************����**************************/\r\n");
		
		//����
		vListInsert(&TestList,&ListItem2);
		printf("/******************����б���ListItem2*****************/\r\n");
		printf("��Ŀ                              ��ַ				    \r\n");
		printf("TestList->xListEnd->pxNext        %#x					\r\n",(int)(TestList.xListEnd.pxNext));
		printf("ListItem1->pxNext                 %#x					\r\n",(int)(ListItem1.pxNext));
		printf("ListItem2->pxNext                 %#x					\r\n",(int)(ListItem2.pxNext));
		printf("/*******************ǰ�������ӷָ���********************/\r\n");
		printf("TestList->xListEnd->pxPrevious    %#x					\r\n",(int)(TestList.xListEnd.pxPrevious));
		printf("ListItem1->pxPrevious             %#x					\r\n",(int)(ListItem1.pxPrevious));
		printf("ListItem2->pxPrevious             %#x					\r\n",(int)(ListItem2.pxPrevious));
		printf("/************************����**************************/\r\n");
		
		//����
		vListInsert(&TestList,&ListItem3);
		printf("/******************����б���ListItem3*****************/\r\n");
		printf("��Ŀ                              ��ַ				    \r\n");
		printf("TestList->xListEnd->pxNext        %#x					\r\n",(int)(TestList.xListEnd.pxNext));
		printf("ListItem1->pxNext                 %#x					\r\n",(int)(ListItem1.pxNext));
		printf("ListItem2->pxNext                 %#x					\r\n",(int)(ListItem2.pxNext));
		printf("ListItem3->pxNext                 %#x					\r\n",(int)(ListItem3.pxNext));
		printf("/*******************ǰ�������ӷָ���********************/\r\n");
		printf("TestList->xListEnd->pxPrevious    %#x					\r\n",(int)(TestList.xListEnd.pxPrevious));
		printf("ListItem1->pxPrevious             %#x					\r\n",(int)(ListItem1.pxPrevious));
		printf("ListItem2->pxPrevious             %#x					\r\n",(int)(ListItem2.pxPrevious));
		printf("ListItem3->pxPrevious             %#x					\r\n",(int)(ListItem3.pxPrevious));
		printf("/************************����**************************/\r\n");
		
		//ɾ��
		uxListRemove(&ListItem3);			//�б���ɾ��
		
		printf("/******************ɾ���б���ListItem3*****************/\r\n");
		printf("��Ŀ                              ��ַ				    \r\n");
		printf("TestList->xListEnd->pxNext        %#x					\r\n",(int)(TestList.xListEnd.pxNext));
		printf("ListItem1->pxNext                 %#x					\r\n",(int)(ListItem1.pxNext));
		printf("ListItem2->pxNext                 %#x					\r\n",(int)(ListItem2.pxNext));
		printf("/*******************ǰ�������ӷָ���********************/\r\n");
		printf("TestList->xListEnd->pxPrevious    %#x					\r\n",(int)(TestList.xListEnd.pxPrevious));
		printf("ListItem1->pxPrevious             %#x					\r\n",(int)(ListItem1.pxPrevious));
		printf("ListItem2->pxPrevious             %#x					\r\n",(int)(ListItem2.pxPrevious));
		printf("/************************����**************************/\r\n");
		
		//ĩβ����
		vListInsertEnd(&TestList,&ListItem3);		//�б���ĩβ����
		printf("/******************ĩβ�����б���ListItem3*****************/\r\n");
		printf("��Ŀ                              ��ַ				    \r\n");
		printf("TestList->xListEnd->pxNext        %#x					\r\n",(int)(TestList.xListEnd.pxNext));
		printf("ListItem1->pxNext                 %#x					\r\n",(int)(ListItem1.pxNext));
		printf("ListItem2->pxNext                 %#x					\r\n",(int)(ListItem2.pxNext));
		printf("ListItem3->pxNext                 %#x					\r\n",(int)(ListItem3.pxNext));
		printf("/*******************ǰ�������ӷָ���********************/\r\n");
		printf("TestList->xListEnd->pxPrevious    %#x					\r\n",(int)(TestList.xListEnd.pxPrevious));
		printf("ListItem1->pxPrevious             %#x					\r\n",(int)(ListItem1.pxPrevious));
		printf("ListItem2->pxPrevious             %#x					\r\n",(int)(ListItem2.pxPrevious));
		printf("ListItem3->pxPrevious             %#x					\r\n",(int)(ListItem3.pxPrevious));
		printf("/************************����**************************/\r\n");
		
		//ɾ��
		uxListRemove(&ListItem3);			//�б���ɾ��
		
		TestList.pxIndex=TestList.pxIndex->pxNext;			//pxIndex�����һ�����pxIndex�ͻ�ָ��ListItem1��
		vListInsertEnd(&TestList,&ListItem3);		//�б���ĩβ����
		printf("/******************ĩβ�����б���ListItem3*****************/\r\n");
		printf("��Ŀ                              ��ַ				    \r\n");
		printf("TestList->pxIndex                 %#x					\r\n",(int)TestList.pxIndex);//��ǰ����ָ���ַ
		printf("TestList->xListEnd                %#x					\r\n",(int)(&TestList.xListEnd));//�����б��ַ
		printf("TestList->xListEnd->pxNext        %#x					\r\n",(int)(TestList.xListEnd.pxNext));
		printf("ListItem1->pxNext                 %#x					\r\n",(int)(ListItem1.pxNext));
		printf("ListItem2->pxNext                 %#x					\r\n",(int)(ListItem2.pxNext));
		printf("ListItem3->pxNext                 %#x					\r\n",(int)(ListItem3.pxNext));
		printf("/*******************ǰ�������ӷָ���********************/\r\n");
		printf("TestList->xListEnd->pxPrevious    %#x					\r\n",(int)(TestList.xListEnd.pxPrevious));
		printf("ListItem1->pxPrevious             %#x					\r\n",(int)(ListItem1.pxPrevious));
		printf("ListItem2->pxPrevious             %#x					\r\n",(int)(ListItem2.pxPrevious));
		printf("ListItem3->pxPrevious             %#x					\r\n",(int)(ListItem3.pxPrevious));
		printf("/************************����**************************/\r\n");
    while(1)
    {
			LED0=~LED0;
			vTaskDelay(500);
    }
}   
