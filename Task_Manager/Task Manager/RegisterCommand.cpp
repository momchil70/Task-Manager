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

	system->addUser(User(username, pass));
}
