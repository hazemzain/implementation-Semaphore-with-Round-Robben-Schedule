#include "STM32F4_RTOS_BSP.h"
#include "stm32f4xx.h"                  // Device header

#define BSP_LED_red_BIT     (1U<<26) /*(1U<<28)*/
#define BSP_LED_green_BIT    (1U<<22)      /*(1U<<26)*/
#define BSP_LED_orange_BIT (1U<<26)
#define BSP_LED_blue_BIT   (1U<<30)

#define	LED_PORT		    GPIOG
#define	BSP_LED_red		 (1U<<13) /*(1U<<14)*/
#define BSP_LED_green   (1U<<11)/*(1U<<13)*/
#define BSP_LED_blue   (1U<<15)
#define BSP_LED_orange (1U<<13)

#define GPIOG_CLOCK   (1<<6)
#define GPIOA_CLOCK 	(1<<0)
#define GPIOC_CLOCK   (1<<2)

#define BSP_Button_PORT		GPIOA

#define BSP_Probe0_BIT  (1U<<0)   /*PC0 as output*/
#define BSP_Probe1_BIT  (1U<<2)   /*PC1 as output*/
#define BSP_Probe2_BIT  (1U<<4)   /*PC2 as output*/
#define BSP_Probe3_BIT  (1U<<8)   /*PC4 as output*/

#define BSP_Probe_PORT		GPIOC
#define CH0			(1U<<0)
#define CH1			(1U<<1)
#define CH2			(1U<<2)
#define CH3			(1U<<4)


void TIMER2_Init(void)
{
	RCC->APB1ENR |= 0x01;  /*Enable TIM2 clock*/
	TIM2->PSC = 16000 -1;  /* 16 000 000 /160 = 100 000*/
	TIM2->ARR = 1000 -1;
	TIM2->CR1 =1;  /*Counter enable*/
	TIM2->DIER |=1; /*Enable Interrupt*/
	NVIC_EnableIRQ(TIM2_IRQn);
}
void BSP_Probe_Init(void){

	  RCC->AHB1ENR |= GPIOC_CLOCK;
	  BSP_Probe_PORT->MODER |=  BSP_Probe0_BIT|BSP_Probe1_BIT|BSP_Probe2_BIT|BSP_Probe3_BIT;
}

void BSP_Probe_CH0(){
  BSP_Probe_PORT->ODR ^= CH0;
}

void BSP_Probe_CH1(){
  BSP_Probe_PORT->ODR ^= CH1;
}
void BSP_Probe_CH2(){
  BSP_Probe_PORT->ODR ^= CH2;
}
void BSP_Probe_CH3(){
  BSP_Probe_PORT->ODR ^= CH3;
}

void BSP_Button_Init(void)
{
	 RCC->AHB1ENR |= GPIOA_CLOCK;
	 BSP_Button_PORT->MODER &= ~0x00000011; /*Clear PA0 pin*/
	
}

uint32_t  BSP_Button_Read(void){
	
	return BSP_Button_PORT->IDR &0x01;
}

void BSP_Delay_Millisecond(uint32_t delay){

	RCC->APB1ENR |= 0x02;  /*Enable TIM3 clock*/
	TIM3->PSC = 160 -1;  /* 16 000 000 /160 = 100 000*/
	TIM3->ARR = 100 -1;  /* 100 000 /100 = 1000*/
	TIM3->CNT =0;
	TIM3->CR1 =1;
	
	for(int i =0;i<delay;i++){
	
		 while(!(TIM3->SR & 1)){}   /*wait for UIF set*/
			 TIM3->SR &= ~1;
			 
	}
	
	
}

void  BSP_ADC1_Init(void){
	
	/*GPIO Pin*/
	RCC->AHB1ENR |=1;				/*ENABLE clock for GPIOA*/
	GPIOA->MODER |= 0xC;		/*PA1 set as analog*/
	
	/*Setup ADC!*/
	RCC->APB2ENR |=0x00000100;
	ADC1->CR2		=0;
	ADC1->SQR3  =1;  /*Conversion sequence start at channel 1*/
  ADC1->SQR1  =0;  /*Length of sequence is 1*/	
  ADC1->CR2		|=1;


}

