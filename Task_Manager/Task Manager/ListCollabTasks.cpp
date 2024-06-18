#include "ListCollabTasks.h"
#include "System.h"

ListCollabTasks::ListCollabTasks(System* s) : Command(s)
{
}

void ListCollabTasks::execute() const
{
	String name;
	std::cin >> name;
	try {
		system->listCollabTasks(name);
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}

