/*
 * File:   RC522.c
 * Author: Johannes Claudius Thomsen
 *
 * Created on March 30, 2023, 4:49 PM
 */

#include "mcc_generated_files/spi1.h"
#include "RC522.h"
#include <xc.h> // include processor files - each processor file is guarded.  
#include "mcc_generated_files/delay.h"
#include <string.h>


//Buffers
uint8_t dummyReadResponse[2];
uint8_t write_fifo_response[64];
uint8_t read_fifo_response[3];
uint8_t bytesInFifoResponse[3];  
uint8_t modRegInitResponse[3];
uint8_t RxModeRegInitResponse[3];
uint8_t RxSelRegInitResponse[3];
uint8_t RxThresholdRegInitResponse[3];
uint8_t activate_receiver_response[3];
uint8_t softResetCmd_response[3];
uint8_t clearCryptoBitCmd_response[3];
uint8_t fifo[FIFO_SIZE];
uint8_t modemStatusResponse[3];
uint8_t TxModeRegInitResponse[3];
uint8_t TxControlRegResponse[3];
uint8_t TxASKRegInitResponse[3];
uint8_t TxSelRegInitResponse[3];
uint8_t receiverGainRegResponse[3];
uint8_t ComIrqRegInitResponse[3];
uint8_t getStatusRegCmdResponse[3];
uint8_t transciveWakeUpResponse[3];

uint8_t read_buffer[2];

void writeToRegister(uint8_t register_number, uint8_t data){      
    uint8_t write_command[] = {register_number, data};
    toggleSlaveSelect();
        SPI1_Exchange8bitBuffer(write_command, 2, transciveWakeUpResponse);
    toggleSlaveSelect();
    int kb = 0;
    return;
}

uint8_t readRegister(uint8_t register_to_read){
    
    uint8_t * readPtr;
    uint8_t read_cmd = register_to_read + 0x80;
    readPtr = &read_cmd;
    
    toggleSlaveSelect();
        SPI1_Exchange8bitBuffer(readPtr, 2, read_buffer);
    toggleSlaveSelect();
    return read_buffer[1];
}

/*

void transceive(){
    //uint8_t wakeupMifareCmd[] = {0x52};
    //writeBytesToFifo(wakeupMifareCmd);
    uint8_t testWrite[] = {0x30, 0x00, 0x23, 0x31};   
    Write_FIFO(testWrite, sizeof(testWrite));
    toggleSlaveSelect();
        SPI1_Exchange8bitBuffer(transciveWakeUp, 2, transciveWakeUpResponse);
    toggleSlaveSelect();
    return;
}

uint8_t getStatusReg(){
    toggleSlaveSelect();
        SPI1_Exchange8bitBuffer(getStatusRegCmd, 2, getStatusRegCmdResponse);
    toggleSlaveSelect();
    return getStatusRegCmdResponse[1];
}


uint8_t * getModemStatus(){
    toggleSlaveSelect();
        SPI1_Exchange8bitBuffer(getModemStatusCmd, 3, modemStatusResponse);
    toggleSlaveSelect();
    //modemStatus = &modemStatusResponse[2];
    return modemStatusResponse;    
}

*/

 /*
 * Description:  Initialize the RC522 by sending a dummy read command.
 * this is just a bug fix, but this function will need to be run before usages of the module
 * in order for it to work correctly.  
 */
void initialize_RC522(){
    readRegister(DummyRead);

   // uint8_t softResetCmd[] = {0b00000010, 0b00001111};
    
    //Soft reset device
    writeToRegister(CommandReg, PCD_SoftReset);
            /*
    toggleSlaveSelect();
        SPI1_Exchange8bitBuffer(softResetCmd, 2, softResetCmd_response);
    toggleSlaveSelect();
             * */
    DELAY_milliseconds(500);
    
/*   
    //Clear crypto flag
    toggleSlaveSelect();
        SPI1_Exchange8bitBuffer(clearCryptoBitCmd, 2, clearCryptoBitCmd_response);
    toggleSlaveSelect();   
*/
      
    return;
}

uint8_t getFifoSize(){
    uint8_t size = readRegister(FIFOLevelReg);
    return size;
}

/*
 * @Summary
 *  get the FIFO content
 * 
 * @Description
 *  Make a read to the FIFOReg and read all bytes from the FIFO. 
 *  The FIFO will be empty after this call. 
 *  Read the size of the FIFO before this call. 
 * 
 * @Return
 *  A FIFO struct containing the size of the fifo and a 64 byte array. 
 */

struct FIFO Read_FIFO(){ 
    struct FIFO fifo;
    memset(fifo.content, '\0', 64);
    fifo.size = getFifoSize();    
    for(int i = 0 ; i < fifo.size ; i++){
        fifo.content[i] = readRegister(FIFODataReg);
    }
    return fifo;
}



void Write_FIFO(uint8_t * buffer_to_write, uint16_t number_of_bytes){
    
    uint8_t write_fifo[2] = {FIFODataReg};
    
    for(int i = 0 ; i < number_of_bytes ; i++){
        write_fifo[1+i] = buffer_to_write[i];  
    } 
    toggleSlaveSelect();
        SPI1_Exchange8bitBuffer(write_fifo, number_of_bytes + 1, write_fifo_response);
    toggleSlaveSelect();
    return;
}

void clearFifoBuffer(){
    writeToRegister(FIFOLevelReg, 0x80);
    return;
}

void toggleSlaveSelect(){
    _LATB15 = ~_LATB15;
    return;
}