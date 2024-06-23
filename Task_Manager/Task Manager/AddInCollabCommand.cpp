#include "AddInCollabCommand.h"

AddInCollabCommand::AddInCollabCommand(System * s) : Command(s)
{
}

void AddInCollabCommand::execute() const
{
	String collab, name;
	std::cin >> collab >> name;
	try {
		system->addUser(collab, name);
		std::cout << "User added successfully!" << std::endl;
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}
