#include "User.h"

int User::findTask(unsigned id) const
{
	int size = tasks.getSize();
	for (int i = 0; i < size; i++) {
		if (id == tasks[i]->getId()) {
			return i;
		}
	}
	return -1;
}

int User::findTask(const String& name) const
{
	int size = tasks.getSize();
	for (int i = 0; i < size; i++) {
		if (name == tasks[i]->getName()) return i;
	}
	return -1;
}

bool User::checkForCopy(const Task& t)
{
	int size = tasks.getSize();
	for (int i = 0; i < size; i++) {
		if (t == *tasks[i]) {
			return true;
		}
	}
	return false;
}

User::User(const String& name, unsigned pass) : name(name), pass(pass)
{
}

void User::add_task(const String& name, const String& date, const String& description, unsigned id)
{
	Task temp(name, date, description, id);

	if (checkForCopy(temp)) throw std::exception("This task already exists!");
	tasks.add(temp);

	temp.clearDate();
}

void User::asign(Task* task)
{
	tasks.add(task);
}

void User::updateTaskName(unsigned id, const String& name)
{
	int index = findTask(id);

	if (index == -1) {
		throw std::exception("Non existing task");
	}
	tasks[index]->setName(name);
}

void User::updateTaskDescription(unsigned id, const String& description)
{
	int index = findTask(id);

	if (index == -1) {
		throw std::exception("Non existing task");
	}
	tasks[index]->setDescription(name);
}

void User::startTask(unsigned id)
{
	int index = findTask(id);

	if (index == -1) {
		throw std::exception("Non existing task");
	}
	tasks[index]->setStatus(Status::IN_PROGRESS);
}

unsigned User::deleteTask(unsigned id)
{
	try {
		dash.removeFromTodo(id);
	}
	catch (std::exception& e) {}

	int index = findTask(id);

	if (index == -1) {
		throw std::exception("Non existing task");
	}
	
	unsigned collabID = tasks[index]->getCollabId();
	if (!tasks[index]->isCollabTask()) {
		DatePool::getInstance().removeDate(tasks[index]->getTaskDate(), tasks[index]->getName());
		tasks.erase(index);
	}
	else {
		tasks.eraseWithoutDelete(index);
	}

	return collabID;
}

void User::deleteTask(const Task* task)
{
	int size = tasks.getSize();
	for (int i = 0; i < size; i++) {
		if (task == tasks[i]) {
			tasks.erase(i);
		}
	}
}

void User::listTasks(const String& date) const
{
	Date temp = DatePool::getInstance().getDate(date, "");
	int count = 0;
	int size = tasks.getSize();

	for (int i = 0; i < size; i++) {
		if (!tasks[i]->hasDate()) continue;

		if (tasks[i]->getTaskDate() == temp) {
			tasks[i]->print();
			count++;
		}
	}
	DatePool::getInstance().removeDate(temp, "");

	if (count == 0) std::cout << "No tasks for that date!" << std::endl;
}

void User::listTasks() const
{
	int size = tasks.getSize();
	if (size == 0) {
		std::cout << "No tasks found!" << std::endl;
		return;
	}
	for (int i = 0; i < size; i++) {
		tasks[i]->print();
	}
}

void User::getTask(const String& name) const
{
	int minIndex = -1;
	int size = tasks.getSize();

	for (int i = 0; i < size; i++) {
		if (name == tasks[i]->getName()) {
			if (minIndex == -1) minIndex = i;

			else minIndex = (i < minIndex) ? i : minIndex;
		}
	}
	if (minIndex == -1) throw std::exception("There is not such task!");

	tasks[minIndex]->print();
}

void User::getTask(unsigned id) const
{
	int size = tasks.getSize();
	for (int i = 0; i < size; i++) {
		if (id == tasks[i]->getId()) tasks[i]->print();
		return;
	}
	throw std::exception("There is not such task!");
}

void User::listCompleted() const
{
	int size = tasks.getSize();
	int count = 0;

	for (int i = 0; i < size; i++) {
		if (tasks[i]->getStatus() == Status::DONE) {
			tasks[i]->print();
			count++;
		}
	}
	if (count == 0) std::cout << "No finished tasks!" << std::endl;
}

void User::finishTask(unsigned id)
{
	int index = findTask(id);

	if (index == -1) throw std::exception("Task not found!");

	tasks[index]->setStatus(Status::DONE);
	try {
		removeTaskFromDashboard(id);
	}
	catch (...) {}
}


void User::listDashboard() const
{
	int size = dash.getSize();

	if (size == 0) {
		std::cout << "No tasks found in dashboard!" << std::endl;
	}

	for (int i = 0; i < size; i++) {
		unsigned id = dash.getTask(i);
		int index = findTask(id);
		if (index != -1) {
			tasks[index]->print();
		}
		else {
			std::cout << "Could not get the task from Dashboard at index " << i << std::endl;
		}
	}
}

