/*
 * startup.c
 *
 *  Created on: Jul 5, 2025
 *      Author: kar-a
 */


#include <stdint.h>

#define SRAM_START 0x20000000U
#define SRAM_SIZE  0x20000U // 128KB SRAM
#define SRAM_END   ((SRAM_START) + (SRAM_SIZE))
#define STACK_START  SRAM_END

/* linker memory maps */
extern uint32_t _etext;
extern uint32_t _la_data;   // flash
extern uint32_t _sdata;     // ram
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

int main(void);

void Reset_Handler(void) {
    uint32_t size, *dptr, *sptr;
    /* copy .data to SRAM */
    dptr = (uint32_t *)&_sdata;
    sptr = (uint32_t *)&_la_data;
    size = (uint32_t)&_edata - (uint32_t)&_sdata;
    for(uint32_t i = 0; i < size; i++) {
        *dptr = *sptr;
        dptr++;
        sptr++;
    }

    /* Initialize bss with 0 */
    dptr = (uint32_t *)&_sbss;
    size = &_ebss - &_sbss;

    for(uint32_t i = 0; i < size; i++) {
        *dptr = 0;
        dptr++;
    }


    main();
}

void Default_Handler(void) {
    while(1);
}

void NMI_Handler 					(void) __attribute__ ((weak, alias("Default_Handler")));
void HardFault_Handler 				(void) __attribute__ ((weak, alias("Default_Handler")));
void MemManage_Handler 				(void) __attribute__ ((weak, alias("Default_Handler")));
void BusFault_Handler 				(void) __attribute__ ((weak, alias("Default_Handler")));
void UsageFault_Handler 			(void) __attribute__ ((weak, alias("Default_Handler")));
void SVC_Handler 					(void) __attribute__ ((weak, alias("Default_Handler")));
void DebugMon_Handler 				(void) __attribute__ ((weak, alias("Default_Handler")));
void PendSV_Handler   				(void) __attribute__ ((weak, alias("Default_Handler")));
void SysTick_Handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void WWDG_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));
void PVD_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));
void TAMP_STAMP_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));
void RTC_WKUP_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));
void RCC_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));
void FLASH_IRQHandler 			    (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI0_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI1_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI2_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI3_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI4_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Stream0_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Stream1_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Stream2_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Stream3_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Stream4_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Stream5_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Stream6_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));
void ADC_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));
void CAN1_TX_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));
void CAN1_RX0_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));
void CAN1_RX1_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));
void CAN1_SCE_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI9_5_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM1_BRK_TIM9_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM1_UP_TIM10_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM1_TRG_COM_TIM11_IRQHandler 	(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM1_CC_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM2_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM3_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM4_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));
void I2C1_EV_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));
void I2C1_ER_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));
void I2C2_EV_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));
void I2C2_ER_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));
void SPI1_IRQHandler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void SPI2_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));
void USART1_IRQHandler  			(void) __attribute__ ((weak, alias("Default_Handler")));
void USART2_IRQHandler  			(void) __attribute__ ((weak, alias("Default_Handler")));
void USART3_IRQHandler   			(void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI15_10_IRQHandler   		(void) __attribute__ ((weak, alias("Default_Handler")));
void RTC_Alarm_IRQHandler    		(void) __attribute__ ((weak, alias("Default_Handler")));
void OTG_FS_WKUP_IRQHandler     	(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM8_BRK_TIM12_IRQHandler   	(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM8_UP_TIM13_IRQHandler    	(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM8_TRG_COM_TIM14_IRQHandler 	(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM8_CC_IRQHandler          	(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Stream7_IRQHandler     	(void) __attribute__ ((weak, alias("Default_Handler")));
void FMC_IRQHandler             	(void) __attribute__ ((weak, alias("Default_Handler")));
void SDIO_IRQHandler             	(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM5_IRQHandler             	(void) __attribute__ ((weak, alias("Default_Handler")));
void SPI3_IRQHandler             	(void) __attribute__ ((weak, alias("Default_Handler")));
void UART4_IRQHandler            	(void) __attribute__ ((weak, alias("Default_Handler")));
void UART5_IRQHandler            	(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM6_DAC_IRQHandler         	(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM7_IRQHandler             	(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream0_IRQHandler     	(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream1_IRQHandler     	(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream2_IRQHandler     	(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream3_IRQHandler     	(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream4_IRQHandler     	(void) __attribute__ ((weak, alias("Default_Handler")));
void CAN2_TX_IRQHandler          	(void) __attribute__ ((weak, alias("Default_Handler")));
void CAN2_RX0_IRQHandler         	(void) __attribute__ ((weak, alias("Default_Handler")));
void CAN2_RX1_IRQHandler         	(void) __attribute__ ((weak, alias("Default_Handler")));
void CAN2_SCE_IRQHandler         	(void) __attribute__ ((weak, alias("Default_Handler")));
void OTG_FS_IRQHandler           	(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream5_IRQHandler     	(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream6_IRQHandler     	(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream7_IRQHandler     	(void) __attribute__ ((weak, alias("Default_Handler")));
void USART6_IRQHandler           	(void) __attribute__ ((weak, alias("Default_Handler")));
void I2C3_EV_IRQHandler          	(void) __attribute__ ((weak, alias("Default_Handler")));
void I2C3_ER_IRQHandler          	(void) __attribute__ ((weak, alias("Default_Handler")));
void OTG_HS_EP1_OUT_IRQHandler   	(void) __attribute__ ((weak, alias("Default_Handler")));
void OTG_HS_EP1_IN_IRQHandler    	(void) __attribute__ ((weak, alias("Default_Handler")));
void OTG_HS_WKUP_IRQHandler      	(void) __attribute__ ((weak, alias("Default_Handler")));
void OTG_HS_IRQHandler           	(void) __attribute__ ((weak, alias("Default_Handler")));
void DCMI_IRQHandler             	(void) __attribute__ ((weak, alias("Default_Handler")));
void FPU_IRQHandler              	(void) __attribute__ ((weak, alias("Default_Handler")));
void SPI4_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void SAI1_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void SAI2_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void QUADSPI_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
void HDMI_CEC_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
void SPDIF_Rx_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
void FMPI2C1_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
void FMPI2CERROR_IRQHandler         (void) __attribute__ ((weak, alias("Default_Handler")));

uint32_t __attribute__((section(".vector_table"))) vector[] = {
    STACK_START,
    (uint32_t)&Reset_Handler,                       // 1
    (uint32_t)&NMI_Handler,                         // 2
    (uint32_t)&HardFault_Handler,                   // 3
    (uint32_t)&MemManage_Handler,                   // 4
    (uint32_t)&BusFault_Handler,                    // 5
    (uint32_t)&UsageFault_Handler,                  // 6
    0, // Reserved                                  // 7
    (uint32_t)&SVC_Handler,                         // 8
    (uint32_t)&DebugMon_Handler,                    // 9
    0,                                              // 10
    (uint32_t)&PendSV_Handler,                      // 11
    (uint32_t)&SysTick_Handler,                     // 12
    (uint32_t)&WWDG_IRQHandler,                     // 13
    (uint32_t)&PVD_IRQHandler,                      // 14
    (uint32_t)&TAMP_STAMP_IRQHandler,               // 15
    (uint32_t)&RTC_WKUP_IRQHandler,                 // 16
    (uint32_t)&FLASH_IRQHandler,                    // 17
    (uint32_t)&RCC_IRQHandler,                      // 18
    (uint32_t)&EXTI0_IRQHandler,                    // 19
    (uint32_t)&EXTI1_IRQHandler,                    // 20
    (uint32_t)&EXTI2_IRQHandler,                    // 21
    (uint32_t)&EXTI3_IRQHandler,                    // 22
    (uint32_t)&EXTI4_IRQHandler,                    // 23
    (uint32_t)&DMA1_Stream0_IRQHandler,             // 24
    (uint32_t)&DMA1_Stream1_IRQHandler,             // 25
    (uint32_t)&DMA1_Stream2_IRQHandler,             // 26
    (uint32_t)&DMA1_Stream3_IRQHandler,             // 27
    (uint32_t)&DMA1_Stream4_IRQHandler,             // 28
    (uint32_t)&DMA1_Stream5_IRQHandler,             // 29
    (uint32_t)&DMA1_Stream6_IRQHandler,             // 30
    (uint32_t)&ADC_IRQHandler,                      // 31
    (uint32_t)&CAN1_TX_IRQHandler,                  // 32
    (uint32_t)&CAN1_RX0_IRQHandler,                 // 33
    (uint32_t)&CAN1_RX1_IRQHandler,                 // 34
    (uint32_t)&CAN1_SCE_IRQHandler,                 // 35
    (uint32_t)&EXTI9_5_IRQHandler,                  // 36
    (uint32_t)&TIM1_BRK_TIM9_IRQHandler,            // 37
    (uint32_t)&TIM1_UP_TIM10_IRQHandler,            // 38
    (uint32_t)&TIM1_TRG_COM_TIM11_IRQHandler,       // 39
    (uint32_t)&TIM1_CC_IRQHandler,                  // 40
    (uint32_t)&TIM2_IRQHandler,                     // 41
    (uint32_t)&TIM3_IRQHandler,                     // 42
    (uint32_t)&TIM4_IRQHandler,                     // 43
    (uint32_t)&I2C1_EV_IRQHandler,                  // 44
    (uint32_t)&I2C1_ER_IRQHandler,                  // 45
    (uint32_t)&I2C2_EV_IRQHandler,                  // 46
    (uint32_t)&I2C2_ER_IRQHandler,                  // 47
    (uint32_t)&SPI1_IRQHandler,                     // 48
    (uint32_t)&SPI2_IRQHandler,                     // 49
    (uint32_t)&USART1_IRQHandler,                   // 50
    (uint32_t)&USART2_IRQHandler,                   // 51
    (uint32_t)&USART3_IRQHandler,                   // 52
    (uint32_t)&EXTI15_10_IRQHandler,                // 53
    (uint32_t)&RTC_Alarm_IRQHandler,                // 54
    (uint32_t)&OTG_FS_WKUP_IRQHandler,              // 55
    (uint32_t)&TIM8_BRK_TIM12_IRQHandler,           // 56
    (uint32_t)&TIM8_UP_TIM13_IRQHandler,            // 57
    (uint32_t)&TIM8_TRG_COM_TIM14_IRQHandler,       // 58
    (uint32_t)&TIM8_CC_IRQHandler,                  // 59
    (uint32_t)&DMA1_Stream7_IRQHandler,             // 60
    (uint32_t)&FMC_IRQHandler,                      // 61
    (uint32_t)&SDIO_IRQHandler,                     // 62
    (uint32_t)&TIM5_IRQHandler,                     // 63
    (uint32_t)&SPI3_IRQHandler,                     // 64
    (uint32_t)&UART4_IRQHandler,                    // 65
    (uint32_t)&UART5_IRQHandler,                    // 66
    (uint32_t)&TIM6_DAC_IRQHandler,                 // 67
    (uint32_t)&TIM7_IRQHandler,                     // 68
    (uint32_t)&DMA2_Stream0_IRQHandler,             // 69
    (uint32_t)&DMA2_Stream1_IRQHandler,             // 70
    (uint32_t)&DMA2_Stream2_IRQHandler,             // 71
    (uint32_t)&DMA2_Stream3_IRQHandler,             // 72
    (uint32_t)&DMA2_Stream4_IRQHandler,             // 73
    0,                                              // 74
    0,                                              // 75
    (uint32_t)&CAN2_TX_IRQHandler,                  // 76
    (uint32_t)&CAN2_RX0_IRQHandler,                 // 77
    (uint32_t)&CAN2_RX1_IRQHandler,                 // 78
    (uint32_t)&CAN2_SCE_IRQHandler,                 // 79
    (uint32_t)&OTG_FS_IRQHandler,                   // 80
    (uint32_t)&DMA2_Stream5_IRQHandler,             // 81
    (uint32_t)&DMA2_Stream6_IRQHandler,             // 82
    (uint32_t)&DMA2_Stream7_IRQHandler,             // 83
    (uint32_t)&USART6_IRQHandler,                   // 84
    (uint32_t)&I2C3_EV_IRQHandler,                  // 85
    (uint32_t)&I2C3_ER_IRQHandler,                  // 86
    (uint32_t)&OTG_HS_EP1_OUT_IRQHandler,           // 87
    (uint32_t)&OTG_HS_EP1_IN_IRQHandler,            // 88
    (uint32_t)&OTG_HS_WKUP_IRQHandler,              // 89
    (uint32_t)&OTG_HS_IRQHandler,                   // 90
    (uint32_t)&DCMI_IRQHandler,                     // 91
    0,                                              // 92
    0,                                              // 93
    (uint32_t)&FPU_IRQHandler,                      // 94
    0,                                              // 95
    0,                                              // 96
    (uint32_t)&SPI4_IRQHandler,                     // 97
    0,                                              // 98
    0,                                              // 99
    (uint32_t)&SAI1_IRQHandler,                     // 100
    0,                                              // 101
    0,                                              // 102
    0,                                              // 103
    (uint32_t)&SAI2_IRQHandler,                     // 104
    (uint32_t)&QUADSPI_IRQHandler,                  // 105
    (uint32_t)&HDMI_CEC_IRQHandler,                 // 106
    (uint32_t)&SPDIF_Rx_IRQHandler,                 // 107
    (uint32_t)&FMPI2C1_IRQHandler,                  // 108
    (uint32_t)&FMPI2CERROR_IRQHandler,              // 109
};
