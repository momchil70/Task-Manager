#include "System.h"
#include <fstream>

void System::getUsersFromDatabase()
{
	std::ifstream ifs("database.dat", std::ios::binary);

	if (!ifs.is_open()) throw std::exception("Error while opening file");

	String name;
	unsigned pass;
	unsigned nameLen;
	while (!ifs.eof()) {
		ifs.read(reinterpret_cast<char*>(&nameLen), sizeof(unsigned));
		ifs.read(reinterpret_cast<char*>(&name), nameLen);
		ifs.read(reinterpret_cast<char*>(&pass), sizeof(unsigned));

		users.push_back(User(name, pass));
	}
}

void System::commandMode()
{
	String command;
	bool programmIsRunning = true;

	while (programmIsRunning) {
		std::cin >> command;

		if (command == "exit") {
			saveToDataBase();
			std::cout << "Exited successfully!" << std::endl;
			return;
		}

		if (command == "login") {
			login();
		}
	}
}

void System::saveToDataBase() const
{
	std::ofstream ofs("database.dat", std::ios::binary);

	if (!ofs.is_open()) throw std::exception("Error while opening file");

	unsigned size = users.size();
	unsigned nameLen = 0;
	for (int i = 0; i < size; i++) {
		nameLen = users[i].getName().getSize();
		String name = users[i].getName();
		unsigned pass = users[i].getPass();
		ofs.write(reinterpret_cast<const char*>(&nameLen), sizeof(unsigned));
		ofs.write(reinterpret_cast<const char*>(&name), nameLen);
		ofs.write(reinterpret_cast<const char*>(&pass), sizeof(unsigned));
	}
}

System::System()
{
	getUsersFromDatabase();

	commandMode();
}

void System::login()
{
}

void System::register_user()
{
	String name;
	unsigned pass;
	std::cin >> name >> pass;
	users.push_back(User(name, pass));
}
