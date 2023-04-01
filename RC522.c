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

//Read Commands
uint8_t dummy_read[] = {10000000, 0x00};
uint8_t read_fifo[] = {0b10010010, 0x00};
uint8_t getBytesInFifoCmd[] = {0b10010100, 0x00};   
uint8_t getModemStatusCmd[] = {0b10010000, 0x00};
uint8_t getStatusRegCmd[] = {0b10001110, 0x00};

//Write commands
uint8_t clearFifoBufferCmd[] = {0b00010100, 0x80};
uint8_t write_fifo[2] = {0b00010010}; //This command needs a data parameter.
uint8_t activate_receiver_cmd[] = {0b00000010, 0b00001000};
uint8_t softResetCmd[] = {0b00000010, 0b00001111};
uint8_t modRegInit[] = {0b00100010, 0b1000000};
uint8_t RxModeRegInit[] = {0b00011010, 0b10000000};
uint8_t RxSelRegInit[] = {0b00101110, 0b01111111};
uint8_t clearCryptoBitCmd[] = {0b00010000, 0b00000000};
uint8_t RxThresholdRegInit[] = {0b00110000, 0b00000000};
uint8_t TxModeRegInit[] = {0b00100100, 0b10000000};
uint8_t TxControlReg[] = {0b00101000, 0b11111011};
uint8_t TxASKRegInit[] = {0b00101010, 0b01000000};
uint8_t TxSelRegInit[] = {0b00101100, 0b00000010};
uint8_t receiverGainReg[] = {0b01001100, 0b01110000};
uint8_t ComIrqRegInit[] = {0b00001000, 0b10100000}; //Interrupt control register
uint8_t transciveWakeUp[] = {0b00000010, 0b00001100};


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


/*
 * Description:  Initialize the RC522 by sending a dummy read command.
 * this is just a bug fix, but this function will need to be run before usages of the module
 * in order for it to work correctly.  
 */
void initialize_RC522(){
    //Dummy read.
    toggleSlaveSelect();
        SPI1_Exchange8bitBuffer(dummy_read, 2, dummyReadResponse);
    toggleSlaveSelect();
    
    //Clear crypto flag
    toggleSlaveSelect();
        SPI1_Exchange8bitBuffer(clearCryptoBitCmd, 2, clearCryptoBitCmd_response);
    toggleSlaveSelect();
    
    //Soft reset device
    toggleSlaveSelect();
        SPI1_Exchange8bitBuffer(softResetCmd, 2, softResetCmd_response);
    toggleSlaveSelect();
    DELAY_milliseconds(500);
    
    toggleSlaveSelect();
        SPI1_Exchange8bitBuffer(modRegInit, 2, modRegInitResponse);
    toggleSlaveSelect();
    
    //Init RxModReg - basic Rx settings register
    toggleSlaveSelect();
        SPI1_Exchange8bitBuffer(RxModeRegInit, 2, RxModeRegInitResponse);
    toggleSlaveSelect();
    
    //Init RxModReg - basic Rx settings register
    toggleSlaveSelect();
        SPI1_Exchange8bitBuffer(RxSelRegInit, 2, RxSelRegInitResponse);
    toggleSlaveSelect();
    
    //Init RxModReg - basic Rx settings register
    toggleSlaveSelect();
        SPI1_Exchange8bitBuffer(RxThresholdRegInit, 2, RxThresholdRegInitResponse);
    toggleSlaveSelect();
    
    
    toggleSlaveSelect();
        SPI1_Exchange8bitBuffer(TxModeRegInit, 2, TxModeRegInitResponse);
    toggleSlaveSelect();
    
    toggleSlaveSelect();
        SPI1_Exchange8bitBuffer(TxControlReg, 2, TxControlRegResponse);
    toggleSlaveSelect();
    
    toggleSlaveSelect();
        SPI1_Exchange8bitBuffer(TxASKRegInit, 2, TxASKRegInitResponse);
    toggleSlaveSelect();
    
    toggleSlaveSelect();
        SPI1_Exchange8bitBuffer(TxSelRegInit, 2, TxSelRegInitResponse);
    toggleSlaveSelect();
    
    toggleSlaveSelect();
        SPI1_Exchange8bitBuffer(receiverGainReg, 2, receiverGainRegResponse);
    toggleSlaveSelect();
    
    toggleSlaveSelect();
        SPI1_Exchange8bitBuffer(ComIrqRegInit, 2, ComIrqRegInitResponse);
    toggleSlaveSelect();
    
    
    
    return;
}

/*
 * @Summary
 *  Activates the receiver circuits 
 * 
 * @Description
 *  Make a write to the commands register, activates the receiver circuits
 * for one read. The receiver turns off after one read.
 */
void turnOnAntenna(){
    toggleSlaveSelect();
        SPI1_Exchange8bitBuffer(activate_receiver_cmd, 2,  activate_receiver_response);
    toggleSlaveSelect();
    return;
}

/*
 * @Summary
 *  get the FIFO size
 * 
 * @Description
 *  Make a read to the FIFOReg
 * 
 * @Return
 *  An unsigned 8 but integer.
 */
uint8_t getFifoSize(){
    toggleSlaveSelect();
        SPI1_Exchange8bitBuffer(getBytesInFifoCmd, 2, bytesInFifoResponse);
    toggleSlaveSelect();
    return bytesInFifoResponse[1];
}

/*
 * @Summary
 *  get the FIFO content
 * 
 * @Description
 *  Make a read to the FIFOReg and read all bytes from the FIFO. 
 *  The FIFO will be empty after this call. 
 *  Read the size of the FIFO before this call. 
 */

struct FIFO Read_FIFO(){ 
    struct FIFO fifo;
    memset(fifo.content, '\0', 64);
    fifo.size = getFifoSize();    
    for(int i = 0 ; i < fifo.size ; i++){
        toggleSlaveSelect();
            SPI1_Exchange8bitBuffer(read_fifo, 2, read_fifo_response);
            fifo.content[i] = read_fifo_response[1];
        toggleSlaveSelect();
    }
     
    return fifo;
}


/*

void Read_FIFO(uint8_t * receive_buffer){    
    uint8_t fifo_size = getFifoSize();    
    for(int i = 0 ; i < fifo_size ; i++){
        toggleSlaveSelect();
            SPI1_Exchange8bitBuffer(read_fifo, 2, read_fifo_response);
            fifo[i] = read_fifo_response[1];
        toggleSlaveSelect();
    }
    for(int i = 0 ; i < 64 ; i++){
        receive_buffer[i] = fifo[i];
    }   
    return;
}
 * 
 */

void Write_FIFO(uint8_t * buffer_to_write, uint16_t number_of_bytes){
        ///Write one byte with value 0x27 to FIFO 
    for(int i = 0 ; i < number_of_bytes ; i++){
        write_fifo[1+i] = buffer_to_write[i];  
    }
  
    toggleSlaveSelect();
        SPI1_Exchange8bitBuffer(write_fifo, number_of_bytes + 1, write_fifo_response);
    toggleSlaveSelect();
    return;
}

void clearFifoBuffer(){
    toggleSlaveSelect();
        SPI1_Exchange8bitBuffer(clearFifoBufferCmd, 2, dummyReadResponse);
    toggleSlaveSelect();
    return;
}

void toggleSlaveSelect(){
    _LATB15 = ~_LATB15;
    return;
}