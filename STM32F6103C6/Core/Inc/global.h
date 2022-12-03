/*
 * global.h
 *
 *  Created on: Nov 28, 2022
 *      Author: Hoang Tri
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	void (*pTask)(void);
	uint32_t Delay;
	uint32_t Period;
	uint8_t RunMe;
} Task;
typedef struct Node_Task{
	Task task;
	struct Node_Task *next;
} Node_Task;

typedef struct {
	Node_Task *head;
	uint32_t size;
} TaskLIST;


#endif /* INC_GLOBAL_H_ */
