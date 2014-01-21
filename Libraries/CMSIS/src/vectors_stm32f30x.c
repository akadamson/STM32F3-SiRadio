//
// This file is part of the GNU ARM Eclipse Plug-in
// Copyright (c) 2013 Liviu Ionescu
//

#if defined (__cplusplus)
extern "C"
  {
#endif

//*****************************************************************************
//
// Forward declaration of the default handlers. These are aliased.
// When the application defines a handler (with the same name), this will
// automatically take precedence over these weak definitions
//
//*****************************************************************************
void __attribute__((weak))
Reset_Handler(void);
void __attribute__((weak))
NMI_Handler(void);
void __attribute__((weak))
HardFault_Handler(void);
void __attribute__((weak))
MemManage_Handler(void);
void __attribute__((weak))
BusFault_Handler(void);
void __attribute__((weak))
UsageFault_Handler(void);
void __attribute__((weak))
SVC_Handler(void);
void __attribute__((weak))
DebugMon_Handler(void);
void __attribute__((weak))
PendSV_Handler(void);
void __attribute__((weak))
SysTick_Handler(void);

void __attribute__((weak))
Default_Handler(void);

//*****************************************************************************
//
// Forward declaration of the specific IRQ handlers. These are aliased
// to the Default_Handler, which is a 'forever' loop. When the application
// defines a handler (with the same name), this will automatically take
// precedence over these weak definitions
//
//*****************************************************************************
void __attribute__ ((weak, alias ("Default_Handler")))
WWDG_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
PVD_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
TAMPER_STAMP_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
RTC_WKUP_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
FLASH_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
RCC_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
EXTI0_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
EXTI1_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
EXTI2_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
EXTI3_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
EXTI4_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
DMA1_Channel1_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
DMA1_Channel2_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
DMA1_Channel3_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
DMA1_Channel4_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
DMA1_Channel5_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
DMA1_Channel6_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
DMA1_Channel7_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
ADC1_2_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
USB_HP_CAN1_TX_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
USB_LP_CAN1_RX0_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
CAN1_RX1_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
CAN1_SCE_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
EXTI9_5_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
TIM1_BRK_TIM15_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
TIM1_UP_TIM16_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
TIM1_TRG_COM_TIM17_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
TIM1_CC_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
TIM2_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
TIM3_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
TIM4_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
I2C1_EV_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
I2C1_ER_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
I2C2_EV_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
I2C2_ER_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
SPI1_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
SPI2_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
USART1_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
USART2_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
USART3_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
EXTI15_10_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
RTC_Alarm_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
USBWakeUp_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
TIM8_BRK_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
TIM8_UP_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
TIM8_TRG_COM_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
TIM8_CC_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
ADC3_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
SPI3_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
UART4_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
UART5_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
TIM6_DAC_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
TIM7_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
DMA2_Channel1_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
DMA2_Channel2_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
DMA2_Channel3_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
DMA2_Channel4_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
DMA2_Channel5_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
ADC4_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
COMP1_2_3_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
COMP4_5_6_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
COMP7_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
USB_HP_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
USB_LP_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
USBWakeUp_RMP_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
FPU_IRQHandler(void);

extern unsigned int _estack;

typedef void
(* const pfn)(void);
//extern pfn g_pfnVectors[];

//*****************************************************************************
#if defined (__cplusplus)
} // extern "C"
#endif

//*****************************************************************************
//
// The vector table.
// This relies on the linker script to place at correct location in memory.
//
//*****************************************************************************

