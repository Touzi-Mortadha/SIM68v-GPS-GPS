
#include "main.h"


BT_Packet packet ;
finderState finder;

int main(void)
{

  /* SysTick end of count event each 10ms */
  RCC_GetClocksFreq(&RCC_Clocks);
  SysTick_Config(RCC_Clocks.HCLK_Frequency / 100);

  //GPS initializing
  GPS_USART_Init();


//************ FSM ********** //
//  finder.currentState = IDLE ;
//  finder.nextState = NORTH_DETECTION ;



  while (1)
  {

    switch(finder.currentState)
    {

        case IDLE :
            //blablabla ............
            finder.currentState=finder.nextState;
            finder.nextState=GPS_DATA;

            break;

        case NORTH_DETECTION :
            //blablabla
            finder.currentState = finder.nextState;
            finder.nextState = SHOW_DIRECTION;
            break;


        case GPS_DATA :
            GPS_receive_data(&packet);

            //completing all packet fields

            packet.start=START;
            packet.id=DATA;
            packet.end=END;
            packet.length=LENGTH;


            finder.currentState=finder.nextState;
            finder.nextState=IDLE;
            break;


            //GSM
        case SHOW_DIRECTION :

            sendLocation(&packet);
            //blablabla
            finder.currentState=finder.nextState;
            finder.nextState=NORTH_DETECTION;
            break;
    } // end switch
  } // end while(1)
}





/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in 10 ms.
  * @retval None
  */
void Delay(__IO uint32_t nTime)
{
  TimingDelay = nTime;

  while(TimingDelay != 0);
}

/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval None
  */
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  {
    TimingDelay--;
  }
}

/**
  * @brief  Basic management of the timeout situation.
  * @param  None.
  * @retval None.
  */
uint32_t LSM303DLHC_TIMEOUT_UserCallback(void)
{
  return 0;
}

/**
  * @brief  Basic management of the timeout situation.
  * @param  None.
  * @retval None.
  */
uint32_t L3GD20_TIMEOUT_UserCallback(void)
{
  return 0;
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
