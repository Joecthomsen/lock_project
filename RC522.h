/*
 * Author: Johannes Claudius Thomsen
 * Date: Marts, 2023
 * Description: This library is created for the PIC24FJ128GA202 to communicate with 
 * the RC522 RFID module
 * 
 */

#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H
#define FIFO_SIZE 64

void initialize_RC522();
void turnOnAntenna();
uint8_t getFifoSize();
void getFifoContent(uint8_t * receving_buffer);
void writeByteToFifo(uint8_t * byte_to_write);
void clearFifoBuffer();
uint8_t * getModemStatus();
uint8_t getStatusReg();
void toggleSlaveSelect();



#endif	/* XC_HEADER_TEMPLATE_H */

