/*
 * Task.c
 *
 *  Created on: Nov 28, 2022
 *      Author: Hoang Tri
 */
#include "Task.h"
void ToggleLEDRED_1()
{
	HAL_GPIO_TogglePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin);
}
void ToggleLEDRED_2()
{
	HAL_GPIO_TogglePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin);
}
void ToggleLEDRED_3()
{
	HAL_GPIO_TogglePin(LED_RED_3_GPIO_Port, LED_RED_3_Pin);
}
void ToggleLEDRED_4()
{
	HAL_GPIO_TogglePin(LED_RED_4_GPIO_Port, LED_RED_4_Pin);
}
void ToggleLEDRED_5()
{
	HAL_GPIO_TogglePin(LED_RED_5_GPIO_Port, LED_RED_5_Pin);
}


