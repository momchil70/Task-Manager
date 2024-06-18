#include "CreateCollabCommand.h"
#include "System.h"

CreateCollabCommand::CreateCollabCommand(System* s) : Command(s)
{
}

void CreateCollabCommand::execute() const
{
	String name;
	std::cin >> name;
	try {
		system->createCollaboration(name);
		std::cout << "Collaboration created!" << std::endl;
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}

