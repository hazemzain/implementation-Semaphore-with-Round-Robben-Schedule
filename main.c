
#include "osKernel.h"
#include "STM32F4_RTOS_BSP.h"


#define	QUANTA	10

uint8_t task1_arr[]="        Task1         ";
uint8_t task2_arr[]="        Task2         ";
uint32_t count0,count1,count2,periodic_count;
uint32_t Semphor0,Semphor1,Semphor2;
void Task0(void)
{
	 while(1){
		 //osSignalWait(&Semphor0);
	 count0++;
	  //BSP_LED_redToggle();
		 BSP_LED_redOn();
		 BSP_LED_blueOff();
		 BSP_LED_orangeOff();
		 
	 }
}


void periodic_Task()
{
	periodic_count++;
	BSP_LED_redOff();
		 BSP_LED_blueOff();
		 BSP_LED_orangeOff();
	for(int i=0;i<1000;i++)
	{	
		for(int j=0;j<2000;j++);
	}
}
void Task1(void)
{
	 while(1){
		  osSignalWait(&Semphor1);
		 UART5_SendString(task1_arr);
		 osSignalSet(&Semphor2);
	 count1++;
	//BSP_LED_blueToggle();
		 BSP_LED_redOff();
		 BSP_LED_blueOn();
		 BSP_LED_orangeOff();

	 }
}	
void Task2(void)
{
	 while(1){
		 osSignalWait(&Semphor2);
		 UART5_SendString(task2_arr);
		 osSignalSet(&Semphor1);
	  count2++;
		 //BSP_LED_orangeToggle();
		 BSP_LED_redOff();
		 BSP_LED_blueOff();
		 BSP_LED_orangeOn();

	 }
}
int main(void)
{
	osSemaphoreInit(&Semphor1,1);
	osSemaphoreInit(&Semphor2,0);
	UART5_Init();
	BSP_LED_Init();
	osKernelInit();
	osKernelAddThreads(&Task0,&Task1,&Task2);
	osKernelLaunch(QUANTA);
	
}