__attribute__ ((section(".isr_vector")))
pfn g_pfnVectors[] =
  {
  // Core Level - CM4
      (pfn) &_estack,                           // The initial stack pointer
      Reset_Handler,                            // The reset handler

      NMI_Handler,                              // The NMI handler
      HardFault_Handler,                        // The hard fault handler
      MemManage_Handler,                        // The MPU fault handler
      BusFault_Handler,                         // The bus fault handler
      UsageFault_Handler,                       // The usage fault handler
      0,                                        // Reserved
      0,                                        // Reserved
      0,                                        // Reserved
      0,                                        // Reserved
      SVC_Handler,                              // SVCall handler
      DebugMon_Handler,                         // Debug monitor handler
      0,                                        // Reserved
      PendSV_Handler,                           // The PendSV handler
      SysTick_Handler,                          // The SysTick handler

      // Chip Level - STM32F30x
      WWDG_IRQHandler,                           // Window WatchDog
      PVD_IRQHandler,                            // PVD
      TAMPER_STAMP_IRQHandler,                   // Tamper and TimeStamps
      RTC_WKUP_IRQHandler,                       // RTC Wakeup
      FLASH_IRQHandler,                          // FLASH
      RCC_IRQHandler,                            // RCC
      EXTI0_IRQHandler,                          // EXTI Line0
      EXTI1_IRQHandler,                          // EXTI Line1
      EXTI2_IRQHandler,                          // EXTI Line2
      EXTI3_IRQHandler,                          // EXTI Line3
      EXTI4_IRQHandler,                          // EXTI Line4
      DMA1_Channel1_IRQHandler,                  // DMA1 Channel 1
      DMA1_Channel2_IRQHandler,                  // DMA1 Channel 2
      DMA1_Channel3_IRQHandler,                  // DMA1 Channel 3
      DMA1_Channel4_IRQHandler,                  // DMA1 Channel 4
      DMA1_Channel5_IRQHandler,                  // DMA1 Channel 5
      DMA1_Channel6_IRQHandler,                  // DMA1 Channel 6
      DMA1_Channel7_IRQHandler,                  // DMA1 Channel 7
      ADC1_2_IRQHandler,                         // ADC1, 2
      USB_HP_CAN1_TX_IRQHandler,                 // USB HP & CAN1 TX
      USB_LP_CAN1_RX0_IRQHandler,                // USB LP & CAN1 RX0
      CAN1_RX1_IRQHandler,                       // CAN1 RX1
      CAN1_SCE_IRQHandler,                       // CAN1 SCE
      EXTI9_5_IRQHandler,                        // External Line[9:5]s
      TIM1_BRK_TIM15_IRQHandler,                 // TIM1 Break and TIM15
      TIM1_UP_TIM16_IRQHandler,                  // TIM1 Update and TIM16
      TIM1_TRG_COM_TIM17_IRQHandler,             // TIM1 and TIM17
      TIM1_CC_IRQHandler,                        // TIM1 Capture Compare
      TIM2_IRQHandler,                           // TIM2
      TIM3_IRQHandler,                           // TIM3
      TIM4_IRQHandler,                           // TIM4
      I2C1_EV_IRQHandler,                        // I2C1 Event
      I2C1_ER_IRQHandler,                        // I2C1 Error
      I2C2_EV_IRQHandler,                        // I2C2 Event
      I2C2_ER_IRQHandler,                        // I2C2 Error
      SPI1_IRQHandler,                           // SPI1
      SPI2_IRQHandler,                           // SPI2
      USART1_IRQHandler,                         // USART1
      USART2_IRQHandler,                         // USART2
      USART3_IRQHandler,                         // USART3
      EXTI15_10_IRQHandler,                      // External Line[15:10]s
      RTC_Alarm_IRQHandler,                      // RTC Alarm (A and B)
      USBWakeUp_IRQHandler,                      // USB  Wakeup
      TIM8_BRK_IRQHandler,                       // TIM8 Break
      TIM8_UP_IRQHandler,                        // TIM8 Update
      TIM8_TRG_COM_IRQHandler,                   // TIM8
      TIM8_CC_IRQHandler,                        // TIM8 Capture Compare
      ADC3_IRQHandler,                           // ADC3
      0,                                         // Reserved
      0,                                         // Reserved
      0,                                         // Reserved
      SPI3_IRQHandler,                           // SPI3
      UART4_IRQHandler,                          // UART4
      UART5_IRQHandler,                          // UART5
      TIM6_DAC_IRQHandler,                       // TIM6 and DAC
      TIM7_IRQHandler,                           // TIM7
      DMA2_Channel1_IRQHandler,                  // DMA2 Channel 1
      DMA2_Channel2_IRQHandler,                  // DMA2 Channel 2
      DMA2_Channel3_IRQHandler,                  // DMA2 Channel 3
      DMA2_Channel4_IRQHandler,                  // DMA2 Channel 4
      DMA2_Channel5_IRQHandler,                  // DMA2 Channel 5
      ADC4_IRQHandler,                           // ADC4
      0,                                         // Reserved
      0,                                         // Reserved
      COMP1_2_3_IRQHandler,                      // COMP 1,2,3
      COMP4_5_6_IRQHandler,                      // COMP 4,5,6
      COMP7_IRQHandler,                          // COMP 7
      0,                                         // Reserved
      0,                                         // Reserved
      0,                                         // Reserved
      0,                                         // Reserved
      0,                                         // Reserved
      0,                                         // Reserved
      0,                                         // Reserved
      USB_HP_IRQHandler,                         // USB HP
      USB_LP_IRQHandler,                         // USB LP
      USBWakeUp_RMP_IRQHandler,                  // USB Wakeup through EXTI
      0,                                         // Reserved
      0,                                         // Reserved
      0,                                         // Reserved
      0,                                         // Reserved
      FPU_IRQHandler                             // FPU
    };

//*****************************************************************************
//
// Processor ends up here if an unexpected interrupt occurs or a specific
// handler is not present in the application code.
//
//*****************************************************************************

void __attribute__ ((section(".after_vectors")))
Default_Handler(void)
{
  while (1)
    {
    }
}

//*****************************************************************************
// Default exception handlers. Override the ones here by defining your own
// handler routines in your application code.
//*****************************************************************************
void __attribute__ ((section(".after_vectors")))
NMI_Handler(void)
{
  while (1)
    {
    }
}

void __attribute__ ((section(".after_vectors")))
HardFault_Handler(void)
{
  while (1)
    {
    }
}

void __attribute__ ((section(".after_vectors")))
MemManage_Handler(void)
{
  while (1)
    {
    }
}

void __attribute__ ((section(".after_vectors")))
BusFault_Handler(void)
{
  while (1)
    {
    }
}

void __attribute__ ((section(".after_vectors")))
UsageFault_Handler(void)
{
  while (1)
    {
    }
}

void __attribute__ ((section(".after_vectors")))
SVC_Handler(void)
{
  while (1)
    {
    }
}

void __attribute__ ((section(".after_vectors")))
DebugMon_Handler(void)
{
  while (1)
    {
    }
}

void __attribute__ ((section(".after_vectors")))
PendSV_Handler(void)
{
  while (1)
    {
    }
}

void __attribute__ ((section(".after_vectors")))
SysTick_Handler(void)
{
  while (1)
    {
    }
}

