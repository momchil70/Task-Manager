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

unsigned System::findCollaboration(const String& name) const
{
	int size = collabs.size();
	for (int i = 0; i < size; i++) {
		if (collabs[i].getName() == name) return i;
	}
	return -1;
}

unsigned System::findUser(const String& name) const
{
	int size = users.size();
	for (int i = 0; i < size; i++) {
		if (users[i].getName() == name) return i;
	}
	return -1;
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

void System::listCollaborations() const
{
	int size = collabs.size();
	for (int i = 0; i < size; i++) {
		if (collabs[i].isUserIn(users[loggedIndex])) std::cout << collabs[i].getName() << std::endl;
	}
}

void System::createCollaboration(const String& name)
{
	unsigned firstFreeId = 1;
	int size = collabs.size();
	for (int i = 0; i < size; i++) {
		if (firstFreeId == collabs[i].getId()) {
			firstFreeId++;
			i = 0;
		}
	}

	if (loggedIndex == -1) throw std::exception("Cannot create collaboration! Nobody is logged!");

	Collaboration temp(users[loggedIndex], name, firstFreeId);
	collabs.push_back(temp);
}


void System::deleteCollaboration(const String& name)
{
	unsigned index = findCollaboration(name);
	if (index == -1) {
		std::cout << "Non existing collaboration!" << std::endl;
		return;
	}
	collabs.erase(index);
}

void System::listCollabTasks(const String& name) const
{
	unsigned index = findCollaboration(name);
	if (index == -1) {
		std::cout << "Non existing collaboration!" << std::endl;
		return;
	}
	collabs[index].listTasks();
}

void System::addUser(const String& collaboration, const String& name)
{
	unsigned index = findCollaboration(collaboration);
	if (index == -1) {
		std::cout << "Non existing collaboration!" << std::endl;
		return;
	}
	unsigned userIndex = findUser(name);
	if (userIndex == -1) {
		std::cout << "Non existing user!" << std::endl;
		return;
	}
	collabs[index].addUser(users[userIndex]);
}

void System::asignTask(const String& collab, const String& user, const String& taskName, const String& due_date, const String& description)
{
	unsigned index = findCollaboration(collab);
	unsigned userIndex = findUser(user);
	if (userIndex == -1 || index==-1 || !collabs[index].isUserIn(users[userIndex])) {
		std::cout << "Cannot procces that command!" << std::endl;
		return;
	}
	CollabTask temp(taskName, due_date, description, users[userIndex].getName());
	collabs[index].addTask(temp);
	users[userIndex].asign(collabs[index].getLastTask());
}



System::~System()
{
	saveToDataBase();
}
