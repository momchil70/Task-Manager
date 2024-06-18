#include "ListCollabsCommand.h"
#include "System.h"

ListCollabsCommand::ListCollabsCommand(System* s) : Command(s)
{
}

void ListCollabsCommand::execute() const
{
	try {
		system->listCollaborations();
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}

