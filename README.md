# STM32 UART2 Transmission Example

This repository contains a basic example of setting up UART2 on the STM32F446xx microcontroller using HAL-less direct register programming. The example demonstrates how to initialize UART2, configure its GPIO pin for transmission, and send a character over UART.

## Features

- **UART2 Initialization**: Initializes USART2 on STM32F446xx.
- **GPIO Configuration**: Configures the appropriate GPIO pin (PA2) for UART transmission (TX).
- **Baud Rate Setup**: Configures UART baud rate to 115200.
- **Transmission**: Sends the character `'Y'` continuously over UART.

## System Requirements

- **STM32F446xx** microcontroller or compatible hardware.
- **STM32CubeMX** (optional for pinout and clock configuration).
- **STM32 HAL** is not used; direct register manipulation is employed.
- **Keil uVision** or any compatible IDE with GCC for STM32.

## Pin Configuration

- **TX (PA2)**: This pin is configured for UART2 transmission.

## Clock Configuration

- **System Clock (SYS_FREQ)**: 16 MHz.
- **APB1 Clock**: Directly derived from the system clock.
  
## Code Walkthrough

### 1. `uar2_tx_init()`

This function initializes UART2 for transmission:

- **GPIO Configuration**:
  - Enables the clock for GPIOA.
  - Configures PA2 as an alternate function (AF07) for UART_TX.
  
- **UART2 Configuration**:
  - Enables the clock for UART2.
  - Configures the baud rate using the `uart_set_baudrate` function.
  - Sets the transfer direction (TX).
  - Enables the UART2 module.

### 2. `uart2_write()`

This function writes a character to the UART2 data register:

- It waits for the UART's TXE (Transmit Data Register Empty) flag to be set.
- Once set, it writes the provided character into the data register (USART2->DR).

### 3. `uart_set_baudrate()`

This function sets the UART baud rate by computing the baud rate value and writing it into the BRR register.

### 4. `compute_uart_bd()`

This function computes the value for the baud rate based on the peripheral clock and desired baud rate.

```c
static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate)
{
  return ((PeriphClk + (BaudRate/2U)) / BaudRate);
}
```

## How to Use

### 1. Clone the repository:
```bash
git clone https://github.com/Sooriyamathy/UART_IMPLEMENTATION_USING_STM32.git
```

### 2. Open the project in your IDE (Keil, STM32CubeIDE, etc.).

### 3. Flash the code to your STM32F446xx microcontroller.

### 4. Use a terminal program (such as PuTTY or Tera Term) to observe the serial output from the microcontroller.

### 5. You should see the character `'Y'` being continuously transmitted over UART.

## Notes

- The UART2 configuration in this example is minimal and only enables the transmit functionality.
- Make sure you have configured the correct clock settings and the UART pin (PA2) before flashing the code.
- The code is written for STM32F446xx, and might require modification for other STM32 series.

## License

This code is open-source and available for modification under the MIT license.

---

If you have any questions or need further assistance, feel free to open an issue in the GitHub repository.
