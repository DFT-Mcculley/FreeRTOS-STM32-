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
#define List_TASK_PRIO		2
//任务堆栈大小	
#define List_STK_SIZE 		128
//任务句柄
TaskHandle_t List_Task_Handler;
//任务函数
void List_Task(void *pvParameters);//函数声明


//定义一个列表和三个列表项
List_t TestList;
ListItem_t ListItem1,ListItem2,ListItem3;


int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//设置系统中断优先级分组4
	delay_init(168);		//初始化延时函数
	uart_init(115200);     	//初始化串口
	LED_Init();		        //初始化LED端口
	//EXTIX_Init();
//	TIM3_Int_Init(10000-1,8400-1);
//	TIM5_Int_Init(10000-1,8400-1);
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
    xTaskCreate((TaskFunction_t )List_Task,     	
                (const char*    )"List_Task",   	
                (uint16_t       )List_STK_SIZE, 
                (void*          )NULL,				
                (UBaseType_t    )List_TASK_PRIO,	
                (TaskHandle_t*  )&List_Task_Handler);   
    vTaskDelete(StartTask_Handler); //删除开始任务 //vTaskDelete(NULL);//删除自己 
    taskEXIT_CRITICAL();            //退出临界区
}



//列表任务函数
void List_Task(void *pvParameters)
{
		//初始化
		vListInitialise(&TestList);
		vListInitialiseItem(&ListItem1);
		vListInitialiseItem(&ListItem2);
		vListInitialiseItem(&ListItem3);

		ListItem1.xItemValue = 40;
		ListItem2.xItemValue = 60;
		ListItem3.xItemValue = 50;
		
		printf("/*******************列表和列表项地址*******************/\r\n");
		printf("项目                              地址				    \r\n");
		printf("TestList                          %#x					\r\n",(int)&TestList);//列表的地址
		printf("TestList->pxIndex                 %#x					\r\n",(int)TestList.pxIndex);//当前索引指向地址
		printf("TestList->xListEnd                %#x					\r\n",(int)(&TestList.xListEnd));//迷你列表地址
		printf("ListItem1                         %#x					\r\n",(int)&ListItem1);//第一个列表项地址
		printf("ListItem2                         %#x					\r\n",(int)&ListItem2);//第一个列表项地址
		printf("ListItem3                         %#x					\r\n",(int)&ListItem3);//第一个列表项地址
		printf("/************************结束**************************/\r\n");
		
		//插入
		vListInsert(&TestList,&ListItem1);
		printf("/******************添加列表项ListItem1*****************/\r\n");
		printf("项目                              地址				    \r\n");
		printf("TestList->xListEnd->pxNext        %#x					\r\n",(int)(TestList.xListEnd.pxNext));
		printf("ListItem1->pxNext                 %#x					\r\n",(int)(ListItem1.pxNext));
		printf("/*******************前后向连接分割线********************/\r\n");
		printf("TestList->xListEnd->pxPrevious    %#x					\r\n",(int)(TestList.xListEnd.pxPrevious));
		printf("ListItem1->pxPrevious             %#x					\r\n",(int)(ListItem1.pxPrevious));
		printf("/************************结束**************************/\r\n");
		
		//插入
		vListInsert(&TestList,&ListItem2);
		printf("/******************添加列表项ListItem2*****************/\r\n");
		printf("项目                              地址				    \r\n");
		printf("TestList->xListEnd->pxNext        %#x					\r\n",(int)(TestList.xListEnd.pxNext));
		printf("ListItem1->pxNext                 %#x					\r\n",(int)(ListItem1.pxNext));
		printf("ListItem2->pxNext                 %#x					\r\n",(int)(ListItem2.pxNext));
		printf("/*******************前后向连接分割线********************/\r\n");
		printf("TestList->xListEnd->pxPrevious    %#x					\r\n",(int)(TestList.xListEnd.pxPrevious));
		printf("ListItem1->pxPrevious             %#x					\r\n",(int)(ListItem1.pxPrevious));
		printf("ListItem2->pxPrevious             %#x					\r\n",(int)(ListItem2.pxPrevious));
		printf("/************************结束**************************/\r\n");
		
		//插入
		vListInsert(&TestList,&ListItem3);
		printf("/******************添加列表项ListItem3*****************/\r\n");
		printf("项目                              地址				    \r\n");
		printf("TestList->xListEnd->pxNext        %#x					\r\n",(int)(TestList.xListEnd.pxNext));
		printf("ListItem1->pxNext                 %#x					\r\n",(int)(ListItem1.pxNext));
		printf("ListItem2->pxNext                 %#x					\r\n",(int)(ListItem2.pxNext));
		printf("ListItem3->pxNext                 %#x					\r\n",(int)(ListItem3.pxNext));
		printf("/*******************前后向连接分割线********************/\r\n");
		printf("TestList->xListEnd->pxPrevious    %#x					\r\n",(int)(TestList.xListEnd.pxPrevious));
		printf("ListItem1->pxPrevious             %#x					\r\n",(int)(ListItem1.pxPrevious));
		printf("ListItem2->pxPrevious             %#x					\r\n",(int)(ListItem2.pxPrevious));
		printf("ListItem3->pxPrevious             %#x					\r\n",(int)(ListItem3.pxPrevious));
		printf("/************************结束**************************/\r\n");
		
		//删除
		uxListRemove(&ListItem3);			//列表项删除
		
		printf("/******************删除列表项ListItem3*****************/\r\n");
		printf("项目                              地址				    \r\n");
		printf("TestList->xListEnd->pxNext        %#x					\r\n",(int)(TestList.xListEnd.pxNext));
		printf("ListItem1->pxNext                 %#x					\r\n",(int)(ListItem1.pxNext));
		printf("ListItem2->pxNext                 %#x					\r\n",(int)(ListItem2.pxNext));
		printf("/*******************前后向连接分割线********************/\r\n");
		printf("TestList->xListEnd->pxPrevious    %#x					\r\n",(int)(TestList.xListEnd.pxPrevious));
		printf("ListItem1->pxPrevious             %#x					\r\n",(int)(ListItem1.pxPrevious));
		printf("ListItem2->pxPrevious             %#x					\r\n",(int)(ListItem2.pxPrevious));
		printf("/************************结束**************************/\r\n");
		
		//末尾插入
		vListInsertEnd(&TestList,&ListItem3);		//列表项末尾插入
		printf("/******************末尾插入列表项ListItem3*****************/\r\n");
		printf("项目                              地址				    \r\n");
		printf("TestList->xListEnd->pxNext        %#x					\r\n",(int)(TestList.xListEnd.pxNext));
		printf("ListItem1->pxNext                 %#x					\r\n",(int)(ListItem1.pxNext));
		printf("ListItem2->pxNext                 %#x					\r\n",(int)(ListItem2.pxNext));
		printf("ListItem3->pxNext                 %#x					\r\n",(int)(ListItem3.pxNext));
		printf("/*******************前后向连接分割线********************/\r\n");
		printf("TestList->xListEnd->pxPrevious    %#x					\r\n",(int)(TestList.xListEnd.pxPrevious));
		printf("ListItem1->pxPrevious             %#x					\r\n",(int)(ListItem1.pxPrevious));
		printf("ListItem2->pxPrevious             %#x					\r\n",(int)(ListItem2.pxPrevious));
		printf("ListItem3->pxPrevious             %#x					\r\n",(int)(ListItem3.pxPrevious));
		printf("/************************结束**************************/\r\n");
		
		//删除
		uxListRemove(&ListItem3);			//列表项删除
		
		TestList.pxIndex=TestList.pxIndex->pxNext;			//pxIndex向后移一项，这样pxIndex就会指向ListItem1。
		vListInsertEnd(&TestList,&ListItem3);		//列表项末尾插入
		printf("/******************末尾插入列表项ListItem3*****************/\r\n");
		printf("项目                              地址				    \r\n");
		printf("TestList->pxIndex                 %#x					\r\n",(int)TestList.pxIndex);//当前索引指向地址
		printf("TestList->xListEnd                %#x					\r\n",(int)(&TestList.xListEnd));//迷你列表地址
		printf("TestList->xListEnd->pxNext        %#x					\r\n",(int)(TestList.xListEnd.pxNext));
		printf("ListItem1->pxNext                 %#x					\r\n",(int)(ListItem1.pxNext));
		printf("ListItem2->pxNext                 %#x					\r\n",(int)(ListItem2.pxNext));
		printf("ListItem3->pxNext                 %#x					\r\n",(int)(ListItem3.pxNext));
		printf("/*******************前后向连接分割线********************/\r\n");
		printf("TestList->xListEnd->pxPrevious    %#x					\r\n",(int)(TestList.xListEnd.pxPrevious));
		printf("ListItem1->pxPrevious             %#x					\r\n",(int)(ListItem1.pxPrevious));
		printf("ListItem2->pxPrevious             %#x					\r\n",(int)(ListItem2.pxPrevious));
		printf("ListItem3->pxPrevious             %#x					\r\n",(int)(ListItem3.pxPrevious));
		printf("/************************结束**************************/\r\n");
    while(1)
    {
			LED0=~LED0;
			vTaskDelay(500);
    }
}   
