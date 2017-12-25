#include<main.h>

void GPS_USART_Init(){

       GPIO_InitTypeDef  GPS_GPIO_InitStruct;
       USART_InitTypeDef GPS_USART_InitStruct;

       // initializing GPIOC and USART3 for the GPS module

       RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
       GPS_GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_5 | GPIO_Pin_6; // -- PC10 = USART3_TX -- PC11 = USART3_RX
       GPS_GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
       GPS_GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
       GPS_GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
       GPS_GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
       GPIO_Init(GPIOC, &GPS_GPIO_InitStruct);


       GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_7);
       GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_7);

       RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);


       USART_DeInit(USART3);
       GPS_USART_InitStruct.USART_BaudRate = 9600;
       GPS_USART_InitStruct.USART_WordLength = USART_WordLength_8b;
       GPS_USART_InitStruct.USART_StopBits = USART_StopBits_1;
       GPS_USART_InitStruct.USART_Parity = USART_Parity_No;
       GPS_USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
       GPS_USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
       USART_Init(USART3,&GPS_USART_InitStruct);

       USART_Cmd(USART3, ENABLE);
}



uint8_t GPS_USART_Receive_Byte(void)
{
  //wait until the RXNE bit is set
  while (((USART3->ISR & USART_FLAG_RXNE) == RESET) ) {}
  return((uint8_t) USART_ReceiveData(USART3));
}



void GPS_USART_Receive_Buffer(uint8_t* Read_buffer, uint32_t size)
{
  int i = 0;
  for (i=0; i<size; i++)
  {
    Read_buffer[i] = GPS_USART_Receive_Byte();
  }
}
