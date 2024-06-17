#include "AddDashboardCommand.h"
#include "System.h"

AddDashboardCommand::AddDashboardCommand(System* s): Command(s)
{
}

void AddDashboardCommand::execute() const
{
	unsigned id;
	std::cin >> id;
	try {
		system->getActiveUser().addTaskToDashboard(id);
		std::cout << "Task added to dashboard successfully!" << std::endl;
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}
	
