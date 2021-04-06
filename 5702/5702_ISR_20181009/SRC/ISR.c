// Function List:
// 0. INT0								#define ISRInt0    0
// 1. Timer0	 						#define ISRTimer0  1
// 2. Timer1	 						#define ISRTimer1  3
// 3. Uart								#define ISRUart    4
// 4. Timer2 							#define ISRTimer2  5
// 5. I2C	 								#define ISRI2c     8
// 6. SPI	 								#define ISRSpi     9
// 7. Timer2 com(1) 			#define ISRCom1    10
// 8. Timer2 com(2)				#define ISRCom2    11
// 9. Timer2 com(3)				#define ISRCom3    12
// 10. Timer2 com(4)			#define ISRCom4    13
// 11. PWM1 							#define ISRPwm1    16
// 12. ADC 								#define ISRAdc     17
// The system clock frequency is IHRC 32MHz

#include "ISR.h"

//===================================================================================================//
//ISR init
//===================================================================================================//
void ISRinit(void)
{
	EX0 = 1;            											// Int 0 isr enable

	ET0 = 1;         						   						// Timer 0 isr enable

	ET1 = 1;         						  						// Timer 1 isr enable

	ES0 = 1;         						   						// Uart isr enable

	ET2 = 1;          						  					// Timer2 interrupt enable

	EI2C = 1;        						   						// I2C interrupt enable

	ESPI = 1;         						  					// SPI interrupt enable

	ET2C3 = 1;        						 						// Timer 2 com(3) interrupt enable
	ET2C2 = 1;        						 						// Timer 2 com(2) interrupt enable
	ET2C1 = 1;       						   						// Timer 2 com(1) interrupt enable
	ET2C0 = 1;       						   						// Timer 2 com(0) interrupt enable

	IEN4 |= 0x80;     						  					// PWM1 interrupt enable (EPWM1)

	IEN2 |= 0x02;     						 						// ADC interrupt enable (EADC)    
	
	EAL = 1;            											// Interrupt enable
	
	IP0 = L_ISR_IP0;
	IP1 = L_ISR_IP1;
}

//===================================================================================================//
//中断程序
//===================================================================================================//
//外部中断0
void INT0_ISR(void) interrupt ISRInt0         // Vector @  0x03
{
    // auto clear int0 flag
    IE0 = 0;         													// Clear INT0 flag
}
//定时器T0中断
void Timer0_ISR(void) interrupt ISRTimer0     // Vector @  0x0B
{
    // auto clear timer0 flag
    // TF0 = 0;         											// Clear Timer0 overflow flag
}
//定时器T1中断
void Timer1_ISR(void) interrupt ISRTimer1     // Vector @  0x1B
{
    // auto clear timer1 flag
    // TF1 = 0;         											// Clear Timer1 overflow flag
}
//Uart中断
void Uart_ISR(void) interrupt ISRUart         // Vector @  0x23
{
    TI0 = 0;            											// Clear transfer flag
    RI0 = 0;            											// Clear receiver flag
}
//定时器T2中断
void Timer2_ISR(void) interrupt ISRTimer2     // Vector @  0x2B
{
    TF2 = 0;            											// Clear Timer 2 overflow flag
    TF2RL = 0;          											// Clear Timer 2 external reload flag
}
//I2C中断
void I2C_ISR(void) interrupt ISRI2c           // Vector @  0x43
{
    I2CCON &= 0xF7;     											// Clear I2C flag (SI)        
}
//SPI中断
void SPI_ISR(void) interrupt ISRSpi           // Vector @  0x4B
{
    SPSTA &= 0x7F;      											// SPIF cleared by reading SPSTA.
    SPSTA &= 0xEF;      											// MODF cleared by SSN is at appropriate level and SPCON be writed
}

//T2 COM1中断
void COM0_ISR(void) interrupt ISRCom1         // Vector @  0x53
{
    // auto clear timer2 com0 flag
    //TF2C0 = 0;        											// Clear timer2 com0 interrupt edge flag
}
//T2 COM2中断
void COM1_ISR(void) interrupt ISRCom2         // Vector @  0x5B
{
    // auto clear timer2 com1 flag
    //TF2C1 = 0;        											// Clear timer2 com1 interrupt edge flag
}
//T2 COM3中断
void COM2_ISR(void) interrupt ISRCom3         // Vector @  0x63
{
    // auto clear timer2 com2 flag
    //TF2C2 = 0;        											// Clear timer2 com2 interrupt edge flag
}
//T2 COM4中断
void COM3_ISR(void) interrupt ISRCom4         // Vector @  0x6B
{
    // auto clear timer2 com0 flag
    //TF2C3 = 0;        											// Clear timer2 com3 interrupt edge flag
}
//PWM1 中断
void PWM1_ISR(void) interrupt ISRPwm1         // Vector @  0x83
{
    IEN4 &= 0xF7;       											// Clear PWM1 request (PWM1F)    
}

//-----------------------------------------------------------------------------------------------------------
void ADC_ISR(void) interrupt ISRAdc           // Vector @  0x9B
{
    IRCON2 &= 0xFB;     											// Clear ADC interrupt edge flag (ADCF)
}


