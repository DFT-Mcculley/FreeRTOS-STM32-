# **FreeRTOS⼊⻔（STM32）**

# 一、FreeRTOS简介

单片机程序分为前台（中断）和后台系统（大循环）。

## 1.RTOS与单片机裸机的区别

### 1）单片机

![image-20230829092244999](C:\Users\dft\Desktop\FreeRTOS(STM32)\FreeRTOS⼊⻔（STM32）\FreeRTOS⼊⻔（STM32）.assets\image-20230829092244999.png) 

#### 流程：

- 系统初始化；
- 主循环（1个大循环）；
- 中断（优先级最高）。

#### 原理：

系统初始化之后进入死循环无限执行任务，有中断产生时先跳出主循环执行中断服务函数，再跳入主循环进行执行任务。

#### 优点：

易开发，适用于简单的小项目

#### 缺点：

由上至下的顺序执行任务，会在某个任务等待，从而无法执行下一个任务。

### 2）RTOS

![image-20230829092746008](C:\Users\dft\Desktop\FreeRTOS(STM32)\FreeRTOS⼊⻔（STM32）\FreeRTOS⼊⻔（STM32）.assets\image-20230829092746008.png) 

#### 流程：

- 系统初始化，创建任务；
- 执行任务（多个小循环）；
- 中断（优先级最高）。

#### 原理：

系统初始化之后，进行创建任务（可删除），利用时间片轮询，同时进行多个死循环执行任务（根据优先级执行），有中断产生时先执行中断服务函数。

#### 优点：

实时性强。

#### 缺点：

 结构复杂，代码量重。

# 二、FreeRTOS移植

## 1.复制标准库工程，并重命名

![image-20230829101211777](C:\Users\dft\Desktop\FreeRTOS(STM32)\FreeRTOS⼊⻔（STM32）\FreeRTOS⼊⻔（STM32）.assets\image-20230829101211777.png) 

## 2.FerrRTOS官网

