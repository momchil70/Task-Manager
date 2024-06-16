#include "System.h"
#include <fstream>

void System::getUsersFromDatabase()
{
	std::ifstream ifs("database.dat", std::ios::binary);

	if (!ifs.is_open()) throw std::exception("Error while opening file");

	String name;
	char* tempName;
	unsigned pass;
	unsigned nameLen = -1;
	while (!ifs.eof()) {
		ifs.read(reinterpret_cast<char*>(&nameLen), sizeof(unsigned));
		
		if (nameLen == -1) return;

		tempName = new char[nameLen + 1];
		ifs.read(reinterpret_cast<char*>(tempName), nameLen);
		name = tempName;
		ifs.read(reinterpret_cast<char*>(&pass), sizeof(unsigned));
		delete[] tempName;

		users.push_back(User(name, pass));
	}
}

void System::commandMode()
{
	String command;
	Command* current;

	while (systemRunning) {
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
	unsigned nameLen = 0;
	for (int i = 0; i < size; i++) {
		nameLen = users[i].getName().getSize() + 1;
		String name = users[i].getName();
		unsigned pass = users[i].getPass();
		ofs.write(reinterpret_cast<const char*>(&nameLen), sizeof(unsigned));
		ofs.write(reinterpret_cast<const char*>(name.c_str()), nameLen);
		ofs.write(reinterpret_cast<const char*>(&pass), sizeof(unsigned));
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

System::~System()
{
	saveToDataBase();
}