void User::addTaskToDashboard(unsigned id)
{
	int index = findTask(id);

	if (index == -1) throw std::exception("Task not found!");
	if (tasks[index]->getStatus() == Status::OVERDUE) throw std::exception("Task is overdue!");

	dash.addTodo(id);
}

void User::removeTaskFromDashboard(unsigned id)
{
	dash.removeFromTodo(id);
}

const String& User::getName() const
{
	return name;
}

unsigned User::getPass() const
{
	return pass;
}

void User::saveToDatabase(std::ofstream& ofs) const
{
	unsigned nameLen = 0;
	nameLen = name.getSize() + 1;
	ofs.write(reinterpret_cast<const char*>(&nameLen), sizeof(unsigned));
	ofs.write(reinterpret_cast<const char*>(name.c_str()), nameLen);
	ofs.write(reinterpret_cast<const char*>(&pass), sizeof(unsigned));

	unsigned taskCount = tasks.getSize();
	unsigned index = 0;
	ofs.write(reinterpret_cast<const char*>(&taskCount), sizeof(unsigned));
	while (index != taskCount) {
		if (tasks[index]) {
			tasks[index]->saveToDataBase(ofs);
			index++;
		}
	}
	saveDashboard(ofs);
}

void User::getFromDataBase(std::ifstream& ifs)
{
	bool isCollab = false;
	unsigned nameLen = 0, taskCount = 0;
	char* tempName;

	ifs.read(reinterpret_cast<char*>(&nameLen), sizeof(unsigned));
	tempName = new char[nameLen];
	ifs.read(reinterpret_cast<char*>(tempName), nameLen);
	name = tempName;

	ifs.read(reinterpret_cast<char*>(&pass), sizeof(unsigned));
	ifs.read(reinterpret_cast<char*>(&taskCount), sizeof(unsigned));

	for (int i = 0; i < taskCount; i++) {
		Task* temp;
		ifs.read(reinterpret_cast<char*>(&isCollab), sizeof(bool));
		if (isCollab) {
			temp = new CollabTask();
			temp->getFromDataBase(ifs);
			tasks.add(std::move(temp));
		}
		else {
			temp = new Task();
			temp->getFromDataBase(ifs);
			tasks.add(std::move(temp));
		}
	}
	readDashboard(ifs);
}

void User::configDashboard(const Date& today)
{
	int size = dash.getSize();

	for (int i = 0; i < size; i++) {
		unsigned index = findTask(dash.getTask(i));

		if (tasks[index]->getStatus() == Status::OVERDUE || tasks[index]->getStatus() == Status::DONE) {
			unsigned id = dash.getTask(i);
			dash.removeFromTodo(id);
		}
	}
}

void User::configTasks(const Date& today)
{
	int size = tasks.getSize();
	for (int i = 0; i < size; i++) {
		if (today == tasks[i]->getTaskDate() && tasks[i]->getStatus() != Status::IN_PROGRESS) {
			tasks[i]->setStatus(Status::IN_PROGRESS);
			dash.addTodo(tasks[i]->getId());
		}
		if (today > tasks[i]->getTaskDate()) {
			tasks[i]->setStatus(Status::OVERDUE);
		}
	}
}

bool User::containsId(unsigned id) const
{
	int taskCount = tasks.getSize();
	for (int i = 0; i < taskCount; i++) {
		if (id == tasks[i]->getId()) return true;
	}
	return false;
}


void User::readDashboard(std::ifstream& ifs)
{
	unsigned size = 0;
	int currentId = 0, currentIndex = 0;
	ifs.read(reinterpret_cast<char*>(&size), sizeof(unsigned));

	for (int i = 0; i < size; i++) {
		ifs.read(reinterpret_cast<char*>(&currentId), sizeof(unsigned));
		try {
			addTaskToDashboard(currentId);
		}
		catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		}
	}
}

void User::saveDashboard(std::ofstream& ofs) const
{
	unsigned size = dash.getSize();
	int currentId = 0;
	ofs.write(reinterpret_cast<const char*>(&size), sizeof(unsigned));

	for (int i = 0; i < size; i++) {
		currentId = dash.getTask(i);
		ofs.write(reinterpret_cast<const char*>(&currentId), sizeof(unsigned));
	}
}

bool operator==(const User& lhs, const User& rhs)
{
	return lhs.getName() == rhs.getName() && lhs.getPass() == rhs.getPass();
}

bool operator!=(const User& lhs, const User& rhs)
{
	return !(lhs == rhs);
}
