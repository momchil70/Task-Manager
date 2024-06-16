#include "AddTaskCommand.h"
#include "System.h"

AddTaskCommand::AddTaskCommand(System* s) : Command(s)
{
}

void AddTaskCommand::execute() const
{
	String taskName;
	String date;
	String description;
	
	std::cin >> taskName;
	std::cin >> date;
	std::cin >> description;

	try {
		system->getActiveUser().add_task(taskName, date, description);
		std::cout << "Task added successfully!" << std::endl;
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}
