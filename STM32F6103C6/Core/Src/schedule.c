/*
 * schedule.c
 *
 *  Created on: Nov 28, 2022
 *      Author: Hoang Tri
 */
#include "main.h"
#include "schedule.h"
#include "global.h"
TaskLIST SCH_TASKS_LIST;

void SCH_Init(void) {
	SCH_TASKS_LIST.head = NULL;
	SCH_TASKS_LIST.size = 0;
}
// Assume Task ID of Schedule_TASK_LIST = index ( task id = 0 -> index = 0; Task id= 1 -> index=1)
uint32_t SCH_Add_Task(void (* pFunction)(void), uint32_t DELAY, uint32_t PERIOD) {
	Node_Task *node = (Node_Task *)malloc(sizeof(Node_Task));
	node->task.pTask = pFunction;
	node->task.Delay = DELAY;
	node->task.Period = PERIOD;
	node->task.RunMe = 0;
	uint8_t Index = 0;
	if(TIMER_CYCLE > 0) {
		node->task.Delay /= TIMER_CYCLE;
	}
	if(SCH_TASKS_LIST.size == 0) {
		node->next = SCH_TASKS_LIST.head;
		SCH_TASKS_LIST.head = node;
	}
	else
	{
		Node_Task *cur = SCH_TASKS_LIST.head;
		Node_Task *prev = NULL;
		while(cur != NULL && node->task.Delay > cur->task.Delay) {
			node->task.Delay =node->task.Delay-cur->task.Delay;
			prev = cur;
			cur = cur->next;
			Index++;
		}
		if(!prev) { // prev == NULL
			node->next = cur;
			cur->task.Delay =cur->task.Delay- node->task.Delay;
			SCH_TASKS_LIST.head = node;
		}
		else {
			prev->next = node;
			node->next = cur;
			if(cur) {
				cur->task.Delay =cur->task.Delay-node->task.Delay;
			}
		}
	}
	SCH_TASKS_LIST.size++;
	return Index;
	// return index is return id of task, because I assume ID = index
}

void SCH_Update(void) {
	if(SCH_TASKS_LIST.head->task.Delay == 0)
	{
		SCH_TASKS_LIST.head->task.RunMe = 1;
	}
	else
	{
		SCH_TASKS_LIST.head->task.Delay--;
	}
}
void SCH_Delete_Task(uint32_t TASK_INDEX) {
	if(TASK_INDEX < 0 || TASK_INDEX >= SCH_TASKS_LIST.size)
	{
		// Delete_Task is ERROR
		   return;
	}
	Node_Task * Node_temp = SCH_TASKS_LIST.head;
	if(TASK_INDEX == 0)
	{
		SCH_TASKS_LIST.head = Node_temp->next;
		SCH_TASKS_LIST.head->task.Delay = SCH_TASKS_LIST.head->task.Delay+Node_temp->task.Delay;
	}
	else {
		uint32_t index = 0;
		Node_Task *cur = SCH_TASKS_LIST.head;
		while(index < TASK_INDEX - 1) {
			cur = cur->next;
			index++;
		}
		Node_temp = cur->next;
		cur->next = Node_temp->next;
		cur->next->task.Delay = cur->next->task.Delay+ Node_temp->task.Delay;
	}
	free(Node_temp);
	Node_temp = NULL;
	SCH_TASKS_LIST.size--;
}
void SCH_Dispatch_Tasks(void) {
	if(SCH_TASKS_LIST.head->task.RunMe == 1) {
		(*SCH_TASKS_LIST.head->task.pTask)();
		// IF period of task = 0 => "One shot task " -> permanently deleted
		if(SCH_TASKS_LIST.head->task.Period > 0)
		{
			SCH_Add_Task(SCH_TASKS_LIST.head->task.pTask, SCH_TASKS_LIST.head->task.Period, SCH_TASKS_LIST.head->task.Period);
		}
		// one-shot task
		SCH_Delete_Task(0);
	}
}


