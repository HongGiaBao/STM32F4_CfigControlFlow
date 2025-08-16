/*
 * app.h
 *
 *  Created on: Aug 15, 2025
 *      Author: baohg1
 */

#ifndef INC_APPS_APP_H_
#define INC_APPS_APP_H_

#include "main.h"

typedef enum
{
	INITIALIZE_APP,
	PROCESS_CMD_APP,
	EXECUTE_CMD_APP,
	PROCESS_FEEDBACK_APP,
	MOTOR_CONTROL_APP,
} APP_STATES;

typedef enum
{
	SIGNAL_NONE = 0,
	SIGNAL_PRESENT,
} SignalStatus;

void InitializeApplications(void);
void InitializeGlobalVariables(void);
void RunSystemTasks(void);

SignalStatus IsInputSignalPresent(void);
void PreprocessData(void);
void ProcessCommand(void);
void ExecuteCommand(void);
void InitializeAppState(void);

#endif /* INC_APPS_APP_H_ */
