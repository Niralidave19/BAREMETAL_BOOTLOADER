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
2. Create different sections of memory, and define where they would be placed and executed.(in flash/RAM?)
### DATA segment
- Stored in flash ( copied to RAM during startup)
- Contains initialized globals and statics
- Initial values lives in Flash memory , then copied to RAM for usage during execution.
- _la_data = LOADADDR(.data) This stores the Load Memory Address (LMA) of .data segment. This is the address in Flash where the initial values are stored
- _sdata = . This marks the start of data in SRAM
- _edata = . This marks the end of data in SRAM
- Run .data from SRAM, but load it from FLASH
### TEXT segment
- Section goes into the flash memory
- Contains all executable instructions , constants , vector table which goes into flash memory.
- Align 4 : ARM cortex -m requires word alignment to avoid hard faults. Hence align the current locaation counter to 4 bytes
### BSS segment
- Section goes into RAM since they are read and write variables
- Uninitialized globals and statics are stored in the .BSS segment
  
 <img width="801" height="392" alt="image" src="https://github.com/user-attachments/assets/f93e1962-d8c9-41fe-a923-5224e80a8472" />
   
## STARTUP file 
### Vector table 
Vector table is defined in the startup file, which has the Stack pointer , address of reset handler, and the interrupt / exception handlers.
- On power up, CPU reads vector_table[0] and vector_table[1].Both these values are read automatically by hardware, CPU has no stack, no PC at reset, no execution of any code.
- Entry [0] of the vector table is the Stack Pointer , Entry [1] has the address of the reset handler
- Vector_table[0] is loaded onto SP and Vector_table[1] is loaded onto PC register of the controller.
- Execution begins from reset handler, starting at the address loaded into PC
### Execution of reset handler 
- Reset handler, copies .data to SRAM: All the initialised globals and statics are copied into RAM
- Initialises all the memory addresses in the BSS segment to 0
- Calls main()

## Bootloader 
<img width="545" height="457" alt="image" src="https://github.com/user-attachments/assets/354ea12b-9bfe-4ac0-a921-7e1c7cbdba23" />

### Receive flash file as serial data frames


### STM32 receives the data frame via UART RX
- 












