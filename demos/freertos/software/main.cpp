// ----------------------------------------------------------------------------
// Copyright (c) 2020-2024 RISC-V Steel contributors
//
// This work is licensed under the MIT License, see LICENSE file for details.
// SPDX-License-Identifier: MIT
// ----------------------------------------------------------------------------

#include "libsteel/soc.h"
#include <FreeRTOS.h>
#include <task.h>

#define STACK_SIZE 800

StaticTask_t xTaskBuffer;
StackType_t xStack[STACK_SIZE];

void vTaskCode(void *pvParameters)
{
  configASSERT((uint32_t)pvParameters == 1UL);

  for (;;)
  {
    vTaskDelay(500);
    gpio_set(RVSTEEL_GPIO, 0);
    vTaskDelay(500);
    gpio_clear(RVSTEEL_GPIO, 0);
  }
}

StaticTask_t xTaskBuffer1;
StackType_t xStack1[STACK_SIZE];

void vTaskCode1(void *pvParameters)
{
  configASSERT((uint32_t)pvParameters == 1UL);

  for (;;)
  {
    vTaskDelay(1000);
    gpio_set(RVSTEEL_GPIO, 1);
    vTaskDelay(1000);
    gpio_clear(RVSTEEL_GPIO, 1);
  }
}

int main(void)
{
  csr_enable_vectored_mode_irq();
  mtimer_enable(RVSTEEL_MTIMER);
  gpio_set_output(RVSTEEL_GPIO, 0);
  gpio_set_output(RVSTEEL_GPIO, 1);

  /* Create the task without using any dynamic memory allocation. */
  xTaskCreateStatic(vTaskCode,     /* Function that implements the task. */
                    "NAME",        /* Text name for the task. */
                    STACK_SIZE,    /* Number of indexes in the xStack array. */
                    (void *)1,     /* Parameter passed into the task. */
                    1,             /* Priority at which the task is created. */
                    xStack,        /* Array to use as the task's stack. */
                    &xTaskBuffer); /* Variable to hold the task's data structure. */

  /* Create the task without using any dynamic memory allocation. */
  xTaskCreateStatic(vTaskCode1,     /* Function that implements the task. */
                    "NAME",         /* Text name for the task. */
                    STACK_SIZE,     /* Number of indexes in the xStack array. */
                    (void *)1,      /* Parameter passed into the task. */
                    1,              /* Priority at which the task is created. */
                    xStack1,        /* Array to use as the task's stack. */
                    &xTaskBuffer1); /* Variable to hold the task's data structure. */

  vTaskStartScheduler();

  while (1)
    ;
}

/* configSUPPORT_STATIC_ALLOCATION is set to 1, so the application must provide an
implementation of vApplicationGetIdleTaskMemory() to provide the memory that is
used by the Idle task. */
void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer,
                                   StackType_t **ppxIdleTaskStackBuffer,
                                   uint32_t *pulIdleTaskStackSize)
{
  /* If the buffers to be provided to the Idle task are declared inside this
  function then they must be declared static - otherwise they will be allocated on
  the stack and so not exists after this function exits. */
  static StaticTask_t xIdleTaskTCB;
  static StackType_t uxIdleTaskStack[configMINIMAL_STACK_SIZE];

  /* Pass out a pointer to the StaticTask_t structure in which the Idle task's
  state will be stored. */
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCB;

  /* Pass out the array that will be used as the Idle task's stack. */
  *ppxIdleTaskStackBuffer = uxIdleTaskStack;

  /* Pass out the size of the array pointed to by *ppxIdleTaskStackBuffer.
  Note that, as the array is necessarily of type StackType_t,
  configMINIMAL_STACK_SIZE is specified in words, not bytes. */
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}

#ifdef __cplusplus
extern "C"
{
#endif
  /* Trap handler for Machine Timer Interrupts.
     Calls FreeRTOS MTimer interrupt handler and return. */
  __attribute__((naked)) void mti_irq_handler()
  {
    __ASM_VOLATILE("call freertos_risc_v_mtimer_interrupt_handler");
    __ASM_VOLATILE("mret");
  }
  /* The default trap handler (for non-vectored mode).
     Calls FreeRTOS exception handler and return. */
  __attribute__((naked)) void default_trap_handler()
  {
    __ASM_VOLATILE("call freertos_risc_v_exception_handler");
    __ASM_VOLATILE("mret");
  }
#ifdef __cplusplus
}
#endif