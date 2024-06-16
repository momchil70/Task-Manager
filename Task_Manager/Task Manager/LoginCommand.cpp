#include "LoginCommand.h"
#include "System.h"

LoginCommand::LoginCommand(System* s) : Command(s)
{
}

void LoginCommand::execute() const
{
	String username;
	unsigned pass;
	std::cin >> username;
	std::cin >> pass;
	system->login(username, pass);
}
