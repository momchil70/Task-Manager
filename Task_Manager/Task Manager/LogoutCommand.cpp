#include "LogoutCommand.h"
#include "System.h"

LogoutCommand::LogoutCommand(System* s) : Command(s)
{
}

void LogoutCommand::execute() const
{
	system->logout();
}
