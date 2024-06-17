#pragma once
#include "Command.h"
#include "LoginCommand.h"
#include "ExitCommand.h"
#include "RegisterCommand.h"
#include "AddTaskCommand.h"
#include "ListTasksCommand.h"
#include "StartTaskCommand.h"
#include "UpdateTaskCommand.h"
#include "AddDashboardCommand.h"
#include "RemoveFromDashCommand.h"
#include "Command.h"
#include "DeleteTaskCommand.h"
#include "System.h"

Command* createCommand(const String& command, System* s);
