#include "UpdateTaskCommand.h"
#include "System.h"

UpdateTaskCommand::UpdateTaskCommand(System* s, bool marker) : Command(s)
{
	this->marker = marker;
}

void UpdateTaskCommand::execute() const
{
	String newValue;
	unsigned id;
	std::cin >> id;
	std::cin >> newValue;
	try {
		if (marker == 0)
			system->getActiveUser().updateTaskName(id, newValue);
		else
			system->getActiveUser().updateTaskDescription(id, newValue);

		std::cout << "Task updated successfully!" << std::endl;
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}