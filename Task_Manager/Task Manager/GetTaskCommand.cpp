#include "GetTaskCommand.h"
#include "System.h"


GetTaskCommand::GetTaskCommand(System* s, bool marker) : Command(s)
{
	this->marker = marker;
}

void GetTaskCommand::execute() const
{
	try {
		if (!marker) {
			unsigned id;
			std::cin >> id;
			system->getActiveUser().getTask(id);
		}
		else {
			String name;
			std::cin >> name;
			system->getActiveUser().getTask(name);
		}
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}
