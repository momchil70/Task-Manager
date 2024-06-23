#include "User.h"

int User::findTask(unsigned id) const
{
	for (int i = 0; i < size; i++) {
		if (id == tasks[i]->getId()) {
			return i;
		}
	}
	return -1;
}

int User::findTask(const String& name) const
{
	for (int i = 0; i < size; i++) {
		if (name == tasks[i]->getName()) return i;
	}
	return -1;
}

bool User::checkForCopy(const Task& t)
{
	for (int i = 0; i < size; i++) {
		if (t == *tasks[i]) {
			return true;
		}
	}
	return false;
}

void User::free()
{
	for (int i = 0; i < size; i++) {
		if (!tasks[i]->isCollabTask()) {
			delete tasks[i];
		}
	}

	delete[] tasks;
}

void User::moveFrom(User&& other)
{
	tasks = other.tasks;
	other.tasks = nullptr;

	size = other.size;
	capacity = other.capacity;

	other.size = other.capacity = 0;

	dash = std::move(other.dash);
	pass = other.pass;
	name = std::move(other.name);
}

void User::copyFrom(const User& other)
{
	tasks = new Task * [other.capacity];

	for (int i = 0; i < other.size; i++) {
		tasks[i] = other.tasks[i]->clone();
	}

	size = other.size;
	capacity = other.capacity;

	dash = other.dash;
	name = other.name;
	pass = other.pass;
}

void User::resize(int newCap)
{
	Task** temp = new Task* [newCap];
	for (int i = 0; i < size; i++) {
		temp[i] = tasks[i];
	}

	delete[] tasks;
	tasks = temp;
	capacity = newCap;
}

User::User()
{
	tasks = new Task * [capacity];
}

User::User(const User& other)
{
	copyFrom(other);
}

User::User(User&& other)
{
	moveFrom(std::move(other));
}

User& User::operator=(const User& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

User& User::operator=(User&& other)
{
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

User::~User()
{
	free();
}

void User::add(Task* t)
{
	if (size == capacity) {
		resize(capacity * 2);
	}
	tasks[size++] = t;
}

void User::add(const Task& t)
{
	Task* cloned = t.clone();
	add(cloned);
}

void User::erase(int index)
{
	if (index >= size)
		throw std::out_of_range("Index out of range");

	delete tasks[index];

	for (int i = index; i < size - 1; i++)
		tasks[i] = std::move(tasks[i + 1]);

	size--;
}

void User::eraseWithoutDelete(int index)
{
	if (index >= size)
		throw std::out_of_range("Index out of range");
	for (int i = index; i < size - 1; i++)
		tasks[i] = std::move(tasks[i + 1]);

	size--;
}

User::User(const String& name, unsigned pass) : name(name), pass(pass)
{
	tasks = new Task * [capacity];
}

void User::add_task(const String& name, const String& date, const String& description, unsigned id)
{
	Task temp(name, date, description, id);

	if (checkForCopy(temp)) throw std::exception("This task already exists!");
		add(temp);

	temp.clearDate();
}

void User::asign(Task* task)
{
	add(task);
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
	if (tasks[index]->getStatus() == Status::DONE) {
		throw std::exception("You cannot start a finished task!");
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
		erase(index);
	}
	else {
		eraseWithoutDelete(index);
	}

	return collabID;
}

void User::deleteTask(const Task* task)
{
	for (int i = 0; i < size; i++) {
		if (task == tasks[i]) {
			erase(i);
		}
	}
}

void User::listTasks(const String& date) const
{
	std::cout << std::endl;
	Date temp = DatePool::getInstance().getDate(date, "");
	int count = 0;

	for (int i = 0; i < size; i++) {
		if (!tasks[i]->hasDate()) continue;

		if (tasks[i]->getTaskDate() == temp) {
			tasks[i]->print();
			std::cout << std::endl;
			count++;
		}
	}
	DatePool::getInstance().removeDate(temp, "");

	if (count == 0) std::cout << "No tasks for that date!" << std::endl;
}

void User::listTasks() const
{
	if (size == 0) {
		std::cout << "No tasks found!" << std::endl;
		return;
	}
	std::cout << std::endl;
	for (int i = 0; i < size; i++) {
		tasks[i]->print();
		std::cout << std::endl;
	}
}

void User::getTask(const String& name) const
{
	int minIndex = -1;

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
	bool marker = 0;
	for (int i = 0; i < size; i++) {
		if (id == tasks[i]->getId()) {
			tasks[i]->print();
			marker = 1;
		}
	}
	if (!marker) throw std::exception("There is not such task!");
}

void User::listCompleted() const
{
	int count = 0;
	
	for (int i = 0; i < size; i++) {
		if (tasks[i]->getStatus() == Status::DONE) {
			std::cout << std::endl;
			tasks[i]->print();
			std::cout << std::endl;
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
		return;
	}
	std::cout << std::endl;
	for (int i = 0; i < size; i++) {
		unsigned id = dash.getTask(i);
		int index = findTask(id);
		if (index != -1) {
			tasks[index]->print();
			std::cout << std::endl;
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
	for (int i = 0; i < size; i++) {
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



void User::saveToDatabase(std::ofstream& ofs) const
{
	unsigned nameLen = 0;
	nameLen = name.getSize() + 1;
	ofs.write(reinterpret_cast<const char*>(&nameLen), sizeof(unsigned));
	ofs.write(reinterpret_cast<const char*>(name.c_str()), nameLen);
	ofs.write(reinterpret_cast<const char*>(&pass), sizeof(unsigned));
}

void User::getFromDataBase(std::ifstream& ifs)
{
	unsigned nameLen = 0;
	char* tempName;

	ifs.read(reinterpret_cast<char*>(&nameLen), sizeof(unsigned));
	tempName = new char[nameLen];
	ifs.read(reinterpret_cast<char*>(tempName), nameLen);
	name = tempName;
	delete[] tempName;

	ifs.read(reinterpret_cast<char*>(&pass), sizeof(unsigned));
}

void User::savePersonalTasks(std::ofstream& ofs) const
{
	unsigned personalTasks = 0;
	for (int i = 0; i < size; i++) {
		if (!tasks[i]->isCollabTask()) personalTasks++;
	}

	ofs.write(reinterpret_cast<const char*>(&personalTasks), sizeof(unsigned));

	for (int i=0;i<personalTasks;i++) {
		if (tasks[i] && !tasks[i]->isCollabTask()) {
			tasks[i]->saveToDataBase(ofs);
		}
	}
}

void User::getPersonalTasks(std::ifstream& ifs)
{
	unsigned tasksCount = 0;
	ifs.read(reinterpret_cast<char*>(&tasksCount), sizeof(unsigned));

	for (int i = 0; i < tasksCount; i++) {
		Task* temp;
		temp = new Task();
		temp->getFromDataBase(ifs);
		add(std::move(temp));
	}
}
