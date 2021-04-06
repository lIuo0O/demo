#ifndef _I2C_SLAVE_H_
#define _I2C_SLAVE_H_
//-----------------------------------------------------------------------------------------------------------------//
#include "sn8f5702.h"
//-----------------------------------------------------------------------------------------------------------------//
#define TIME_PERIOD_SEC   					  35 							 		   						 // Timeout Period(ms)
#define FCPU_HZ												32 									   						 // Fcpu(MHz)
#define TIME_PERIOD		((uint32_t)((TIME_PERIOD_SEC * FCPU_HZ) / 1.024))  // Timeout Period Value 	 	
//-----------------------------------------------------------------------------------------------------------------//
#define MAX_BUF_LEN   								100			// Transmit/Receive Maximum bytes				
#define I2C_SLAVE_ADDR								0xC0	// I2C Slave address
//-----------------------------------------------------------------------------------------------------------------//
// Master Transmitter/Receiver
#define I2C_START               			0x08   // A START condition has been transmitted
#define I2C_RESTART      							0x10   // A repeated START condition has been transmitted.
//-----------------------------------------------------------------------------------------------------------------//
// Master Transmitter
#define I2C_MT_SLA_ACK   							0x18   // SLA+W has been transmitted;ACK has been received
#define I2C_MT_SLA_NACK  							0x20   // SLA+W has been transmitted;not ACK has been received
#define I2C_MT_DATA_ACK  							0x28   // Data byte in I2CDAT has beentransmitted;ACK has been received
#define I2C_MT_DATA_NACK 							0x30   // Data byte in I2CDAT has beentransmitted;not ACK has been received
//-----------------------------------------------------------------------------------------------------------------//
// Master Receiver
#define I2C_MR_SLA_ACK   							0x40   // SLA+R has been transmitted;ACK has been received
#define I2C_MR_SLA_NACK  							0x48   // SLA+R has been transmitted;not ACK has been received
#define I2C_MR_DATA_ACK  							0x50   // Data byte has been received;ACK has been returned
#define I2C_MR_DATA_NACK 							0x58   // Data byte has been received;not ACK has been returned
//-----------------------------------------------------------------------------------------------------------------//
// Slave Receiver
#define I2C_SR_SLA_ACK    						0x60   // Own SLA+W has been received;ACK has been returned
#define I2C_SR_ARB_LOST_SLA_ACK  			0x68   // Arbitration lost in SLA+R/W as master;own SLA+W has been received, ACK returned
#define I2C_SR_GCALL_ACK   						0x70   // General call address (00H) has been received; ACK has been returned
#define I2C_SR_ARB_LOST_GCALL_ACK 		0x78   // Arbitration lost in SLA+R/W as master; general call address has been received, ACK returned
#define I2C_SR_DATA_ACK    						0x80   // Previously addressed with own SLV address; DATA has been received; ACK returned
#define I2C_SR_DATA_NACK   						0x88   // Previously addressed with own SLA; DATA byte has been received; not ACK returned
#define I2C_SR_GCALL_DATA_ACK  				0x90   // Previously addressed withgeneral call address;DATA has been received; ACK returned
#define I2C_SR_GCALL_DATA_NACK  			0x98   // Previously addressed withgeneral call address; DATA has been received; not ACK returned
#define I2C_SR_STOP     							0xA0   // A STOP condition or repeated START condition has been received while still addressed as SLV/REC or SLV/TRX
//-----------------------------------------------------------------------------------------------------------------//
// Slave Transmitter
#define I2C_ST_SLA_ACK   							0xA8   // Own SLA+R has been received;ACK has been returned
#define I2C_ST_ARB_LOST_SLA_ACK 			0xB0   // Arbitration lost in SLA+R/W as master; own SLA+R has been received, ACK has been returned.
#define I2C_ST_DATA_ACK   						0xB8   // Data byte has been transmitted; ACK will be received.
#define I2C_ST_DATA_NACK 							0xC0   // Data byte has been transmitted; not ACK has been received.
#define I2C_ST_LAST_DATA  						0xC8   // Last Data byte has been transmitted; ACK has been received.
//-----------------------------------------------------------------------------------------------------------------//
// Miscellaneous
#define I2C_NO_INFO   								0xF8   // No relevant state information available; SI=0
#define I2C_MR_ARB_LOST  							0x38   // Arbitration lost
#define I2C_BUS_ERROR  								0x00   // Bus error during MST or selected slave modes
//-----------------------------------------------------------------------------------------------------------------//
extern uint16_t code g_iToutPer;
//-----------------------------------------------------------------------------------------------------------------//
void i2c_slave_init (void);	
//-----------------------------------------------------------------------------------------------------------------//
#endif



