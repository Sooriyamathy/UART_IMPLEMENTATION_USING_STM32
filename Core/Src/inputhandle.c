#include "uart.h"
#include<stdint.h>
#include<string.h>

// Define maximum buffer size for command storage
#define MAX_COMMAND_BUFFER 20

// Define LED pin position
#define LED_PIN		(1U<<5)

// Buffer to store received command
char CommandBuffer[MAX_COMMAND_BUFFER];

// Function to process received command
void command(char key)
{
	// Static index to track buffer position
	static int i=0;

	// Check for end of command (newline, carriage return, or null character)
	if(key == '\0' || key == '\n' || key=='\r')
	{
		// Null-terminate the command string
		CommandBuffer[i]='\0';
		// Reset index for next command
		i=0;

		// Check if received command is "LED_ON"
		if(strcmp(CommandBuffer,"LED_ON")==0)
		{
			// Turn LED ON
			GPIOA->ODR |= LED_PIN;
			// Send confirmation message
			char *message = "LED IS ON\n";
			for(int j=0;message[j]!='\0';j++)
			{
				uart2_write(message[j]);
			}
		}
		// Check if received command is "LED_OFF"
		else if(strcmp(CommandBuffer,"LED_OFF")==0)
		{
			// Turn LED OFF
			GPIOA->ODR &= ~LED_PIN;
			// Send confirmation message
			char *message = "LED IS OFF\n";
			for(int j=0;message[j]!='\0';j++)
			{
				uart2_write(message[j]);
			}
		}
		// If command is not recognized, send error message
		else
		{
			char* message = "COMMAND ERROR";
			for(int j=0;message[j]!='\0';j++)
			{
				uart2_write(message[j]);
			}
		}
	}
	// Store received character in buffer if within limit
	else if(i < MAX_COMMAND_BUFFER-1)
	{
		CommandBuffer[i++]=key;
	}
}
