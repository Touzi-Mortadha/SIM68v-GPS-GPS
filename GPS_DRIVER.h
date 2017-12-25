#ifndef GPS_DRIVER_H
#define GPS_DRIVER_H



void GPS_USART_Init(void);

uint8_t GPS_USART_Receive_Byte(void);

void GPS_USART_Receive_Buffer(uint8_t* Read_buffer, uint32_t size);


#endif
