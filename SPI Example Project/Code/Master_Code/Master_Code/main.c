/*
 * Master_Code.c
 *
 * Created: 10-Jul-20 12:01:02 AM
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


int main(void)
{
    volatile u8 Data = 0;		//Create a Variable to hold the Transmitted Data 
	
	/* Initialize PORTB */
	//Make SS Output
	DIO_VidSetPinDirection(4,portB,OUTPUT);
	//Make MOSI Output
	DIO_VidSetPinDirection(5,portB,OUTPUT);
	//Make SCK Output
	DIO_VidSetPinDirection(7,portB,OUTPUT);

	/* Initialize SPI */
	SPI_STC_Callback(SPI_Handler);
	SPI_Init ();

	//Send message to the first slave at the beginning	
	DIO_VidSetPinValue(4,portB,LOW);
	SPI_Transmit(Data); 	
	
    while (1) 
    {
		if (Binary_Semaphore)
		{
			//Delay for One Second
			delay_ms_Timer1(150);
			
			//Select the other Slave
			TOG_BIT(PORTB_REG,4);
			
			//Update Data
			Data = (Data % 0x100)+1 ;
			
			//transmit Data
			SPI_Transmit(Data);	
			
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


