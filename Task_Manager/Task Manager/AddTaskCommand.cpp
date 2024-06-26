#include "AddTaskCommand.h"

AddTaskCommand::AddTaskCommand(System* s) : Command(s)
{
}

void AddTaskCommand::execute() const
{
	String taskName;
	String date;
	String description;
	char buffer[1024];
	unsigned id;
	
	std::cin >> taskName;
	std::cin >> date;
	std::cin.ignore();
	std::cin.getline(buffer, 1024);
	description = buffer;
	id = system->findFreeId();

	try {
		system->getActiveUser().add_task(taskName, date, description, id);
		std::cout << "Task added successfully!" << std::endl;
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}
