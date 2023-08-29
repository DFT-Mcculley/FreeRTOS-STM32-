#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "FreeRTOS.h"
#include "task.h"


//空闲任务
static StackType_t IdleTaskStack[configMINIMAL_STACK_SIZE];//任务堆栈//configMINIMAL_STACK_SIZE:空闲任务的任务堆栈
static StaticTask_t IdleTaskTCB;//占用的内存位置

//空闲任务所需内存
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer,//空闲任务任务控制块的内存
																		StackType_t **ppxIdleTaskStackBuffer,//堆栈内存
																		uint32_t *pulIdleTaskStackSize )//堆栈的大小
{
	*ppxIdleTaskTCBBuffer = &IdleTaskTCB;
	*ppxIdleTaskStackBuffer = IdleTaskStack;
	*pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}


//定时器任务
static StackType_t TimerTaskStack[configTIMER_TASK_STACK_DEPTH];//任务堆栈//configMINIMAL_STACK_SIZE:空闲任务的任务堆栈
//占用的内存位置
static StaticTask_t TimerTaskTCB;

//定时器任务所需内存
void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer,//空闲任务任务控制块的内存
																		 StackType_t **ppxTimerTaskStackBuffer,//堆栈内存
																		 uint32_t *pulTimerTaskStackSize )//堆栈的大小
{
	*ppxTimerTaskTCBBuffer = &TimerTaskTCB;
	*ppxTimerTaskStackBuffer = TimerTaskStack;
	*pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}


//开始任务
#define START_TASK_PRIO		1								 //任务优先级
#define START_STK_SIZE 		128  						 //任务堆栈大小	
StackType_t StartTaskStack[START_STK_SIZE];//任务堆栈
StaticTask_t StaticTaskTCB;								 //空闲任务任务控制块的内存
TaskHandle_t StartTask_Handler;						 //任务句柄
void Start_Task(void *pvParameters);			 //函数声明


//LED任务
#define LED_TASK_PRIO		3									//任务优先级
#define LED_STK_SIZE 		50  							//任务堆栈大小	
StackType_t LEDTaskStack[LED_STK_SIZE];   //任务堆栈
StaticTask_t LEDTaskTCB;								  //空闲任务任务控制块的内存
TaskHandle_t LED_Task_Handler;						//任务句柄
void LED_Task(void *pvParameters);				//函数声明


int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//设置系统中断优先级分组4
	delay_init(168);		                   				 //初始化延时函数
	uart_init(115200);  											   	//初始化串口
	LED_Init();		      											    //初始化LED端口
	
	StartTask_Handler=xTaskCreateStatic((TaskFunction_t ) Start_Task,               //任务函数
																			(char*)						"Start_Task",             //任务名称
																			(uint32_t)				START_STK_SIZE,           //任务堆栈大小
																			(void *)					NULL,                     //传递给任务函数的参数
																			(UBaseType_t)			START_TASK_PRIO,          //任务优先级
																			(StackType_t *)		StartTaskStack,     			//任务句柄            
																			(StaticTask_t *)	&StaticTaskTCB);					//任务控制块的内存     
	vTaskStartScheduler();          //开启任务调度
}


//创建任务的任务函数
void Start_Task(void *pvParameters)//任务内容，因为任务创建函数用于创建其他任务，因此只需执行一次即可删除
{
    taskENTER_CRITICAL();           //进入临界区 
    //创建LED任务
    StartTask_Handler=xTaskCreateStatic((TaskFunction_t )LED_Task,     	
                (const char*    )"LED_Task",   	
                (uint16_t       )LED_STK_SIZE, 
                (void*          )NULL,				
                (UBaseType_t    )LED_TASK_PRIO,	
								(StackType_t *)		LEDTaskStack,     			//任务句柄            
								(StaticTask_t *)	&LEDTaskTCB);					//任务控制块的内存     
    vTaskDelete(NULL);						 //删除开始任务 //vTaskDelete(NULL);//删除自己 
    taskEXIT_CRITICAL();            //退出临界区
}


//LED任务函数
void LED_Task(void *pvParameters)
{
    while(1)
    {
        LED0=~LED0;
        vTaskDelay(500);
    }
}   
