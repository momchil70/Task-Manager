#include "ListTasksCommand.h"
#include "System.h"

ListTasksCommand::ListTasksCommand(System* s, bool marker) : Command(s)
{
	this->marker = marker;
}

void ListTasksCommand::execute() const
{
	try {
		if (!marker)
			system->getActiveUser().listTasks();
		else
			system->getActiveUser().listDashboard();
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}
