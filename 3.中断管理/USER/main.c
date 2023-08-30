#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "FreeRTOS.h"
#include "task.h"
#include "key.h"
#include "exti.h"
#include "timer.h"


//创建任务的任务
//任务优先级
#define START_TASK_PRIO		1
//任务堆栈大小	
#define START_STK_SIZE 		128  
//任务句柄
TaskHandle_t StartTask_Handler;
//任务函数
void Start_Task(void *pvParameters);//函数声明


//KEY的任务
//任务优先级
#define KEY_TASK_PRIO		2
//任务堆栈大小	
#define KEY_STK_SIZE 		50  
//任务句柄
TaskHandle_t KEY_Task_Handler;
//任务函数
void KEY_Task(void *pvParameters);//函数声明


int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//设置系统中断优先级分组4
	delay_init(168);		//初始化延时函数
	uart_init(115200);     	//初始化串口
	LED_Init();		        //初始化LED端口
	EXTIX_Init();
	TIM3_Int_Init(10000-1,8400-1);
	TIM5_Int_Init(10000-1,8400-1);
	xTaskCreate((TaskFunction_t )Start_Task,            //任务函数
							(const char*    )"Start_Task",          //任务名称
							(uint16_t       )START_STK_SIZE,        //任务堆栈大小
							(void*          )NULL,                  //传递给任务函数的参数
							(UBaseType_t    )START_TASK_PRIO,       //任务优先级
							(TaskHandle_t*  )&StartTask_Handler);   //任务句柄             
	vTaskStartScheduler();          //开启任务调度
}


//创建任务的任务函数
void Start_Task(void *pvParameters)//任务内容，因为任务创建函数用于创建其他任务，因此只需执行一次即可删除
{
    taskENTER_CRITICAL();           //进入临界区 
    //创建KEY任务
    xTaskCreate((TaskFunction_t )KEY_Task,     	
                (const char*    )"KEY_Task",   	
                (uint16_t       )KEY_STK_SIZE, 
                (void*          )NULL,				
                (UBaseType_t    )KEY_TASK_PRIO,	
                (TaskHandle_t*  )&KEY_Task_Handler);   
    vTaskDelete(StartTask_Handler); //删除开始任务 //vTaskDelete(NULL);//删除自己 
    taskEXIT_CRITICAL();            //退出临界区
}



//KEY任务函数
void KEY_Task(void *pvParameters)
{
    while(1)
    {
			if(KEY_Scan(0)==2)
			{
				portENABLE_INTERRUPTS();//开中断
			}
    }
}   
