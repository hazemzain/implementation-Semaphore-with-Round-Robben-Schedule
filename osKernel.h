#ifndef __OS_KERNEL_H__
#define __OS_KERNEL_H__

#include <stdint.h>

#include "stm32f4xx.h"                  // Device header

void osKernelLaunch(uint32_t quanta);
void osKernelInit(void);
uint8_t osKernelAddThreads(void(*task0)(void), void(*task1)(void),void(*task2)(void));
void osThreadYield(void);
void periodic_Task(void);
void osSemaphoreInit(int32_t *semaphore,int32_t value);
void osSignalSet(int *semaphore);
void osSignalWait(int32_t *semaphore);
#endif