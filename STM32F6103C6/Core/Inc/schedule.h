/*
 * schedule.h
 *
 *  Created on: Nov 28, 2022
 *      Author: Hoang Tri
 */

#ifndef INC_SCHEDULE_H_
#define INC_SCHEDULE_H_
#include "global.h"
#define TIMER_CYCLE 	10       // ngat timer 10ms
void SCH_Init(void);
uint32_t SCH_Add_Task(void (* pFunction)(void), uint32_t DELAY, uint32_t PERIOD);
void SCH_Delete_Task(uint32_t TASK_INDEX);
void SCH_Dispatch_Tasks(void);
void SCH_Update(void);

#endif /* INC_SCHEDULE_H_ */
