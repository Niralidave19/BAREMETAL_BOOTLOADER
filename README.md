# BOOTLOADER FOR STM32 F446RE 
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

## Linker script
1. Define the memory layout for RAM and FLASH memory.
2. Create different sections of memory, and define where they would be placed (in flash/RAM?)
 <img width="801" height="392" alt="image" src="https://github.com/user-attachments/assets/f93e1962-d8c9-41fe-a923-5224e80a8472" />
### .DATA
- Stored in flash ( copied to RAM during startup)
- Contains initialized globals and statics
- Initial values lives in Flash memory , then copied to RAM for usage during execution.
- _la_data = LOADADDR(.data) This stores the Load Memory Address (LMA) of .data segment. This is the address in Flash where the initial values are stored
- _sdata = . This marks the start of data in SRAM
- _edata = . This marks the end of data in SRAM
- Run .data from SRAM, but load it from FLASH
### .TEXT
- Section goes into the flash memory
- Contains all executable instructions , constants , vector table which goes into flash memory.
- Align 4 : ARM cortex -m requires word alignment to avoid hard faults. Hence align the current locaation counter to 4 bytes
### .BSS
- Section goes into RAM since they are read and write variables
- Uninitialized globals and statics are stored in the .BSS segment
  

   



