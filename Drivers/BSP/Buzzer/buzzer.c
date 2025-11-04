/*
 * buzzer.c
 *
 *  Created on: Oct 21, 2025
 *      Author: dariu
 */

#include "buzzer.h"

extern I2C_HandleTypeDef hi2c2;

#define PCF7_ADDR7 (0x20u)  //Address
#define PCF7_ADDR8 (PCF7_ADDR7 <<1 ) //Address for HAL

static uint8_t pcf_shadow = 0xFF; //shadow register
static uint8_t pcf_addr8 = PCF7_ADDR8; //Address for HAL

static uint8_t pcf_present=0; //device status, 0 for not found, 1 for found

static HAL_StatusTypeDef PCF_Write(uint8_t v){ //v is the data you wanna write
	return HAL_I2C_Master_Transmit(&hi2c2, pcf_addr8, &v, 1, 20); // only write one byte, with 20 ms overtime limit
}

static HAL_StatusTypeDef PCF_Read(uint8_t *a){ //*a is the address you want to receive the data
	return HAL_I2C_Master_Receive(&hi2c2, pcf_addr8, a, 1, 20); //same 20 ms overtime
}


void Buzzer_Init(void){
	if (HAL_I2C_IsDeviceReady(&hi2c2, pcf_addr8, 2, 10)==HAL_OK){ //check whether the device is online, check 2 times
		pcf_present=1;

		if(PCF_Read(&pcf_shadow)!= HAL_OK){ //read current data for backup
			pcf_shadow = 0xFF;
		}

		pcf_shadow |= (1U<<0); //change the P0 to 1 (make sure always off)
		PCF_Write(pcf_shadow); //write back to chip
	}
	else{
		pcf_present=0; //offline
	}

}

void Buzzer_On(void){
	if(!pcf_present){
		return;
	}
	pcf_shadow &= ~(1U<<0); //P0 to 0
	PCF_Write(pcf_shadow);
}

void Buzzer_Off(void){
	if(!pcf_present){
		return;
	}
	pcf_shadow |= (1U<<0); //change the P0 to 1
	PCF_Write(pcf_shadow);
}

void Buzzer_Toggle(void){
	if(!pcf_present){
		return;
	}
	pcf_shadow ^= (1U<<0); //toggle the P0
	PCF_Write(pcf_shadow);
}
