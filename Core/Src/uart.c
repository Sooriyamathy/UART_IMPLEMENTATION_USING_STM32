#include "stm32f446xx.h"

/* Enable clock for GPIOA and UART2 */
#define GPIOAEN		(1U<<0)  // GPIOA clock enable
#define UART2EN		(1U<<17) // UART2 clock enable

/* UART control register bit definitions */
#define CR1_TE		(1U<<3)  // Transmit enable
#define CR1_UE		(1U<<13) // UART enable
#define SR_TXE		(1U<<7)  // Transmit data register empty
#define CR1_RE		(1U<<2)  // Receive enable

/* System clock and baud rate settings */
#define SYS_FREQ		16000000  // System frequency 16MHz
#define APB1_CLK		SYS_FREQ  // APB1 clock frequency
#define UART_BAUDRATE		115200  // UART baud rate

/* Function prototypes */
static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk,  uint32_t BaudRate);
static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate);
void uart2_write(int ch);

/* Redirect printf output to UART */
int __io_putchar(int ch)
{
	uart2_write(ch);
	return ch;
}

/* UART2 initialization function */
void uart2_rxtx_init(void)
{
	/****************Configure UART GPIO pin***************/
	/* Enable clock access to GPIOA */
	RCC->AHB1ENR |= GPIOAEN;

	/* Set PA2 mode to alternate function mode for transmitter mode */
	GPIOA->MODER &=~(1U<<4);
	GPIOA->MODER |= (1U<<5);

	/* Set PA3 to alternate function mode for receiver mode */
	GPIOA->MODER &= ~(1U<<6);
	GPIOA->MODER |= (1U<<7);

	/* Set PA2 alternate function type to UART_TX (AF07) */
	GPIOA->AFR[0] |= (1U<<8)|(1U<<9)|(1U<<10);
	GPIOA->AFR[0] &= ~(1U<<11);

	/* Set PA3 to alternate function type to UART_RX (AF07) */
	GPIOA->AFR[0] &= ~(1U<<15);
	GPIOA->AFR[0] |= ((1U<<12)|(1U<<13)|(1U<<14));

	/****************Configure UART module ***************/
	/* Enable clock access to UART2 */
	RCC->APB1ENR |= UART2EN;

	/* Configure BaudRate */
	uart_set_baudrate(USART2, APB1_CLK, UART_BAUDRATE);

	/* Configure the transfer direction (transmitter) */
	USART2->CR1 =  CR1_TE;

	/* Enable Receiver */
	USART2->CR1 |= CR1_RE;

	/* Enable UART module */
	USART2->CR1 |= CR1_UE;
}

/* Function to read a character from UART2 */
char uart2_read(void)
{
	/* Make sure receive data register is not empty */
	while(!(USART2->SR & (1U<<5)))
	{}
	return USART2->DR; // Return received character
}

/* Function to transmit a character using UART2 */
void uart2_write(int ch)
{
  /* Make sure the transmit data register is empty */
	while(!(USART2->SR & SR_TXE)){}

  /* Write to transmit data register */
	USART2->DR =  (ch & 0xFF);
}

/* Function to set UART baud rate */
static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk,  uint32_t BaudRate)
{
	USARTx->BRR =  compute_uart_bd(PeriphClk, BaudRate);
}

/* Function to compute the UART baud rate register value */
static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate)
{
	return ((PeriphClk + (BaudRate/2U))/BaudRate);
}
