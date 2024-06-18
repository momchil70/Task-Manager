#include "System.h"
#include <fstream>

void System::getUsersFromDatabase()
{
	std::ifstream ifs("database.dat", std::ios::binary);

	if (!ifs.is_open()) throw std::exception("Error while opening file");

	unsigned usersCount = 0;
	ifs.read(reinterpret_cast<char*>(&usersCount), sizeof(unsigned));
	User configurational;

	for (int i = 0; i < usersCount; i++){
		users.push_back(configurational);
		users[i].getFromDataBase(ifs);
	}
}

void System::commandMode()
{
	String command;
	Command* current;

	while (systemRunning) {
		std::cout << "->";
		std::cin >> command;

		if (command != "login" && command != "register" && command != "exit" && loggedIndex == -1) {
			std::cout << "No logged user! I cannot execute any command! Try again!" << std::endl;
			continue;
		}

		try {
			Command* current = createCommand(command, this);
			current->execute();
			delete current;
		}
		catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		}
	}
}

void System::saveToDataBase() const
{
	std::ofstream ofs("database.dat", std::ios::binary | std::ios::trunc);

	if (!ofs.is_open()) throw std::exception("Error while opening file");

	unsigned size = users.size();
	ofs.write(reinterpret_cast<const char*>(&size), sizeof(unsigned));

	for (int i = 0; i < size; i++) {
		users[i].saveToDatabase(ofs);
	}
	ofs.close();
}

bool System::isTakenUsername(const String& name) const
{
	int size = users.size();
	for (int i = 0; i < size; i++) {
		if (name == users[i].getName()) return true;
	}
	return false;
}

System::System()
{
	getUsersFromDatabase();

	commandMode();
}

void System::login(const String& name, unsigned pass)
{
	int size = users.size();
	for (int i = 0; i < size; i++) {
		if (name == users[i].getName() && pass == users[i].getPass()) {
			loggedIndex = i;
			std::cout << "Hello " << name << std::endl;

			String temp = getCurrentDate(); //ETO TUK MOJESH DA SI PRAVISH TESTOVE --------------------------

			Date today = DatePool::getInstance().getDate(temp, "");

			users[loggedIndex].configTasks(today);
			users[loggedIndex].configDashboard(today);

			DatePool::getInstance().removeDate(today, "");
			return;
		}
	}
	std::cout << "Cannot find user with that name! Register first!" << std::endl;
}

void System::register_user()
{
	String name;
	unsigned pass;
	std::cin >> name >> pass;
	users.push_back(User(name, pass));
}

void System::setTheRun(bool value)
{
	systemRunning = value;
}

void System::addUser(const User& user)
{
	if (isTakenUsername(user.getName())) std::cout << "User with the same username already exists!" << std::endl;

	else {
		users.push_back(user);
		std::cout << "Successfully registered!" << std::endl;
	}
}

User& System::getActiveUser()
{
	return users[loggedIndex];
}

void System::logout()
{
	std::cout << "Goodbye " << users[loggedIndex].getName() << "!" << std::endl;
	loggedIndex = -1;
}

System::~System()
{
	saveToDataBase();
}
