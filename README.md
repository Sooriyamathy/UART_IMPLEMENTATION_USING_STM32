
# STM32 UART Communication with RealTerm (STM32F446RE)

This project demonstrates UART communication between an STM32F446RE microcontroller and a PC using RealTerm for viewing and interacting with the data sent and received over UART. The communication allows the user to send commands like `LED_ON` and `LED_OFF` from RealTerm, and the STM32F446RE responds by toggling an LED on the board.

## Project Overview

In this project, the STM32F446RE communicates with a PC through UART, where commands are sent from the user via RealTerm, and the STM32 microcontroller processes these commands to control an LED.

### Key Features:
- **Low-Level UART Configuration:** This project uses STM32 low-level register programming to configure and manage UART communication.
- **RealTerm for Command and Response:** RealTerm is used for sending commands to the STM32 and displaying responses.
- **Simple LED Control:** The STM32 responds to commands `LED_ON` and `LED_OFF` by toggling the state of an onboard LED.

## Hardware Requirements
- STM32F446RE microcontroller
- USB to TTL adapter (for connecting STM32 to your PC)
- Jumper wires to connect TX and RX pins between the STM32 and USB to TTL adapter
- PC with RealTerm software installed
- LED connected to an available GPIO pin on STM32F446RE (e.g., PA5 for onboard LED)

## Software Requirements
- STM32CubeIDE or your preferred development environment for STM32
- RealTerm (for UART communication with the STM32)

## Communication Setup

### Wiring Configuration
- **STM32 TX (Transmit)** → **USB to TTL RX (Receive)**
- **STM32 RX (Receive)** → **USB to TTL TX (Transmit)**
- **GND** → **GND**

### RealTerm Setup
1. Open **RealTerm** on your PC.
2. Set the correct serial port corresponding to the USB to TTL adapter.
3. Set the communication parameters to match the STM32 UART configuration (e.g., Baud rate: 9600, Data bits: 8, Stop bits: 1, Parity: None).
4. Use RealTerm to send commands and display responses.

## STM32 UART Setup

The UART configuration for STM32F446RE is done using low-level registers. Below are the key steps in configuring the UART and processing commands.

### 1. UART Initialization
The STM32 UART initialization is done by configuring the following registers:
- **BRR** (Baud Rate Register) for setting the baud rate.
- **CR1** (Control Register 1) to enable the transmitter, receiver, and interrupt (if necessary).
- **CR2** (Control Register 2) to configure stop bits.
- **CR3** (Control Register 3) to manage flow control.

### 2. UART Transmission
To send data, the STM32 writes the data to the **DR** (Data Register) and waits for the **TXE** flag to be set before sending the next byte:

```c
// Wait for TXE (Transmit Data Register Empty) flag
while (!(USART1->SR & USART_SR_TXE));

// Send data byte to the USART data register
USART1->DR = data;
```

### 3. UART Reception
For receiving data, the STM32 reads the **DR** register when the **RXNE** flag is set:

```c
// Wait for RXNE (Read Data Register Not Empty) flag
while (!(USART1->SR & USART_SR_RXNE));

// Read received data byte
receivedData = USART1->DR;
```

### 4. Command Processing
The STM32 processes the commands `LED_ON` and `LED_OFF` to toggle the state of an LED connected to a GPIO pin.

```c
if (strcmp(receivedData, "LED_ON") == 0) {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);  // Turn on LED (PA5)
} else if (strcmp(receivedData, "LED_OFF") == 0) {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);  // Turn off LED (PA5)
}
```

### 5. Interrupts (Optional)
You can also configure UART interrupts for asynchronous reception of data. This allows you to handle incoming commands without polling for data continuously.

## How to Use

### Step 1: Set up Hardware
1. Connect the STM32F446RE to the USB to TTL adapter.
2. Connect the adapter to your PC via USB.
3. Ensure the LED is connected to GPIO pin PA5 (or any other pin if modified in the code).

### Step 2: Set up STM32 Environment
1. Clone this repository to your local machine.
2. Open the project in STM32CubeIDE (or any other preferred development environment).
3. Compile and flash the code to the STM32F446RE microcontroller.

### Step 3: Open RealTerm
1. Launch **RealTerm** on your PC.
2. Select the correct COM port for your USB to TTL adapter.
3. Configure the baud rate, data bits, stop bits, and parity to match the STM32 configuration (e.g., Baud rate: 9600).
4. You should now see the output from the STM32 and can start sending commands.

### Step 4: Interact with the System
- **Send Commands:** In RealTerm, type `LED_ON` or `LED_OFF` and press Enter.
- **View Responses:** The STM32 will process the commands and respond accordingly (e.g., turning the LED on or off).

## Code Structure
- **main.c:** Contains the main application code to handle UART communication and LED control.
- **uart.c:** Functions for initializing and handling UART communication.
- **gpio.c:** Manages GPIO configuration for controlling the LED.
- **uart.h:** Header file containing declarations for UART functions.

## Example Command Flow

### Sending a Command:
1. Open RealTerm and connect to the appropriate COM port.
2. Type `LED_ON` and press Enter.

   **RealTerm (Sent):**
   ```
   LED_ON
   ```

### STM32 Response:
1. The STM32 turns on the LED and sends a response back.

   **STM32 Response (in RealTerm):**
   ```
   LED IS ON
   ```

### Sending Another Command:
1. Type `LED_OFF` and press Enter.

   **RealTerm (Sent):**
   ```
   LED_OFF
   ```

### STM32 Response:
1. The STM32 turns off the LED and sends a response back.

   **STM32 Response (in RealTerm):**
   ```
   LED IS OFF
   ```
### Output Example

1. **LED ON Command**: When the `LED_ON` command is sent, the LED lights up as shown below:
   
   ![LED ON](https://github.com/Sooriyamathy/UART_IMPLEMENTATION_USING_STM32/blob/main/OUTPUT%20photos/LED_ON.jpg)

2. **LED OFF Command**: When the `LED_OFF` command is sent, the LED turns off as seen in the image below:

   ![LED OFF](https://github.com/Sooriyamathy/UART_IMPLEMENTATION_USING_STM32/blob/main/OUTPUT%20photos/LED_OFF.jpg)

These output images demonstrate the LED's response to the UART commands.
## Troubleshooting

- **No response from STM32**: Check the wiring between the STM32 and the USB to TTL adapter. Ensure that the TX and RX pins are correctly connected.
- **RealTerm does not connect**: Make sure you have selected the correct COM port and configured the baud rate and parameters correctly.
- **LED not toggling**: Ensure the LED is connected to the correct GPIO pin (e.g., PA5) and that the code matches the pin configuration.

## Contributing
Feel free to fork the repository, contribute bug fixes, or add new features via pull requests. All contributions are welcome!

## License
This project is licensed under the GNU License - see the [LICENSE](LICENSE) file for details.
