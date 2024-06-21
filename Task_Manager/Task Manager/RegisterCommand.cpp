#include "RegisterCommand.h"
#include "System.h"

RegisterCommand::RegisterCommand(System* s) : Command(s)
{
}

void RegisterCommand::execute() const
{
	String username;
	unsigned pass;
	std::cin >> username;
	std::cin >> pass;

	if (system->isTakenUsername(username)) {
		std::cout << "User with the same name already exists!" << std::endl;
		return;
	}
	system->addUser(User(username, pass));
}
