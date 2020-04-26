/*
 * I2C_prog.c
 *
 *  Created on: Apr 25, 2020
 *      Author: hp
 */
#include "../../LIBRARY/stdTypes.h"
#include "../../LIBRARY/BIT_MATH.h"
#include "../../LIBRARY/errorStates.h"

#include "I2C_config.h"
#include "I2C_priv.h"


ERROR_STATES I2C_enuInitMaster	(void)
{
	ERROR_STATES error_enuState = ES_NOT_OK;

#if I2C_PRESCALER == I2C_PRESCALER_1
	SET_I2C_PRESCALER_1;
	SET_TWBR_VALUE;
	SET_I2C_ENABLE;
	error_enuState = ES_OK;

#elif I2C_PRESCALER == I2C_PRESCALER_4
	SET_I2C_PRESCALER_4;
	SET_TWBR_VALUE;
	SET_I2C_ENABLE;
	error_enuState = ES_OK;

#elif I2C_PRESCALER == I2C_PRESCALER_16
	SET_I2C_PRESCALER_16;
	SET_TWBR_VALUE;
	SET_I2C_ENABLE;
	error_enuState = ES_OK;

#elif I2C_PRESCALER == I2C_PRESCALER_64
	SET_I2C_PRESCALER_64;
	SET_TWBR_VALUE;
	SET_I2C_ENABLE;
	error_enuState = ES_OK;

#else
#error"The Selection of I2C_PRESCALER is Wrong"
#endif

	return error_enuState;
}



ERROR_STATES I2C_enuInitSlave	(void)
{
	ERROR_STATES error_enuState = ES_NOT_OK;

	SET_ECU_ADDRESS;
	SET_I2C_ENABLE;
	error_enuState = ES_OK;

	return error_enuState;
}



ERROR_STATES I2C_enuStartCondition	(void)
{
	ERROR_STATES error_enuState = ES_NOT_OK;

	SET_START_CONDITION;
	CLEAR_FLAG;
	while (WAIT_FLAG);
	if (START_CONDITION_TRANSMIT)
		error_enuState = ES_OK;

	return error_enuState;
}




ERROR_STATES I2C_enuRepeatStartCondition	(void)
{
	ERROR_STATES error_enuState = ES_NOT_OK;

	SET_START_CONDITION;
	CLEAR_FLAG;
	while (WAIT_FLAG);
	if (REPEAT_START_CONDITION_TRANSMIT)
		error_enuState = ES_OK;

	return error_enuState;
}



ERROR_STATES I2C_enuStopCondition	(void)
{
	ERROR_STATES error_enuState = ES_NOT_OK;

	SET_STOP_CONDITION;
	CLEAR_FLAG;
	error_enuState = ES_OK;

	return error_enuState;
}



ERROR_STATES I2C_enuSendSlaveAddress	(u8 Copy_u8SlaveAddress , u8 Copy_u8Action)
{
	ERROR_STATES error_enuState = ES_NOT_OK;


	if (Copy_u8SlaveAddress <= I2C_MAX_SLAVES) SET_SLAVE_ADDRESS(Copy_u8SlaveAddress);
	if (Copy_u8Action <= I2C_ONE)              SET_SLAVE_ACTION (Copy_u8Action);
	CLEAR_START_CONDITION;
	CLEAR_FLAG;
	while (WAIT_FLAG);
	if (SLA_WRITE_TRANSMIT)
		error_enuState = ES_OK;

	else if (SLA_READ_TRANSMIT)
		error_enuState = ES_OK;

	return error_enuState;
}



ERROR_STATES I2C_enuSlaveCheckHisAdress (void)
{
	ERROR_STATES error_enuState = ES_NOT_OK;

	SET_ACKNOWLEDGE;
	CLEAR_FLAG;
	while (WAIT_FLAG);
	if (SLAVE_WRITE_RECIEVE_ADDRESS)
		error_enuState = ES_OK;
	else if(SLAVE_READ_RECIEVE_ADDRESS)
		error_enuState = ES_OK;

	return error_enuState;
}




ERROR_STATES I2C_enuMasterSendData	(u8 Copy_u8Data)
{
	ERROR_STATES error_enuState = ES_NOT_OK;

	SEND_DATA_REGISTER(Copy_u8Data);
	CLEAR_FLAG;
	while (WAIT_FLAG);
	if (MASTER_DATA_TRANSMIT)
		error_enuState = ES_OK;

	return error_enuState;
}


ERROR_STATES I2C_enuSlaveRecieveData	(u8 * Copy_Pu8Data)
{
	ERROR_STATES error_enuState = ES_NOT_OK;

	CLEAR_FLAG;
	while (WAIT_FLAG);
	if (SLAVE_DATA_RECIEVED)
	{
		RECIEVE_DATA_REGISTER(* Copy_Pu8Data);
		error_enuState = ES_OK;
	}

	return error_enuState;
}
