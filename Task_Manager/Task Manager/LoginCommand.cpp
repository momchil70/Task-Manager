#include "LoginCommand.h"


LoginCommand::LoginCommand(System* s) : Command(s)
{
}

void LoginCommand::execute() const
{
	String username;
	unsigned pass;
	std::cin >> username;
	std::cin >> pass;
	if (system->hasLoggedUser()) {
		std::cout << "Logout first!" << std::endl;
		return;
	}
	system->login(username, pass);
}
