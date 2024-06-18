#include "FinishCommand.h"
#include "System.h"


FinishCommand::FinishCommand(System* s) : Command(s)
{
}

void FinishCommand::execute() const
{
	unsigned id;
	std::cin >> id;
	try {
		system->getActiveUser().finishTask(id);
		std::cout << "You finished task " << id << "!" << std::endl;
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}
