/**
  ******************************************************************************
  * @file    main.c
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "board.h"

/** @addtogroup STM32F3-aprs
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t execUpCount = 0;

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    uint32_t currentTime;

    /*!< At this stage the microcontroller clock setting is already configured,
         this is done through SystemInit() function which is called from startup
         file (startup_stm32f3xx.s) before to branch to application main.
         To reconfigure the default setting of SystemInit() function, refer to
          system_stm32f4xx.c file
    */

    systemReady = false;

    systemInit();

    systemReady = true;

    //evrPush(EVR_StartingMain, 0);

    /* Setup SysTick Timer for 1 msec interrupts.
       ------------------------------------------
      1. The SysTick_Config() function is a CMSIS function which configure:
         - The SysTick Reload register with value passed as function parameter.
         - Configure the SysTick IRQ priority to the lowest value (0x0F).
         - Reset the SysTick Counter register.
         - Configure the SysTick Counter clock source to be Core Clock Source (HCLK).
         - Enable the SysTick Interrupt.
         - Start the SysTick Counter.

      2. You can change the SysTick Clock source to be HCLK_Div8 by calling the
         SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8) just after the
         SysTick_Config() function call. The SysTick_CLKSourceConfig() is defined
         inside the misc.c file.

      3. You can change the SysTick IRQ priority by calling the
         NVIC_SetPriority(SysTick_IRQn,...) just after the SysTick_Config() function
         call. The NVIC_SetPriority() is defined inside the core_cm4.h file.

      4. To adjust the SysTick time base, use the following formula:

           Reload Value = SysTick Counter Clock (Hz) x  Desired Time base (s)

         - Reload Value is the parameter to be passed for SysTick_Config() function
         - Reload Value should not exceed 0xFFFFFF
     */

    while (1)
    {
        //evrCheck();

        // Wait for sampling clock to overflow
        if (TIM_GetFlagStatus(TIM2, TIM_FLAG_Update) != RESET)
        {
            ;
        }

        ///////////////////////////////

        if (frame_500Hz)
        {
            frame_500Hz = false;

            currentTime       = micros();
            deltaTime500Hz    = currentTime - previous500HzTime;
            previous500HzTime = currentTime;

            executionTime500Hz = micros() - currentTime;
        }

        ///////////////////////////////

        if (frame_100Hz)
        {
            frame_100Hz = false;

            currentTime       = micros();
            deltaTime100Hz    = currentTime - previous100HzTime;
            previous100HzTime = currentTime;

            executionTime100Hz = micros() - currentTime;
        }

        ///////////////////////////////

        if (frame_50Hz)
        {
            frame_50Hz = false;

            currentTime      = micros();
            deltaTime50Hz    = currentTime - previous50HzTime;
            previous50HzTime = currentTime;

            executionTime50Hz = micros() - currentTime;
        }

        ///////////////////////////////

        if (frame_10Hz)
        {
            frame_10Hz = false;

            currentTime      = micros();
            deltaTime10Hz    = currentTime - previous10HzTime;
            previous10HzTime = currentTime;

            cliCom();

            executionTime10Hz = micros() - currentTime;
        }

        ///////////////////////////////

        if (frame_5Hz)
        {
            frame_5Hz = false;

            currentTime     = micros();
            deltaTime5Hz    = currentTime - previous5HzTime;
            previous5HzTime = currentTime;

            executionTime5Hz = micros() - currentTime;
        }

        ///////////////////////////////

        if (frame_1Hz)
        {
            frame_1Hz = false;

            currentTime     = micros();
            deltaTime1Hz    = currentTime - previous1HzTime;
            previous1HzTime = currentTime;

            if (execUp == true)
                ledToggle(LED0);

            if (execUp == false)
                execUpCount++;

            if ((execUpCount == 5) && (execUp == false))
            {
                execUp = true;
                ledOFF(LED0);
            }

            executionTime1Hz = micros() - currentTime;
        }
    }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    /* Infinite loop */
    while (1)
    {
    }
}
#endif
