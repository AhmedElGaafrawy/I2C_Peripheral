/*
 * main.c
 *
 *  Created on: Apr 25, 2020
 *      Author: hp
 */
#include "../LIBRARY/stdTypes.h"
#include "../LIBRARY/BIT_MATH.h"
#include "../LIBRARY/errorStates.h"
#include "../LIBRARY/AVR_REG.h"


#include "../MCAL/I2C/I2C_int.h"
#define Master		0
#define Slave		1
#define Code		Slave

#if Code == Master

int main ()
{
	I2C_enuInitMaster();
	DDRA=0xff;
	DDRB=0xff;
	ERROR_STATES state;

	state = I2C_enuStartCondition();
	if (state==ES_OK)
	{
		state = I2C_enuSendSlaveAddress(1,0);
		if (state==ES_OK)
		{
			state = I2C_enuMasterSendData(63);
			if (state == ES_OK)
			{
				I2C_enuStopCondition();
			}
			else
				PORTB=1;
		}
		else
			PORTB=2;

	}
	else
		PORTB=4;
	return 0;
}

#elif Code == Slave

int main ()
{
	I2C_enuInitSlave();
	DDRA=0xff;
	DDRB=0xff;
	u8 y;
	ERROR_STATES state;

	state = I2C_enuSlaveCheckHisAdress();
	if (state == ES_OK)
	{
		state = I2C_enuSlaveRecieveData(&y);
		if (state == ES_OK)
		{
			PORTA=y;
		}
		else
			PORTB=8;
	}
	else
		PORTB=16;
	return 0;
}

#endif
