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


//Dummy read register

#define     DummyRead               0x00

// Command and status registers

#define     CommandReg              0x01 << 1	// starts and stops command execution
#define     ComIEnReg				0x02 << 1	// enable and disable interrupt request control bits
#define		DivIEnReg				0x03 << 1	// enable and disable interrupt request control bits
#define		ComIrqReg				0x04 << 1	// interrupt request bits
#define		DivIrqReg				0x05 << 1	// interrupt request bits
#define		ErrorReg				0x06 << 1	// error bits showing the error status of the last command executed 
#define		Status1Reg				0x07 << 1	// communication status bits
#define		Status2Reg				0x08 << 1	// receiver and transmitter status bits
#define		FIFODataReg				0x09 << 1	// input and output of 64 byte FIFO buffer
#define		FIFOLevelReg			0x0A << 1	// number of bytes stored in the FIFO buffer
#define		WaterLevelReg			0x0B << 1	// level for FIFO underflow and overflow warning
#define		ControlReg				0x0C << 1	// miscellaneous control registers
#define		BitFramingReg			0x0D << 1	// adjustments for bit-oriented frames
#define		CollReg					0x0E << 1	// bit position of the first bit-collision detected on the RF interface

//  Communication

#define		ModeReg					0x11 << 1	// defines general modes for transmitting and receiving 
#define		TxModeReg				0x12 << 1	// defines transmission data rate and framing
#define		RxModeReg				0x13 << 1	// defines reception data rate and framing
#define 	TxControlReg            0x14 << 1	// controls the logical behavior of the antenna driver pins TX1 and TX2
#define		TxASKReg				0x15 << 1	// controls the setting of the transmission modulation
#define		TxSelReg				0x16 << 1	// selects the internal sources for the antenna driver
#define		RxSelReg				0x17 << 1	// selects internal receiver settings
#define		RxThresholdReg			0x18 << 1	// selects thresholds for the bit decoder
#define		DemodReg				0x19 << 1	// defines demodulator settings
#define		MfTxReg					0x1C << 1	// controls some MIFARE communication transmit parameters
#define		MfRxReg					0x1D << 1	// controls some MIFARE communication receive parameters
#define		SerialSpeedReg			0x1F << 1	// selects the speed of the serial UART interface
	
//   Configuration

#define		CRCResultRegH			0x21 << 1	// shows the MSB and LSB values of the CRC calculation
#define		CRCResultRegL			0x22 << 1
#define		ModWidthReg				0x24 << 1	// controls the ModWidth setting?
#define		RFCfgReg				0x26 << 1	// configures the receiver gain
#define		GsNReg					0x27 << 1	// selects the conductance of the antenna driver pins TX1 and TX2 for modulation 
#define		CWGsPReg				0x28 << 1	// defines the conductance of the p-driver output during periods of no modulation
#define		ModGsPReg				0x29 << 1	// defines the conductance of the p-driver output during periods of modulation
#define		TModeReg				0x2A << 1	// defines settings for the internal timer
#define		TPrescalerReg			0x2B << 1	// the lower 8 bits of the TPrescaler value. The 4 high bits are in TModeReg.
#define		TReloadRegH				0x2C << 1	// defines the 16-bit timer reload value
#define		TReloadRegL				0x2D << 1
#define		TCounterValueRegH		0x2E << 1	// shows the 16-bit timer value
#define		TCounterValueRegL		0x2F << 1

// Test Registers

#define		TestSel1Reg				0x31 << 1	// general test signal configuration
#define		TestSel2Reg				0x32 << 1	// general test signal configuration
#define		TestPinEnReg			0x33 << 1	// enables pin output driver on pins D1 to D7
#define		TestPinValueReg			0x34 << 1	// defines the values for D1 to D7 when it is used as an I/O bus
#define		TestBusReg				0x35 << 1	// shows the status of the internal test bus
#define		AutoTestReg				0x36 << 1	// controls the digital self-test
#define		VersionReg				0x37 << 1	// shows the software version
#define		AnalogTestReg			0x38 << 1	// controls the pins AUX1 and AUX2
#define		TestDAC1Reg				0x39 << 1	// defines the test value for TestDAC1
#define		TestDAC2Reg				0x3A << 1	// defines the test value for TestDAC2
#define		TestADCReg				0x3B << 1	// shows the value of ADC I and Q channels

// Commands

#define		PCD_Idle				0x00		// no action, cancels current command execution
#define		PCD_Mem					0x01		// stores 25 bytes into the internal buffer
#define		PCD_GenerateRandomID	0x02		// generates a 10-byte random ID number
#define		PCD_CalcCRC				0x03		// activates the CRC coprocessor or performs a self-test
#define		PCD_Transmit			0x04		// transmits data from the FIFO buffer
#define		PCD_NoCmdChange			0x07		// no command change, can be used to modify the CommandReg register bits without affecting the command, for example, the PowerDown bit
#define		PCD_Receive				0x08		// activates the receiver circuits
#define		PCD_Transceive 			0x0C		// transmits data from FIFO buffer to antenna and automatically activates the receiver after transmission
#define		PCD_MFAuthent 			0x0E		// performs the MIFARE standard authentication as a reader
#define		PCD_SoftReset			0x0F		// resets the MFRC522



//#define		FIFODataReg				0x09 << 1
//#define		FIFOLevelReg			0x0A << 1	// number of bytes stored in the FIFO buffer

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
void writeToRegister(uint8_t register_number, uint8_t data);
uint8_t readRegister(uint8_t register_to_read);
uint8_t * getModemStatus();
uint8_t getStatusReg();
void toggleSlaveSelect();   //Move this function to SPI library



#endif	/* XC_HEADER_TEMPLATE_H */

