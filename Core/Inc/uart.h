#ifndef INC_UART_H_
#define INC_UART_H_
#include "stm32f446xx.h"
#define MAX_COMMAND_BUFFER 20
void uart2_rxtx_init(void);
char uart2_read(void);
void uart2_write(int ch);
#endif /* INC_UART_H_ */
