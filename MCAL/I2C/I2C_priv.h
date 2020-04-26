/*
 * I2C_priv.h
 *
 *  Created on: Apr 25, 2020
 *      Author: hp
 */

#ifndef MCAL_I2C_I2C_PRIV_H_
#define MCAL_I2C_I2C_PRIV_H_

#define TWBR *((volatile u8 *)0x20)
#define TWCR *((volatile u8 *)0x56)
#define TWSR *((volatile u8 *)0x21)
#define TWDR *((volatile u8 *)0x23)
#define TWAR *((volatile u8 *)0x22)


#define I2C_ONE								1
#define I2C_MAX_SLAVES						127



#define TWBR_VALUE							( (F_CPU - 16*SCL_FREQUENCY) / (2*SCL_FREQUENCY * I2C_PRESCALER) )

#define SET_TWBR_VALUE						TWBR = TWBR_VALUE


#define I2C_PRESCALER_1						1
#define I2C_PRESCALER_4						4
#define I2C_PRESCALER_16					16
#define I2C_PRESCALER_64					64

#define SET_I2C_PRESCALER_1					TWSR&=~(1<<0) &(~(1<<1))


#define SET_I2C_PRESCALER_4					TWSR&=~(1<<1);\
											TWSR|= (1<<0)

#define SET_I2C_PRESCALER_16				TWSR&=~(1<<0);\
											TWSR|= (1<<1)

#define SET_I2C_PRESCALER_64				TWSR|= (1<<0) | (1<<1)



#define SET_I2C_ENABLE						TWCR|=(1<<2)



#define SET_ECU_ADDRESS					TWAR=ECU_ADDRESS




#define SET_START_CONDITION					TWCR|= (1<<5);
#define CLEAR_START_CONDITION				TWCR&=~(1<<5);
#define SET_STOP_CONDITION					TWCR|= (1<<4);
#define SET_ACKNOWLEDGE						TWCR|= (1<<6);


#define CLEAR_FLAG							TWCR|= (1<<7);


#define WAIT_FLAG							!((TWCR>>7) & 1)


#define SET_SLAVE_ADDRESS(Address)			TWDR=(Address<<1)
#define SET_SLAVE_ACTION(Action)			TWDR|=Action

#define SEND_DATA_REGISTER(Data)			TWDR=Data
#define RECIEVE_DATA_REGISTER(Data)			Data=TWDR



#define START_CONDITION_TRANSMIT			(TWSR & 0xf8) == 0x08
#define REPEAT_START_CONDITION_TRANSMIT		(TWSR & 0xf8) == 0x10
#define SLA_WRITE_TRANSMIT					(TWSR & 0xf8) == 0x18
#define SLA_READ_TRANSMIT					(TWSR & 0xf8) == 0x40
#define MASTER_DATA_TRANSMIT				(TWSR & 0xf8) == 0x28
#define SLAVE_DATA_RECIEVED					(TWSR & 0xf8) == 0x80
#define SLAVE_WRITE_RECIEVE_ADDRESS			(TWSR & 0xf8) == 0x60
#define SLAVE_READ_RECIEVE_ADDRESS			(TWSR & 0xf8) == 0xA8



#endif /* MCAL_I2C_I2C_PRIV_H_ */
