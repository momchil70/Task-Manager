#include "DeleteTaskCommand.h"
#include "System.h"

DeleteTaskCommand::DeleteTaskCommand(System* s) : Command(s)
{
}

void DeleteTaskCommand::execute() const
{
	unsigned id;
	std::cin >> id;

	try {
		system->getActiveUser().deleteTask(id);
		std::cout << "Task deleted successfully!" << std::endl;
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}
