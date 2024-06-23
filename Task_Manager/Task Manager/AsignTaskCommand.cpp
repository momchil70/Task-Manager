#include "AsignTaskCommand.h"

AsignTaskCommand::AsignTaskCommand(System* s) : Command(s)
{
}

void AsignTaskCommand::execute() const
{
	String collab, user, taskName, due_date, descr;
	char buffer[1024];
	std::cin >> collab >> user >> taskName >> due_date;
	std::cin.ignore();
	std::cin.getline(buffer, 1024);
	descr = buffer;
	try {
		system->asignTask(collab, user, taskName, due_date, descr);
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}