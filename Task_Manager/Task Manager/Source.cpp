#include <iostream>
#include "String.h"
#include "Date.h"
#include "User.h"
#include "System.h"

int main() {
	User momo;

	momo.add_task();
	try {
		momo.add_task();
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	momo.addTaskToDashboard(1);

	momo.listTasks();
}
