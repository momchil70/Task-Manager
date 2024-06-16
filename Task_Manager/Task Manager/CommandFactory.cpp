#include "CommandFactory.h"

Command* createCommand(const String& command, System* s)
{
    if (command == "login") {
        return new LoginCommand(s);
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
        return new ListTasksCommand(s);
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

    throw std::exception("Non existing command!");
}
