/*******************************************************************************************
 * File name: app_uart_flash.c
 * Description: The Client sends a flash file through UART, and this application moves the control to the sector
 * of flash memory where it has been flashed
 *******************************************************************************************/

#include <stdint.h>
#include "uart_proto.h"
#include "app_uart_proto.h"
#include"flash_types.h"
#include"stm32f446xx.h"

/* Receive request to flash data from client
 * Send ACK to client
 * Client sends no. of bytes of data and no. of records
 * Clear memory segment and send ACK
 * Client sends 16 Bytes of data - and waits
 * Server checks if the data isn't corrupted and writes this data
 * Server sends ACK
 * Clients sends data ... process continues till no. of bytes reached
 */

#define START_ADDR  		0x08060000UL    /* Sector 7*/
#define FLASH_BASE			0x40023C00UL
#define FLASH               ((FLASH_TypeDef *) FLASH_BASE)

void app_flash_write_unlock(){
	/* Write KEY1 */
	FLASH->KEYR = 0x45670123;
	FLASH->KEYR = 0xCDEF89AB;

	/* wait till FLash CR is unlocked */
	while(FLASH->CR & FLASH_CR_LOCK);
	/* Code reaching here indicates FLASH CR is unlocked */

	/* Wait till operation over */
	while(FLASH->SR & FLASH_SR_BSY);
	/* If interrupts are enabled check for EOP */

	/* Write a byte to flash */
	/* Set PSIZE (00 for byte writing) */
	/* CLear 8th and 9th bit */
	FLASH->CR &= ~(0x3 << FLASH_CR_PSIZE);
	/* Set bits to correct value (0 in case of byte writing) */
	FLASH->CR |= 0 << FLASH_CR_PSIZE;
}
void app_sector_erase(){
		/* sector erase */
	/* wait for flash operation to end */
	while(FLASH->SR & FLASH_SR_BSY);
	/* SER bit set */
	FLASH->CR |= FLASH_CR_SER;
	/* Clear SNB */
	FLASH->CR &= ~(0xF << FLASH_CR_SNB);
	/* Select sector 7 in SNB */
	FLASH->CR |= (0x7 << FLASH_CR_SNB);
	/* Start Sector clear */
	FLASH->CR |= FLASH_CR_START;
	/* Wait for end of operation */
	while(FLASH->SR & FLASH_SR_BSY);
	/* Clear SER */
	FLASH->CR &= ~(FLASH_CR_SER);
	/* Clear SNB */
	FLASH->CR &= ~(0xF << FLASH_CR_SNB);
	/* START gets cleared automatically */
	/* Set programming bit */
	FLASH->CR |= FLASH_CR_PG;
}
void app_write_byte(uint32_t addr,uint8_t byte){
	*((uint8_t *)(addr)) = (uint8_t)byte;
}

void app_lock_flash(){
	/* Wait for operation completion */
	while(FLASH->SR & FLASH_SR_BSY);
	/* Clear programming bit */
	FLASH->CR &= ~(FLASH_CR_PG);
	/* Wait for completion */
	while(FLASH->SR & FLASH_SR_BSY);
	/* Flush caches */
	/* Flush instruction cache  */
	if ((FLASH->ACR & FLASH_ACR_ICEN) != 0)
	{
		/* Disable instruction cache  */
		FLASH->ACR &= ~(FLASH_ACR_ICEN);
		/* Reset instruction cache */
		FLASH->ACR |= FLASH_ACR_ICRST;
		/* Enable instruction cache */
		FLASH->ACR |= FLASH_ACR_ICEN;
	}
	  /* Flush data cache */
	if ((FLASH->ACR & FLASH_ACR_DCEN) != 0)
	{
		/* Disable data cache  */
		FLASH->ACR &= ~(FLASH_ACR_DCEN);
		/* Reset data cache */
		FLASH->ACR |= FLASH_ACR_DCRST;
		/* Enable data cache */
		FLASH->ACR |= FLASH_ACR_DCEN;
	}
	/* Wait for completion */
	while(FLASH->SR & FLASH_SR_BSY);
	/* Lock flash */
	FLASH->CR |= FLASH_CR_LOCK;
	/* Wait for completion */
	while(FLASH->SR & FLASH_SR_BSY);
}

unsigned char check_crc(unsigned int data, unsigned char framechkseq) {
    /*
     * Check if the CRC is valid for the given data.
        * :param data: The input data 32 bit long.
        * :param framechkseq: The frame check sequence, which is a 1 byte long value and should be >= 0x80.
     * :return: True if the CRC is valid, False otherwise.
     */
    unsigned char cnt = 31, bitpos;
    unsigned int rem, num;
    if (data < framechkseq) {
        if(data == (framechkseq & 0x7f)) return 1;
        else return 0;
    }
    /* Find first non zero bit */
    while((data & (1 << cnt)) == 0) cnt--;
    /* initialize bit position */
    bitpos = cnt - 7;
    num = (data & (0xFFU << bitpos)) >> bitpos;
    rem = framechkseq;
    while(num >= (1 << 7)){
        rem = num ^ framechkseq;
        while(bitpos > 0) {
            bitpos --;
            rem = (rem << 1) | ((data & (1 << bitpos)) >> bitpos);
            if (rem  >= (1 << 7)) break;
        }
        num = rem & 0xFF;
    }
    return (rem==0);
}

void check_receive(){
	uint8_t bytes[4];
	uint32_t offset = 0;
	uint32_t count = 0;
	uint32_t size;
	unsigned char crc;
	unsigned char crc_check = 0;
	uint32_t temp = 0xFFFFFF;
	uint32_t num;
	uint8_t x;
	/* receive the request frame ID */
	uint8_t rx_buff = app_req_frame();
	/* if request frame ID == 0x3 Flash software */
	if(rx_buff == 0x3){
		/*Unlock flash*/
		app_flash_write_unlock();
		/*send an ACK indicating server ready for request*/
		uart_write(0x1);
		/* Client sends total size of flash file */
		for(int i=0;i<2;i++){
			bytes[i] = uart_receive();
		}
		size = bytes[0]<<8 | bytes[1];
		if(size!=0){
			app_sector_erase();
			/*sending ACK for sector erase*/
			uart_write(0x1);
		}
		else{
			return;
		}
		size = size/3;
		while(size != 0){
			/*get 4 bytes of data*/
			for(int i=0;i<4;i++){
				bytes[i] = uart_receive();
			}
			num = (bytes[0]<<24) | (bytes[1]<<16) | (bytes[2]<<8) | (bytes[3]);
			crc = check_crc(num,0b10101010);
			if(crc == 1){
				num >>= 7;
				bytes[0] = (num & 0xFF0000)>>16;
				bytes[1] = (num & 0x00FF00)>>8;
				bytes[2] = num & 0x0000FF;
				app_write_byte(START_ADDR+offset,bytes[2]);
				offset++;
				app_write_byte(START_ADDR+offset,bytes[1]);
				offset++;
				app_write_byte(START_ADDR+offset,bytes[0]);
				offset++;
				crc_check = (crc_check | !crc);
			}
			else{
				/*corrupt data*/
				uart_write(0xF);
			}
			size--;
			/* ACK , send next 4 bytes */
			uart_write(0x1);
		}
		x = 1;
	}
	else{
		/*send NACK*/
		uart_write(0xF);
	}
}
