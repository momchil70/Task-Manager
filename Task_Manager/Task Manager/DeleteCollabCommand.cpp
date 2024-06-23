#include "DeleteCollabCommand.h"

DeleteCollabCommand::DeleteCollabCommand(System* s) : Command(s)
{
}

void DeleteCollabCommand::execute() const
{
	String name;
	std::cin >> name;
	try {
		system->deleteCollaboration(name);
		std::cout << "Collaboration deleted successfully!" << std::endl;
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}

