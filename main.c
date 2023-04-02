
#include "mcc_generated_files/system.h"
#include "mcc_generated_files/led.h"
#include "RC522.h"
#include "mcc_generated_files/delay.h"
#include "mcc_generated_files/led.h"
#include "mcc_generated_files/spi1.h"

/*
                         Main application
 */
int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    LED_Initialize();
    initialize_RC522();
    
    
    
    clearFifoBuffer();
    struct FIFO fifo;

    
    writeToRegister(FIFODataReg, 0x01);
    writeToRegister(FIFODataReg, 0x02);
    writeToRegister(FIFODataReg, 0x03);
    writeToRegister(FIFODataReg, 0x04);
    writeToRegister(FIFODataReg, 0x05);
    writeToRegister(FIFODataReg, 0x06);

    uint8_t buf[] = {0x01, 0x02, 0x03};
    //Write_FIFO(buf, sizeof(buf));
    
    
    fifo = Read_FIFO();
    uint8_t hj = getFifoSize();
    

    int km = 7;
    while (1)
    {
        uint8_t fifoSize = getFifoSize();
        if(fifoSize != 4){
            int k = 9;
            LED_On();
        }

        if(fifoSize > 1){
            int k = 56;
        }        
        //int k = 7;
    }

    return 1;
}
/**
 End of File
*/

