#include "ListTasksCommand.h"
#include "System.h"

ListTasksCommand::ListTasksCommand(System* s) : Command(s)
{
}

void ListTasksCommand::execute() const
{
	try {
		system->getActiveUser().listTasks();
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}