uint32_t BSP_Sensor_Read(void){
  
	  ADC1->CR2 |= 0x40000000;   /*Start conversion*/
	  while(!(ADC1->SR & 2)){}   /*Wait for conversion complete*/
		
			return ADC1->DR;

}

void BSP_LED_Init(void)
{
  __disable_irq();
	RCC->AHB1ENR |=GPIOG_CLOCK;
	GPIOG->MODER |= BSP_LED_red_BIT|BSP_LED_green_BIT|BSP_LED_orange_BIT|BSP_LED_blue_BIT;
  __enable_irq();

}



 void BSP_LED_blueOn(void)
 {
	 GPIOG->ODR |=BSP_LED_blue;
	 
 }

 void BSP_LED_blueOff(void)
 {
	 GPIOG->ODR &= ~BSP_LED_blue;
	 
 }


 
  void BSP_LED_orangeOn(void)
 {
	 GPIOG->ODR |=BSP_LED_orange;
	 
 }

 void BSP_LED_orangeOff(void)
 {
	 GPIOG->ODR &= ~BSP_LED_orange;
	 
 }
 
  void BSP_LED_greenOn(void)
 {
	 GPIOG->ODR |=BSP_LED_green;
	 
 }

 void BSP_LED_greenOff(void)
 {
	 GPIOG->ODR &= ~BSP_LED_green;
	 
 }

 void BSP_LED_redOn(void)
 {
	 GPIOG->ODR |=BSP_LED_red;
	 
 }

 void BSP_LED_redOff(void)
 {
	 GPIOG->ODR &= ~BSP_LED_red;
	 
 }
  void BSP_LED_blueToggle(void)
 {
	 GPIOG->ODR ^=BSP_LED_blue;
	 
 }

 void BSP_LED_greenToggle(void)
 {
	 GPIOG->ODR ^=BSP_LED_green;
	 
 }
 
 void BSP_LED_redToggle(void)
 {
	 GPIOG->ODR ^=BSP_LED_red;
	 
 }

 void BSP_LED_orangeToggle(void)
 {
	 GPIOG->ODR ^=BSP_LED_orange;
	 
 }
void UART5_Init(void)
{
	/*0-Enable CLoc For PATH that have UART5 (APB1)*/
	/*1-Enable RCC for UART5*/
	RCC->APB1ENR|=(1<<20);
	/*2-Enable RCC for Pin that allow to UART5 */
	RCC->AHB1ENR|=(1<<2);
	RCC->AHB1ENR|=(1<<3);

	/*3-Enable Altrante Funcation for this Pin RX-TX(pc12 ==TX)(PD2==RX)*/
	GPIOC->MODER|=(2<<24);
	GPIOC->AFR[1]|=(8<<16);
	GPIOD->MODER|=(2<<4);
	GPIOD->AFR[0]|=(8<<8);
	/*4-Configration for UART5*/
			/*Word lengthWord length*/
				UART5->CR1&=~(1<<12);
				/*sampling by 16*/
				UART5->CR1&=~(1<<15);
			/* Parity control enable*/
				UART5->CR1|=(1<<10);
			/*: Parity selection*/
				UART5->CR1|=(1<<9);
			/*STOP: STOP bits one*/
				UART5->CR2&=~(1<<12);
				UART5->CR2&=~(1<<13);
			/*�PSC[4:0]: Prescaler value*/
			UART5->BRR=0x0683;
			/* TE: Transmitter enable*/
			UART5->CR1|=(1<<3);
			/* RE: Receiver enable*/
			UART5->CR1|=(1<<2);
			/*enable break */
	SET_BIT(UART5->CR1,0);
			
}
void UART5_SendCharachter(char* Copy_Var)
{
	/*: USART enable*/
		UART5->CR1|=(1<<13);
	while(GET_BIT(UART5->SR,7)==0);
	UART5->DR&=0;
	UART5->DR=*Copy_Var;
	while(GET_BIT(UART5->SR,6)==0);
}
void UART5_SendString(char *arr)
{
	int i=0;
	while(arr[i]!='\0')
		{
			UART5_SendCharachter(&arr[i]);
			i++;
		}
}