[FreeRTOS - Market leading RTOS (Real Time Operating System) for embedded systems with Internet of Things extensions](https://www.freertos.org/zh-cn-cmn-s/)

## 3.复制FerrRTOS的文件到自己工程目录下

![image-20230829093210177](C:\Users\dft\Desktop\FreeRTOS(STM32)\FreeRTOS⼊⻔（STM32）\FreeRTOS⼊⻔（STM32）.assets\image-20230829093210177.png) 

![image-20230829093351795](C:\Users\dft\Desktop\FreeRTOS(STM32)\FreeRTOS⼊⻔（STM32）\FreeRTOS⼊⻔（STM32）.assets\image-20230829093351795.png) 

portable其实只留这三个文件夹即可，其他的可删可不删。

![image-20230829103255546](C:\Users\dft\Desktop\FreeRTOS(STM32)\FreeRTOS⼊⻔（STM32）\FreeRTOS⼊⻔（STM32）.assets\image-20230829103255546.png) 



## 4.复制FerrRTOS的配置文件到自己工程目录下的任意处（记得包含路径）

###  ![image-20230829093547100](C:\Users\dft\Desktop\FreeRTOS(STM32)\FreeRTOS⼊⻔（STM32）\FreeRTOS⼊⻔（STM32）.assets\image-20230829093547100.png) 

作者这里放在Source里的include里面。

 ![image-20230829100503645](C:\Users\dft\Desktop\FreeRTOS(STM32)\FreeRTOS⼊⻔（STM32）\FreeRTOS⼊⻔（STM32）.assets\image-20230829100503645.png)  

## 5.打开工程，创建工程分组添加文件

新建两个工程分组FreeRTOS_CORE和FreeRTOS_PORTABLE

![image-20230829102100668](C:\Users\dft\Desktop\FreeRTOS(STM32)\FreeRTOS⼊⻔（STM32）\FreeRTOS⼊⻔（STM32）.assets\image-20230829102100668.png) 

![image-20230829102039741](C:\Users\dft\Desktop\FreeRTOS(STM32)\FreeRTOS⼊⻔（STM32）\FreeRTOS⼊⻔（STM32）.assets\image-20230829102039741.png) 

![image-20230829102350164](C:\Users\dft\Desktop\FreeRTOS(STM32)\FreeRTOS⼊⻔（STM32）\FreeRTOS⼊⻔（STM32）.assets\image-20230829102350164.png) 

## 6.包含头文件路径

![image-20230829102652786](C:\Users\dft\Desktop\FreeRTOS(STM32)\FreeRTOS⼊⻔（STM32）\FreeRTOS⼊⻔（STM32）.assets\image-20230829102652786.png) 

![image-20230829103434763](C:\Users\dft\Desktop\FreeRTOS(STM32)\FreeRTOS⼊⻔（STM32）\FreeRTOS⼊⻔（STM32）.assets\image-20230829103434763.png) 

## 7.修改部分代码

在文件组FreeRTOS_PORTABLE的heap_4里面找到FerrRTOSConfig.h并进入，#ifdef \__ICCARM\_\_改为以下代码

```c
#if defined(__ICCARM__) || defined(__CC_ARM) || defined(__GNUC__)
```

![image-20230829103826166](C:\Users\dft\Desktop\FreeRTOS(STM32)\FreeRTOS⼊⻔（STM32）\FreeRTOS⼊⻔（STM32）.assets\image-20230829103826166.png)  

![image-20230829104438197](C:\Users\dft\Desktop\FreeRTOS(STM32)\FreeRTOS⼊⻔（STM32）\FreeRTOS⼊⻔（STM32）.assets\image-20230829104438197.png) 

在stm32f4xx_it.c文件下注释下图三个函数。

![image-20230829104753718](C:\Users\dft\Desktop\FreeRTOS(STM32)\FreeRTOS⼊⻔（STM32）\FreeRTOS⼊⻔（STM32）.assets\image-20230829104753718.png) 

在FreeRTOSConfig.h下把下图宏定义注释掉。

![image-20230829104952265](C:\Users\dft\Desktop\FreeRTOS(STM32)\FreeRTOS⼊⻔（STM32）\FreeRTOS⼊⻔（STM32）.assets\image-20230829104952265.png) 

修改FreeRTOSConfig.h下的下图宏定义。

![image-20230829105250890](C:\Users\dft\Desktop\FreeRTOS(STM32)\FreeRTOS⼊⻔（STM32）\FreeRTOS⼊⻔（STM32）.assets\image-20230829105250890.png) 

编译无错误无警告。

## 8.修改main.c

把一下代码覆盖main.c

```c
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "FreeRTOS.h"
#include "task.h"

int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//设置系统中断优先级分组4
	delay_init(168);		//初始化延时函数
	uart_init(115200);     	//初始化串口
}
```

# 三、创建任务及删除任务

创建任务和静态任务的区别：

## 1.动态创建任务

### 1）动态创建任务函数

```c
//动态创建任务函数原型
BaseType_t xTaskCreate(	TaskFunction_t pxTaskCode,
                        const char * const pcName,
                        const uint16_t usStackDepth,
                        void * const pvParameters,
                        UBaseType_t uxPriority,
                        TaskHandle_t * const pxCreatedTask );

```

### 2）示例

示例使用的新函数

```c
xTaskCreate();//动态创建任务
vTaskDelete(); //删除任务
vTaskStartScheduler();//开启任务调度
taskENTER_CRITICAL();//进入临界区
taskEXIT_CRITICAL();//退出临界区
vTaskDelay();//延时函数
```

```c
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "FreeRTOS.h"
#include "task.h"


//任务优先级
#define START_TASK_PRIO		1
//任务堆栈大小	
#define START_STK_SIZE 		128  
//任务句柄
TaskHandle_t StartTask_Handler;
//任务函数
void Start_Task(void *pvParameters);//函数声明


//任务优先级
#define LED1_TASK_PRIO		3
//任务堆栈大小	
#define LED1_STK_SIZE 		50  
//任务句柄
TaskHandle_t LED1Task_Handler;
//任务函数
void LED_Task(void *pvParameters);//函数声明


int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//设置系统中断优先级分组4
	delay_init(168);		//初始化延时函数
	uart_init(115200);     	//初始化串口
	LED_Init();		        //初始化LED端口
    xTaskCreate((TaskFunction_t )Start_Task,            //任务函数
                (const char*    )"Start_Task",          //任务名称
                (uint16_t       )START_STK_SIZE,        //任务堆栈大小
                (void*          )NULL,                  //传递给任务函数的参数
                (UBaseType_t    )START_TASK_PRIO,       //任务优先级
                (TaskHandle_t*  )&StartTask_Handler);   //任务句柄             
    vTaskStartScheduler();         					  //开启任务调度
}


//创建任务的任务函数
void Start_Task(void *pvParameters)//任务内容，因为任务创建函数用于创建其他任务，因此只需执行一次即可删除
{
    taskENTER_CRITICAL();           //进入临界区 
    //创建LED0任务
    xTaskCreate((TaskFunction_t )LED_Task,     	
                (const char*    )"LED_Task",   	
                (uint16_t       )LED0_STK_SIZE, 
                (void*          )NULL,				
                (UBaseType_t    )LED0_TASK_PRIO,	
                (TaskHandle_t*  )&LED0Task_Handler);   
    vTaskDelete(StartTask_Handler); //删除开始任务 //vTaskDelete(NULL);//删除自己 
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

```

小提示：

代码的临界段也称为临界区，一旦这部分代码开始执行，则不允许任何中断打断。为确保临界段代码
的执行不被中断，在进入临界段之前须关中断，而临界段代码执行完毕后，要立即开中断。

## 2.静态创建任务

### 1）修改宏编译configSUPPORT_STATIC_ALLOCATION

把configSUPPORT_STATIC_ALLOCATION 	0改为configSUPPORT_STATIC_ALLOCATION	1

![image-20230829114358921](C:\Users\dft\Desktop\FreeRTOS(STM32)\FreeRTOS⼊⻔（STM32）\FreeRTOS⼊⻔（STM32）.assets\image-20230829114358921.png) 

FreeRTOS默认至少会创建一个任务，即空闲任务，若将宏configSUPPORT_STATIC_ALLOCATION打开，则空闲任务也会使用静态的方法创建，因此也需任务堆栈（需内存）、任务控制块（需内存），该内存需用户自供，即通过vApplicationGetIdleTaskMemory()函数提供（引用处见task.c的1967行vTaskStartScheduler()任务调度器内），定时器任务同理。

```c
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
```

### 2）静态创建任务函数

```c
//静态创建任务函数原型
    TaskHandle_t xTaskCreateStatic( TaskFunction_t pxTaskCode,
                                    const char * const pcName, 
                                    const uint32_t ulStackDepth,
                                    void * const pvParameters,
                                    UBaseType_t uxPriority,
                                    StackType_t * const puxStackBuffer,
                                    StaticTask_t * const pxTaskBuffer )
```

### 3）示例

示例使用的新函数

```c
vApplicationGetIdleTaskMemory();//获取任务内存
```

```c
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
#define START_TASK_PRIO		1							//任务优先级
#define START_STK_SIZE 		128  						 //任务堆栈大小	
StackType_t StartTaskStack[START_STK_SIZE];//任务堆栈
StaticTask_t StaticTaskTCB;								 //空闲任务任务控制块的内存
TaskHandle_t StartTask_Handler;							 //任务句柄
void Start_Task(void *pvParameters);					 //函数声明


//LED任务
#define LED_TASK_PRIO		3								//任务优先级
#define LED_STK_SIZE 		50  							//任务堆栈大小	
StackType_t LEDTaskStack[LED_STK_SIZE];   					 //任务堆栈
StaticTask_t LEDTaskTCB;								    //空闲任务任务控制块的内存
TaskHandle_t LED_Task_Handler;								//任务句柄
void LED_Task(void *pvParameters);							//函数声明


int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);			//设置系统中断优先级分组4
	delay_init(168);		                   			   //初始化延时函数
	uart_init(115200);  								 //初始化串口
	LED_Init();		      								 //初始化LED端口
	
	StartTask_Handler=xTaskCreateStatic((TaskFunction_t ) Start_Task,               //任务函数
                                                        (char*)						"Start_Task",        //任务名称
                                                        (uint32_t)				START_STK_SIZE,           //任务堆栈大小
                                                        (void *)					NULL,                 //传递给任务函数的参数
                                                        (UBaseType_t)			START_TASK_PRIO,          //任务优先级
                                                        (StackType_t *)		StartTaskStack,     		 //任务句柄            
                                                        (StaticTask_t *)	&StaticTaskTCB);			 //任务控制块的内存     
	vTaskStartScheduler();          																//开启任务调度
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
                (StackType_t *)	LEDTaskStack,     			//任务句柄            
                (StaticTask_t *)&LEDTaskTCB);					//任务控制块的内存     
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
```

## 3.删除任务

```c
vTaskDelete(任务名);						 //vTaskDelete(NULL);//删除自己 
```

# 四、任务挂起和恢复

## 1.相关函数

```c
vTaskSuspend();	//挂起一个任务
vTaskResume();	//恢复一个任务
xTaskResumeFromISR();	//在中断服务函数中恢复一个任务 
```

## 2.示例

```c
//main.c文件
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "FreeRTOS.h"
#include "task.h"
#include "key.h"
#include "exti.h"


//创建任务的任务
//任务优先级
#define START_TASK_PRIO		1
//任务堆栈大小	
#define START_STK_SIZE 		128  
//任务句柄
TaskHandle_t StartTask_Handler;
//任务函数
void Start_Task(void *pvParameters);//函数声明


//LED的任务
//任务优先级
#define LED_TASK_PRIO		3
//任务堆栈大小	
#define LED_STK_SIZE 		50  
//任务句柄
TaskHandle_t LED_Task_Handler;
//任务函数
void LED_Task(void *pvParameters);//函数声明


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
    //创建LED任务
    xTaskCreate((TaskFunction_t )LED_Task,     	
                (const char*    )"LED_Task",   	
                (uint16_t       )LED_STK_SIZE, 
                (void*          )NULL,				
                (UBaseType_t    )LED_TASK_PRIO,	
                (TaskHandle_t*  )&LED_Task_Handler);
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


//LED任务函数
void LED_Task(void *pvParameters)
{
    while(1)
    {
        LED0=~LED0;
        vTaskDelay(500);
    }
}   


//KEY任务函数
void KEY_Task(void *pvParameters)
{
    while(1)
    {
			if(KEY_Scan(0)==2)
			{
					vTaskSuspend(LED_Task_Handler);//挂起LED任务
					LED0=1;
			}
    }
}   
```

```c
//exti.c 文件
#include "exti.h"
#include "delay.h" 
#include "key.h"
#include "FreeRTOS.h"
#include "task.h"
	   
//外部中断初始化程序
//初始化PE2~4,PA0为中断输入.
void EXTIX_Init(void)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	
	KEY_Init(); //按键对应的IO口初始化
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//使能SYSCFG时钟
 
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource4);//PE4 连接到中断线4
	
	/* 配置EXTI_Line4 */
	EXTI_InitStructure.EXTI_Line =  EXTI_Line4;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;		//中断事件
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿触发
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;				//中断线使能
	EXTI_Init(&EXTI_InitStructure);							//配置
 
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;		//外部中断4
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x06;//抢占优先级6
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;	//子优先级0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//使能外部中断通道
	NVIC_Init(&NVIC_InitStructure);							//配置	   
}

//任务句柄
extern TaskHandle_t LED_Task_Handler;

//外部中断4服务程序,KEY0
void EXTI4_IRQHandler(void)
{
	BaseType_t YieldRequired;
	if(KEY0==0)	 
	{				 
		YieldRequired=xTaskResumeFromISR(LED_Task_Handler);//恢复LED任务
		if(YieldRequired==pdTRUE)
		{
			/*如果函数xTaskResumeFromISR()返回值为pdTRUE，那么说明要恢复的这个
			任务的任务优先级等于或者高于正在运行的任务(被中断打断的任务),所以在
			退出中断的时候一定要进行上下文切换！*/
			portYIELD_FROM_ISR(YieldRequired);
		}
	}		 
	 EXTI_ClearITPendingBit(EXTI_Line4);//清除LINE4上的中断标志位  
}
```



# 五、中断管理

## 1）抢占优先级与子优先级

ARM Cortex-M使用8位宽的寄存器来配置中断的优先级，即最大支持256，但STM32只用了中断优先级配置寄存器的高4位[7:4]，因此STM32提供了最大16级的中断优先等级。

- 抢占优先级：抢占优先级高的中断可以打断正在执行但强制优先级低的中断。
- 子优先级：当同时发生具有相同抢占优先级的两个中断时，子优先级数值小的优先执行。

![image-20230829170604022](C:\Users\dft\Desktop\FreeRTOS(STM32)\FreeRTOS⼊⻔（STM32）\FreeRTOS⼊⻔（STM32）.assets\image-20230829170604022.png) 

```c
NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
```

## 2）中断屏蔽寄存器

- PRIMASK：这是个只有1个位的寄存器。当它置1时，就关掉所有可屏蔽的异常，只剩下NMI和硬fault可以响应。它的缺省值是0,表示没有关中断。
- FAULTMASK：这是个只有1个位的寄存器。当它置1时，只有NMI才能响应，所有其它的异常，包括中断和fault,通通闭嘴。它的缺省值也是0，表示没有关异常。（比PRIMASK高级一点）
- BASEPRI：这个寄存器最多有9位(由表达优先级的位数决定)。它定义了被屏蔽优先级的阈值。当它被设成某个值后，所有优先级号大于等于此值的中断都被关(优先级号越大，优先级越低)。但若被设成0，则不关闭任何中断，0也是缺省值。（FreeRTOS采用该方式进行中断屏蔽）

![image-20230829171143312](C:\Users\dft\Desktop\FreeRTOS(STM32)\FreeRTOS⼊⻔（STM32）\FreeRTOS⼊⻔（STM32）.assets\image-20230829171143312.png) 

## 3）相关宏

```c
#define configPRIO_BITS       		4        /* 15 priority levels */	//几位优先级
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY			0xf	//优先级的个数为16，最低优先级为15
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY	5	//系统可管理的最高中断优先级
#define configKERNEL_INTERRUPT_PRIORITY 	( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )//设置内核中断优先级    
#define portDISABLE_INTERRUPTS()                  vPortRaiseBASEPRI()	//关中断
#define portENABLE_INTERRUPTS()                   vPortSetBASEPRI( 0 )	//开中断
```

## 4）示例

```c
//main.c
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

```

```c
//key.c
#include "key.h"
#include "delay.h" 

//按键初始化函数
void KEY_Init(void)
{
	
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOE, ENABLE);//使能GPIOA,GPIOE时钟
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4; //KEY0 KEY1 KEY2对应引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIOE2,3,4
	
	 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;//WK_UP对应引脚PA0
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN ;//下拉
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA0
} 

//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//0，没有任何按键按下
//1，KEY0按下
//2，KEY1按下
//3，KEY2按下 
//4，WKUP按下 WK_UP
//注意此函数有响应优先级,KEY0>KEY1>KEY2>WK_UP!!
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按		  
	if(key_up&&(KEY1==0||KEY2==0||WK_UP==1))
	{
		delay_ms(10);//去抖动 
		key_up=0;
		if(KEY0==0)return 1;
		else if(KEY1==0)return 2;
		else if(KEY2==0)return 3;
		else if(WK_UP==1)return 4;
	}else if(KEY0==1&&KEY1==1&&KEY2==1&&WK_UP==0)key_up=1; 	    
 	return 0;// 无按键按下
}

```

```c
//timer.h
#ifndef _TIMER_H
#define _TIMER_H
#include "sys.h"

void TIM3_Int_Init(u16 arr,u16 psc);
void TIM5_Int_Init(u16 arr,u16 psc);
#endif

```

```c
//exti.c
#include "exti.h"
#include "delay.h" 
#include "key.h"
#include "FreeRTOS.h"
#include "task.h"
	   
//外部中断初始化程序
//初始化PE2~4,PA0为中断输入.
void EXTIX_Init(void)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	
	KEY_Init(); //按键对应的IO口初始化
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//使能SYSCFG时钟
 
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource4);//PE4 连接到中断线4
	
	/* 配置EXTI_Line4 */
	EXTI_InitStructure.EXTI_Line =  EXTI_Line4;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;		//中断事件
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿触发
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;				//中断线使能
	EXTI_Init(&EXTI_InitStructure);							//配置
 
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;		//外部中断4
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x05;//抢占优先级5
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;	//子优先级0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//使能外部中断通道
	NVIC_Init(&NVIC_InitStructure);							//配置	   
}

//任务句柄
extern TaskHandle_t LED_Task_Handler;

//外部中断4服务程序,KEY0
void EXTI4_IRQHandler(void)
{
	BaseType_t YieldRequired;
	if(KEY0==0)	 
	{
		portDISABLE_INTERRUPTS();//关中断
	}		 
	 EXTI_ClearITPendingBit(EXTI_Line4);//清除LINE4上的中断标志位  
}

```

```c
//timer.c
#include "timer.h"
#include "led.h"

//通用定时器3中断初始化
//arr：自动重装值。
//psc：时钟预分频数
//定时器溢出时间计算方法:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=定时器工作频率,单位:Mhz
//这里使用的是定时器3!
void TIM3_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  ///使能TIM3时钟
	
  TIM_TimeBaseInitStructure.TIM_Period = arr; 	//自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);//初始化TIM3
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //允许定时器3更新中断
	TIM_Cmd(TIM3,ENABLE); //使能定时器3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; //定时器3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x04; //抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x00; //子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}


//通用定时器3中断初始化
//arr：自动重装值。
//psc：时钟预分频数
//定时器溢出时间计算方法:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=定时器工作频率,单位:Mhz
//这里使用的是定时器3!
void TIM5_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);  ///使能TIM3时钟
	
  TIM_TimeBaseInitStructure.TIM_Period = arr; 	//自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStructure);//初始化TIM3
	
	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE); //允许定时器3更新中断
	TIM_Cmd(TIM5,ENABLE); //使能定时器3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM5_IRQn; //定时器3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x05; //抢占优先级5
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x00; //子优先级0
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}

//定时器3中断服务函数
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) //溢出中断
	{
		LED0=!LED0;//LED0翻转
	}
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //清除中断标志位
}

//定时器3中断服务函数
void TIM5_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM5,TIM_IT_Update)==SET) //溢出中断
	{
		LED1=!LED1;//LED1翻转
	}
	TIM_ClearITPendingBit(TIM5,TIM_IT_Update);  //清除中断标志位
}

```



