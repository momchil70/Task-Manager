#include "User.h"

int User::findTask(unsigned id) const
{
	int size = tasks.getSize();
	for (int i = 0; i < size; i++) {
		if (id == tasks[i]->getId()) return i;
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

void User::add_task(const String& name, const String& date, const String& description)
{
	Task temp(name, date, description);

	if (checkForCopy(temp)) throw std::exception("This task already exists!");
	tasks.add(temp);

	temp.clearDate();
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

	tasks[index]->setDescription(description);
}

void User::startTask(unsigned id)
{
	int index = findTask(id);

	if (index == -1) {
		throw std::exception("Non existing task");
	}

	tasks[index]->setStatus(Status::IN_PROGRESS);
}

void User::deleteTask(unsigned id)
{
	try {
		dash.removeFromTodo(id);
	}
	catch (std::exception& e) {}

	int index = findTask(id);

	if (index == -1) {
		throw std::exception("Non existing task");
	}

	DatePool::getInstance().removeDate(tasks[index]->getTaskDate(), tasks[index]->getName());
	tasks.erase(index);
}

void User::listTasks(const String& date) const
{
	Date temp = DatePool::getInstance().getDate(date, "");
	int count = 0;
	int size = tasks.getSize();

	for (int i = 0; i < size; i++) {
		if (!tasks[i]->hasDate()) continue;

		if (tasks[i]->getTaskDate() == temp) {
			std::cout << (*tasks[i]);
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
	}
	for (int i = 0; i < size; i++) {
		std::cout << *tasks[i] << std::endl;
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

	std::cout << *tasks[minIndex] << std::endl;
}

void User::getTask(unsigned id) const
{
	int size = tasks.getSize();
	for (int i = 0; i < size; i++) {
		if (id == tasks[i]->getId()) std::cout << *tasks[i] << std::endl;
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
			std::cout << (*tasks[i]);
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
}


void User::listDashboard() const
{
	int size = dash.getSize();

	if (size == 0) {
		std::cout << "No tasks found in dashboard!" << std::endl;
	}

	for (int i = 0; i < size; i++) {
		const Task* temp = dash.getTask(i);
		if (temp) {
			std::cout << *temp << std::endl;
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

	dash.addTodo(tasks[index]);
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
	ofs.write(reinterpret_cast<const char*>(&taskCount), sizeof(unsigned));
	for (int i = 0; i < taskCount; i++) {
		tasks[i]->saveToDataBase(ofs);
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
		ifs.read(reinterpret_cast<char*>(&isCollab), sizeof(bool));
		if (isCollab) {
			CollabTask temp;
			temp.getFromDataBase(ifs);
			tasks.add(temp);
		}
		else {
			Task temp;
			temp.getFromDataBase(ifs);
			tasks.add(temp);
		}
	}
	readDashboard(ifs);
}

void User::configDashboard(const Date& today)
{
	int size = dash.getSize();

	for (int i = 0; i < size; i++) {
		if (dash.getTask(i)->getStatus() == Status::OVERDUE || dash.getTask(i)->getStatus() == Status::DONE) {
			unsigned id = dash.getTask(i)->getId();
			dash.removeFromTodo(id);
		}
	}
}

void User::configTasks(const Date& today)
{
	int size = tasks.getSize();
	for (int i = 0; i < size; i++) {
		if (today == tasks[i]->getTaskDate() && tasks[i]->getStatus()!=Status::IN_PROGRESS) {
			tasks[i]->setStatus(Status::IN_PROGRESS);
			dash.addTodo(tasks[i]);
		}
		if (today > tasks[i]->getTaskDate()) {
			tasks[i]->setStatus(Status::OVERDUE);
		}
	}
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
		currentId = dash.getTaskId(i);
		ofs.write(reinterpret_cast<const char*>(&currentId), sizeof(unsigned));
	}
}
