#include "ListDateCommand.h"
#include "System.h"


ListDateCommand::ListDateCommand(System* s): Command(s)
{
}

void ListDateCommand::execute() const
{
	String temp;
	std::cin >> temp;

	try {
		system->getActiveUser().listTasks(temp);
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}
