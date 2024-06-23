#include "RemoveFromDashCommand.h"

RemoveFromDashCommand::RemoveFromDashCommand(System* s) : Command(s)
{
}

void RemoveFromDashCommand::execute() const
{
	unsigned id;
	std::cin >> id;
	try {
		system->getActiveUser().removeTaskFromDashboard(id);
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}
