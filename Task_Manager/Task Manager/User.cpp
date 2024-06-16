#include "User.h"

int User::findTask(unsigned id) const
{
	int size = tasks.size();
	for (int i = 0; i < size; i++) {
		if (id == tasks[i].getId()) return i;
	}
	return -1;
}

int User::findTask(const String& name) const
{
	int size = tasks.size();
	for (int i = 0; i < size; i++) {
		if (name == tasks[i].getName()) return i;
	}
	return -1;
}

bool User::checkForCopy(const Task& t)
{
	int size = tasks.size();
	for (int i = 0; i < size; i++) {
		if (t == tasks[i]) {
			return true;
		}
	}
	return false;
}

User::User(const String& name, unsigned pass): name(name), pass(pass)
{
}

void User::add_task(const String& name, const String& date, const String& description)
{
	Task temp(name, date, description);
	if (checkForCopy(temp)) throw std::exception("This task already exists!");

	tasks.push_back(temp);
	temp.clearDate();
	
}

void User::updateTaskName(unsigned id, const String& name)
{
	int index = findTask(id);

	if (index == -1) {
		throw std::exception("Non existing task");
	}

	tasks[index].setName(name);
}

void User::updateTaskDescription(unsigned id, const String& description)
{
	int index = findTask(id);

	if (index == -1) {
		throw std::exception("Non existing task");
	}

	tasks[index].setDescription(description);
}

void User::startTask(unsigned id)
{
	int index = findTask(id);

	if (index == -1) {
		throw std::exception("Non existing task");
	}

	tasks[index].setStatus(Status::IN_PROGRESS);
}

void User::deleteTask(unsigned id)
{
	int index = findTask(id);

	if (index == -1) {
		throw std::exception("Non existing task");
	}

	try {
		dash.removeFromTodo(id);
	}
	catch(std::exception& e){}

	DatePool::getInstance().removeDate(tasks[index].getTaskDate(), tasks[index].getName());
	tasks.erase(index);
}

void User::listTasks(const String& date) const
{
	Date temp(date);
	int count = 0;
	int size = tasks.size();

	for (int i = 0; i < size; i++) {
		if (!tasks[i].hasDate()) continue;

		if (tasks[i].getTaskDate() == temp) {
			std::cout << tasks[i];
			count++;
		}
	}

	if (count == 0) std::cout << "No tasks for that date!" << std::endl;
}

void User::listTasks() const
{
	int size = tasks.size();

	if (size == 0) {
		std::cout << "No tasks found!" << std::endl;
	}
	for (int i = 0; i < size; i++) {
		std::cout << tasks[i] << std::endl;
	}
}

void User::getTask(const String& name) const
{
	int minIndex = -1;
	int size = tasks.size();

	for (int i = 0; i < size; i++) {
		if (name == tasks[i].getName()) {
			if (minIndex == -1) minIndex = i;

			else minIndex = (i < minIndex) ? i : minIndex;
		}
	}
	if (minIndex==-1) throw std::exception("There is not such user!");

	std::cout << tasks[minIndex];
}

void User::getTask(unsigned id) const
{
	int size = tasks.size();
	for (int i = 0; i < size; i++) {
		if (id == tasks[i].getId()) std::cout << tasks[i];
	}
	throw std::exception("There is not such user!");
}

void User::listCompleted() const
{
	int size = tasks.size();
	int count = 0;

	for (int i = 0; i < size; i++) {
		if (tasks[i].getStatus() == Status::DONE) {
			std::cout << tasks[i];
			count++;
		}
	}
	if (count == 0) std::cout << "No finished tasks!" << std::endl;
}

void User::finishTask(unsigned id)
{
	int index = findTask(id);

	if (index == -1) throw std::exception("Task not found!");

	tasks[index].setStatus(Status::DONE);
}

void User::listDashboard() const
{
	int size = dash.getSize();

	if (size == 0) {
		std::cout << "No tasks found in dashboard!" << std::endl;
	}
	for (int i = 0; i < size; i++) {
		std::cout << dash.getTask(i) << std::endl;
	}
}

void User::addTaskToDashboard(unsigned id)
{
	int index = findTask(id);

	if (index==-1) throw std::exception("Task not found!");

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
