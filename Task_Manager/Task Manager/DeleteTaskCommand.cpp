#include "DeleteTaskCommand.h"
#include "System.h"

DeleteTaskCommand::DeleteTaskCommand(System* s) : Command(s)
{
}

void DeleteTaskCommand::execute() const
{
	unsigned id;
	std::cin >> id;

	try {
		unsigned collabId = system->getActiveUser().deleteTask(id);
		
		if (collabId == -1)
			std::cout << "Task deleted successfully!" << std::endl;
	
		else {
			Collaboration& collab = system->getCollab(collabId);
			collab.removeTask(id);
		}
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}