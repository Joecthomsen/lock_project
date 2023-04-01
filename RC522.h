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

struct FIFO{
    uint16_t size;
    uint8_t content[64];
};

void initialize_RC522();
void turnOnAntenna();   //perhaps deprecated
void transceive();
uint8_t getFifoSize();
//void Read_FIFO(uint8_t * receving_buffer);
struct FIFO Read_FIFO();
void Write_FIFO(uint8_t * buffer_to_write, uint16_t number_of_bytes);
void Write_FIFO_Append_CRC();
void clearFifoBuffer();
uint8_t * getModemStatus();
uint8_t getStatusReg();
void toggleSlaveSelect();   //Move this function to SPI library



#endif	/* XC_HEADER_TEMPLATE_H */

