#include "AsignTaskCommand.h"
#include "System.h"

AsignTaskCommand::AsignTaskCommand(System* s) : Command(s)
{
}

void AsignTaskCommand::execute() const
{
	String collab, user, taskName, due_date, descr;
	std::cin >> collab >> user >> taskName >> due_date >> descr;
	try {
		system->asignTask(collab, user, taskName, due_date, descr);
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}