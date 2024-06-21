#include "System.h"
#include <fstream>


void System::loadData()
{
	std::ifstream ifs("users.dat", std::ios::binary);
	if (!ifs.is_open()) throw std::exception("Error while opening file");
	//getUsers ---------------------------------
	unsigned usersCount = 0;
	ifs.read(reinterpret_cast<char*>(&usersCount), sizeof(unsigned));
	User configurational;
	for (int i = 0; i < usersCount; i++) {
		users.push_back(configurational);
		users[i].getFromDataBase(ifs);
	}
	ifs.close();
	//get usertasks-----------------------------
	std::ifstream ifs1("usertasks.dat", std::ios::binary);
	if (!ifs1.is_open()) throw std::exception("Error while opening file");

	for (int i = 0; i < users.size(); i++) {
		users[i].getPersonalTasks(ifs1);
	}

	//get collabs--------------------------------
	std::ifstream ifs2("collabs.dat", std::ios::binary);
	if (!ifs2.is_open()) throw std::exception("Error while opening file");
	getCollabsFromDatabase(ifs2);
	ifs2.close();

	//u need to load the dashboard of every user
	for (int i = 0; i < users.size(); i++) {
		users[i].readDashboard(ifs1);
	}
}



void System::saveToDataBase() const
{
	std::ofstream ofs("users.dat", std::ios::binary | std::ios::trunc);

	if (!ofs.is_open()) throw std::exception("Error while opening file");

	unsigned size = users.size();
	ofs.write(reinterpret_cast<const char*>(&size), sizeof(unsigned));

	for (int i = 0; i < size; i++) {
		users[i].saveToDatabase(ofs);
	}
	ofs.close();
	// DOTUK E FAILUT users.dat ----------------------------------------------------------

	std::ofstream ofs1("usertasks.dat", std::ios::binary | std::ios::trunc);

	if (!ofs1.is_open()) throw std::exception("Error while opening file");
	for (int i = 0; i < size; i++) {
		users[i].savePersonalTasks(ofs1);
	}
	for (int i = 0; i < size; i++) {
		users[i].saveDashboard(ofs1);
	}
	ofs1.close();
	// DOTUK E FAILUT usertasks.dat -------------------------------------------------------
	std::ofstream ofs2("collabs.dat", std::ios::binary | std::ios::trunc);

	if (!ofs2.is_open()) throw std::exception("Error while opening file");

	saveCollabsToDatabase(ofs2);
	ofs2.close();
}


void System::saveCollabsToDatabase(std::ofstream& ofs) const
{
	unsigned collabsCount = collabs.size();
	ofs.write(reinterpret_cast<const char*>(&collabsCount), sizeof(unsigned));

	for (int i = 0; i < collabsCount; i++) {
		collabs[i].saveToDatabase(ofs);
	}
}

