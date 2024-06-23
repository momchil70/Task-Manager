#include "ListCompletedCommand.h"


ListCompletedCommand::ListCompletedCommand(System* s) : Command(s)
{
}

void ListCompletedCommand::execute() const
{
	try {
		system->getActiveUser().listCompleted();
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}
