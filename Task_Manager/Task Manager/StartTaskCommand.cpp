#include "StartTaskCommand.h"

StartTaskCommand::StartTaskCommand(System* s) : Command(s)
{
}

void StartTaskCommand::execute() const
{
	unsigned id;
	std::cin >> id;
	try {
		system->getActiveUser().startTask(id);
		std::cout << "You started task " << id << "!" << std::endl;
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}
