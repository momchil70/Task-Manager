#include "ExitCommand.h"

ExitCommand::ExitCommand(System* s): Command(s)
{
}

void ExitCommand::execute() const
{
	std::cout << "Goodbye!";
	system->setTheRun(false);
}
