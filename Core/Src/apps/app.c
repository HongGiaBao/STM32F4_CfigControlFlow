/*
 * app.c
 *
 *  Created on: Aug 15, 2025
 *      Author: baohg1
 */

#include "app.h"

APP_STATES appState;

void InitializeApplications(void)
{
	/*Initialize global struct variables:*/
	InitializeGlobalVariables();
	/*Wating for all setting up is okay:*/
	HAL_Delay(10);
}

void InitializeGlobalVariables(void)
{
	/*Clear timer counter*/
	InitTimerCounter();

	/*Clear all buffer*/
	initDrvUSART();

	/*Init states of system*/
	InitializeAppState();
}

void InitializeAppState(void)
{
	appState = INITIALIZE_APP;
}

void RunSystemTasks(void)
{
	switch(appState)
	{
		case INITIALIZE_APP:
			if(IsInputSignalPresent() == SIGNAL_PRESENT)
			{
				PreprocessData();
				appState = PROCESS_CMD_APP;
				break;
			}
			appState = MOTOR_CONTROL_APP;
			break;
		case PROCESS_CMD_APP:
			ProcessCommand();
			appState = EXECUTE_CMD_APP;
			break;
		case EXECUTE_CMD_APP:
			ExecuteCommand();
			appState = PROCESS_FEEDBACK_APP;
			break;
		case PROCESS_FEEDBACK_APP:
			appState = MOTOR_CONTROL_APP;
			break;
		case MOTOR_CONTROL_APP:
			if(isSystemReady == true)
			{
				//Run control tasks ...
				ControlTasks();
			}
			appState = INITIALIZE_APP;
			break;
		default:
			break;
	}
}

SignalStatus IsInputSignalPresent(void)
{
	if(SCI2buffer.flag == 1)
	{
		return SIGNAL_PRESENT;
	}
	else
		return 0;
}

void PreprocessData()
{
//	preProcessUSART1();
	preProcessUSART2();
}

void ProcessCommand()
{}

void ExecuteCommand()
{}

