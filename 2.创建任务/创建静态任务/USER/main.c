#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "FreeRTOS.h"
#include "task.h"


//��������
static StackType_t IdleTaskStack[configMINIMAL_STACK_SIZE];//�����ջ//configMINIMAL_STACK_SIZE:��������������ջ
static StaticTask_t IdleTaskTCB;//ռ�õ��ڴ�λ��

//�������������ڴ�
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer,//��������������ƿ���ڴ�
																		StackType_t **ppxIdleTaskStackBuffer,//��ջ�ڴ�
																		uint32_t *pulIdleTaskStackSize )//��ջ�Ĵ�С
{
	*ppxIdleTaskTCBBuffer = &IdleTaskTCB;
	*ppxIdleTaskStackBuffer = IdleTaskStack;
	*pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}


//��ʱ������
static StackType_t TimerTaskStack[configTIMER_TASK_STACK_DEPTH];//�����ջ//configMINIMAL_STACK_SIZE:��������������ջ
//ռ�õ��ڴ�λ��
static StaticTask_t TimerTaskTCB;

//��ʱ�����������ڴ�
void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer,//��������������ƿ���ڴ�
																		 StackType_t **ppxTimerTaskStackBuffer,//��ջ�ڴ�
																		 uint32_t *pulTimerTaskStackSize )//��ջ�Ĵ�С
{
	*ppxTimerTaskTCBBuffer = &TimerTaskTCB;
	*ppxTimerTaskStackBuffer = TimerTaskStack;
	*pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}


//��ʼ����
#define START_TASK_PRIO		1								 //�������ȼ�
#define START_STK_SIZE 		128  						 //�����ջ��С	
StackType_t StartTaskStack[START_STK_SIZE];//�����ջ
StaticTask_t StaticTaskTCB;								 //��������������ƿ���ڴ�
TaskHandle_t StartTask_Handler;						 //������
void Start_Task(void *pvParameters);			 //��������


//LED����
#define LED_TASK_PRIO		3									//�������ȼ�
#define LED_STK_SIZE 		50  							//�����ջ��С	
StackType_t LEDTaskStack[LED_STK_SIZE];   //�����ջ
StaticTask_t LEDTaskTCB;								  //��������������ƿ���ڴ�
TaskHandle_t LED_Task_Handler;						//������
void LED_Task(void *pvParameters);				//��������


int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//����ϵͳ�ж����ȼ�����4
	delay_init(168);		                   				 //��ʼ����ʱ����
	uart_init(115200);  											   	//��ʼ������
	LED_Init();		      											    //��ʼ��LED�˿�
	
	StartTask_Handler=xTaskCreateStatic((TaskFunction_t ) Start_Task,               //������
																			(char*)						"Start_Task",             //��������
																			(uint32_t)				START_STK_SIZE,           //�����ջ��С
																			(void *)					NULL,                     //���ݸ��������Ĳ���
																			(UBaseType_t)			START_TASK_PRIO,          //�������ȼ�
																			(StackType_t *)		StartTaskStack,     			//������            
																			(StaticTask_t *)	&StaticTaskTCB);					//������ƿ���ڴ�     
	vTaskStartScheduler();          //�����������
}


//���������������
void Start_Task(void *pvParameters)//�������ݣ���Ϊ���񴴽��������ڴ��������������ֻ��ִ��һ�μ���ɾ��
{
    taskENTER_CRITICAL();           //�����ٽ��� 
    //����LED����
    StartTask_Handler=xTaskCreateStatic((TaskFunction_t )LED_Task,     	
                (const char*    )"LED_Task",   	
                (uint16_t       )LED_STK_SIZE, 
                (void*          )NULL,				
                (UBaseType_t    )LED_TASK_PRIO,	
								(StackType_t *)		LEDTaskStack,     			//������            
								(StaticTask_t *)	&LEDTaskTCB);					//������ƿ���ڴ�     
    vTaskDelete(NULL);						 //ɾ����ʼ���� //vTaskDelete(NULL);//ɾ���Լ� 
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
