#include <stdio.h>
#include <stdint.h>
#include "stm32f446xx.h"
#include "uart.h"
#include "inputhandle.h"

char key;  // Variable to store received UART character

int main(void)
{
    // Enable clock for GPIOA (bit 0 of RCC AHB1 peripheral clock enable register)
    RCC->AHB1ENR = 1U << 0;

    // Configure PA5 as output (LED control)
    GPIOA->MODER |= (1U << 10);   // Set bit 10 (PA5 mode bit 0)
    GPIOA->MODER &= ~(1U << 11);  // Clear bit 11 (PA5 mode bit 1) -> Output mode

    // Initialize UART for transmission and reception
    uart2_rxtx_init();

    // Infinite loop to continuously read data from UART and process commands
    while (1)
    {
        key = uart2_read();  // Read a character from UART
        command(key);        // Pass the character to command handler function
    }
}


