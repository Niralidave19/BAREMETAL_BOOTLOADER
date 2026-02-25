#BOOTLOADER FOR STM32 F446RE 
## Project Motivation
The motive of this project is to design and implement a **bare-metal bootloader for STM32 microcontrollers**.

The bootloader provides a complete system to:
- Build a flashable application image
- Manage linker and startup files
- Receive firmware over UART using a **proprietary protocol**
- Program the received firmware into internal Flash memory
- Transfer control to the user application
---
## Bootloader Overview
- Firmware image is received via **UART**
- Data is transferred using a **custom (proprietary) protocol**
- The bootloader programs the received data into:
  - **Flash Sector 5**
  - **Flash Sector 6**
- After successful flashing, execution control is transferred to the application stored in Flash
---
## Target Platform
- MCU: **STM32F446RE**
- IDE: **STM32CubeIDE**
- Toolchain: **ARM GCC**
- Communication: **UART**