void System::getCollabsFromDatabase(std::ifstream& ifs)
{
	unsigned collabsCount = collabs.size();
	ifs.read(reinterpret_cast<char*>(&collabsCount), sizeof(unsigned));
	for (int i = 0; i < collabsCount; i++) {
		unsigned nameLen = 0, id = 0;
		char* creatorName; char* name;
		//getting name and id of the collab
		ifs.read(reinterpret_cast<char*>(&nameLen), sizeof(unsigned));
		name = new char[nameLen];
		ifs.read(reinterpret_cast<char*>(name), nameLen);

		ifs.read(reinterpret_cast<char*>(&id), sizeof(unsigned));
		//getting creator
		ifs.read(reinterpret_cast<char*>(&nameLen), sizeof(unsigned));
		creatorName = new char[nameLen];
		ifs.read(reinterpret_cast<char*>(creatorName), nameLen);
		User& creator = users[findUser(creatorName)];
		delete[] creatorName;
		//pushing the collaboration in the collection
		Collaboration temp(creator, name, id);
		collabs.push_back(std::move(temp));		//it takes the name. We do not have to delete it. It is already nullptr

		//loading the participants
		unsigned participantsCount = 0; char* participantName = nullptr;
		ifs.read(reinterpret_cast<char*>(&participantsCount), sizeof(unsigned));
		for (int j = 0; j < participantsCount; j++) {
			ifs.read(reinterpret_cast<char*>(&nameLen), sizeof(unsigned));
			participantName = new char[nameLen];
			ifs.read(reinterpret_cast<char*>(participantName), nameLen);
			int index = findUser(participantName); //get the participant
			delete[] participantName;
			collabs[i].addUser(users[index]);
		}
		//loading the tasks and asigning them to the users
		unsigned taskCount;
		ifs.read(reinterpret_cast<char*>(&taskCount), sizeof(unsigned));
		for (int j = 0; j < taskCount; j++) {
			CollabTask tempTask;
			tempTask.getFromDataBase(ifs);
			collabs[i].addTask(&tempTask);
			String name = tempTask.getAsignee();
			int index = findUser(name);
			unsigned id = tempTask.getId();
			users[index].asign(collabs[i].getTaskById(id));
		}
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


unsigned System::findFreeId() const
{
	unsigned result = 1;
	int usersCount = users.size();
	while (true) {
		for (int i = 0; i < usersCount; i++) {
			if (users[i].containsId(result)) {
				result++;
				break;
			}
		}
		return result;
	}
}

Collaboration& System::getCollab(unsigned id)
{
	int size = collabs.size();
	for (int i = 0; i < size; i++) {
		if (id == collabs[i].getId()) return collabs[i];
	}

}

System::System()
{
	loadData();

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
	if (loggedIndex == -1) throw std::exception("Cannot create collaboration! Nobody is logged!");

	unsigned firstFreeId = 1;
	int size = collabs.size();
	for (int i = 0; i < size; i++) {
		if (firstFreeId == collabs[i].getId()) {
			firstFreeId++;
			i = 0;
		}
	}

	collabs.push_back(Collaboration(users[loggedIndex], name, firstFreeId));
}

void System::deleteCollaboration(const String& name)
{
	unsigned index = findCollaboration(name);
	if (index == -1) {
		std::cout << "Non existing collaboration!" << std::endl;
		return;
	}
	if (collabs[index].getCreator() != users[loggedIndex]) {
		throw std::exception("You do not own the collaboration!");
		return;
	}

	int size = collabs[index].getTasksCapacity();
	for (int i = 0; i < size; i++) {
		const Task* temp = collabs[index].getTask(i);
		if (temp == nullptr) continue;

		String username = temp->getAsignee();
		unsigned userIndex = findUser(username);
		users[userIndex].deleteTask(temp->getId());
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
	if (!collabs[index].isUserIn(users[loggedIndex])) {
		std::cout << "You do not participate in this collab!" << std::endl;
		return;
	}
	collabs[index].listTasks();
}

void System::addUser(const String& collaboration, const String& name)
{
	unsigned index = findCollaboration(collaboration);
	if (index == -1) {
		throw std::exception("Non existing collaboration!");
		return;
	}
	unsigned userIndex = findUser(name);
	if (userIndex == -1) {
		throw std::exception("Non existing user!");
		return;
	}
	collabs[index].addUser(users[userIndex]);
}

void System::asignTask(const String& collab, const String& user, const String& taskName, const String& due_date, const String& description)
{
	unsigned index = findCollaboration(collab);
	unsigned userIndex = findUser(user);
	if (userIndex == -1 || index == -1 || !collabs[index].isUserIn(users[userIndex])) {
		std::cout << "Cannot procces that command!" << std::endl;
		return;
	}
	unsigned freeId = this->findFreeId();
	unsigned collabIndex = findCollaboration(collab);
	unsigned collabId = collabs[collabIndex].getId();
	CollabTask temp(taskName, due_date, description, freeId, users[userIndex].getName(), collabId);
	collabs[index].addTask(&temp);
	users[userIndex].asign(collabs[index].getTaskById(freeId));// tuk shte butash
}

bool System::hasLoggedUser() const
{
	return loggedIndex != -1;
}


System::~System()
{
	saveToDataBase();
}
