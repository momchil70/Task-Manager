#include "CommandFactory.h"

Command* createCommand(const String& command, System* s)
{
	if (command == "login") {
		return new LoginCommand(s);
	}
	if (command == "logout") {
		return new LogoutCommand(s);
	}
	if (command == "exit") {
		return new ExitCommand(s);
	}
	if (command == "register") {
		return new RegisterCommand(s);
	}
	if (command == "add_task") {
		return new AddTaskCommand(s);
	}
	if (command == "list_tasks") {
		return new ListTasksCommand(s, 0);
	}
	if (command == "list_tasks_ondate") {
		return new ListDateCommand(s);
	}
	if (command == "list_completed") {
		return new ListCompletedCommand(s);
	}
	if (command == "list_dashboard") {
		return new ListTasksCommand(s, 1);
	}
	if (command == "update_task_name") {
		return new UpdateTaskCommand(s, 0);
	}
	if (command == "update_task_description") {
		return new UpdateTaskCommand(s, 1);
	}
	if (command == "start_task") {
		return new StartTaskCommand(s);
	}
	if (command == "add_task_to_dashboard") {
		return new AddDashboardCommand(s);
	}
	if (command == "remove_task_from_dashboard") {
		return new RemoveFromDashCommand(s);
	}
	if (command == "delete_task") {
		return new DeleteTaskCommand(s);
	}
	if (command == "finish_task") {
		return new FinishCommand(s);
	}
	if (command == "get_task_with_id") {
		return new GetTaskCommand(s, 0);
	}
	if (command == "get_task_with_name") {
		return new GetTaskCommand(s, 1);
	}

	throw std::exception("Non existing command!");
}
