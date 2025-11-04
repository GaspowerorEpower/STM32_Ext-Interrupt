/*
 * buzzer.h
 *
 *  Created on: Oct 21, 2025
 *      Author: dariu
 */

#ifndef BSP_BUZZER_BUZZER_H_
#define BSP_BUZZER_BUZZER_H_
#include "i2c.h"

void Buzzer_Init(void);

void Buzzer_On(void);

void Buzzer_Off(void);

void Buzzer_Toggle(void);

#endif /* BSP_BUZZER_BUZZER_H_ */
