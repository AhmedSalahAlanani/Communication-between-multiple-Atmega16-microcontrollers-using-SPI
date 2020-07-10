/*
 * Slave_Code.c
 *
 * Created: 10-Jul-20 12:01:48 AM
 * Author : Ahmed Salah
 */ 

#define		F_CPU		16000000UL


#include "DIO Driver/DIO_INIT.h"
#include "SPI Driver/SPI.h"
#include "delay_Timer1 Driver/delay_Timer1.h"


//	Global Variables
static volatile u8 Binary_Semaphore = 0;


//	Function Prototypes
void SPI_Handler(void);


//	Main Entry Point
int main(void)
{
	/* Initialize PORTB */
	//Make MISO Output
	DIO_VidSetPinDirection(6,portB,OUTPUT);
	
	/* Initialize PORTD */
	DIO_VidSetPortDirection(portD,OUTPUT);
	DIO_VidSetPortValue(portD,LOW);
	
	/* Initialize SPI */
	SPI_STC_Callback(SPI_Handler);
	SPI_Init ();

	
		
    while (1) 
    {
		
		if (Binary_Semaphore)
		{
			//Read what is received over the SPI and Output it to PORTD
			//PORTD_REG = SPI_Read();
			DIO_VidWritePortValue(PORTD_REG,SPI_Read());
			
			//Reset the Binary Semaphore
			Binary_Semaphore =0;
		}
		

    }
}


void SPI_Handler(void)
{
	//Set the Binary Semaphore
	Binary_Semaphore =1;
}

