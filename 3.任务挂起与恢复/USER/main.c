#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "FreeRTOS.h"
#include "task.h"
#include "key.h"
#include "exti.h"


//�������������
//�������ȼ�
#define START_TASK_PRIO		1
//�����ջ��С	
#define START_STK_SIZE 		128  
//������
TaskHandle_t StartTask_Handler;
//������
void Start_Task(void *pvParameters);//��������


//LED������
//�������ȼ�
#define LED_TASK_PRIO		3
//�����ջ��С	
#define LED_STK_SIZE 		50  
//������
TaskHandle_t LED_Task_Handler;
//������
void LED_Task(void *pvParameters);//��������


//KEY������
//�������ȼ�
#define KEY_TASK_PRIO		2
//�����ջ��С	
#define KEY_STK_SIZE 		50  
//������
TaskHandle_t KEY_Task_Handler;
//������
void KEY_Task(void *pvParameters);//��������


int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//����ϵͳ�ж����ȼ�����4
	delay_init(168);		//��ʼ����ʱ����
	uart_init(115200);     	//��ʼ������
	LED_Init();		        //��ʼ��LED�˿�
	EXTIX_Init();
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
    //����LED����
    xTaskCreate((TaskFunction_t )LED_Task,     	
                (const char*    )"LED_Task",   	
                (uint16_t       )LED_STK_SIZE, 
                (void*          )NULL,				
                (UBaseType_t    )LED_TASK_PRIO,	
                (TaskHandle_t*  )&LED_Task_Handler);
    //����KEY����
    xTaskCreate((TaskFunction_t )KEY_Task,     	
                (const char*    )"KEY_Task",   	
                (uint16_t       )KEY_STK_SIZE, 
                (void*          )NULL,				
                (UBaseType_t    )KEY_TASK_PRIO,	
                (TaskHandle_t*  )&KEY_Task_Handler);   
    vTaskDelete(StartTask_Handler); //ɾ����ʼ���� //vTaskDelete(NULL);//ɾ���Լ� 
    taskEXIT_CRITICAL();            //�˳��ٽ���
}


//LED������
void LED_Task(void *pvParameters)
{
    while(1)
    {
        LED0=~LED0;
        vTaskDelay(500);
    }
}   


//KEY������
void KEY_Task(void *pvParameters)
{
    while(1)
    {
			if(KEY_Scan(0)==2)
			{
					vTaskSuspend(LED_Task_Handler);//����LED����
					LED0=1;
			}
    }
}   
