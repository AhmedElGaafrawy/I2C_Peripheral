/*
 * I2C_int.h
 *
 *  Created on: Apr 25, 2020
 *      Author: hp
 */

#ifndef MCAL_I2C_I2C_INT_H_
#define MCAL_I2C_I2C_INT_H_

ERROR_STATES I2C_enuInitMaster	(void);

ERROR_STATES I2C_enuInitSlave	(void);

ERROR_STATES I2C_enuStartCondition	(void);

ERROR_STATES I2C_enuRepeatStartCondition	(void);

ERROR_STATES I2C_enuStopCondition	(void);

ERROR_STATES I2C_enuSendSlaveAddress	(u8 Copy_u8SlaveAddress , u8 Copy_u8Action);

ERROR_STATES I2C_enuSlaveCheckHisAdress (void);

ERROR_STATES I2C_enuMasterSendData	(u8 Copy_u8Data);

ERROR_STATES I2C_enuSlaveRecieveData	(u8 * Copy_Pu8Data);


#endif /* MCAL_I2C_I2C_INT_H_ */
