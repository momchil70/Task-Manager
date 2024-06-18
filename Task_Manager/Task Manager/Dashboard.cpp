#include "Dashboard.h"

int Dashboard::findTask(unsigned id) const
{
	int size = todo.size();
	for (int i = 0; i < size; i++) {
		if (id == todo[i]->getId()) return i;
	}
	return -1;
}

void Dashboard::addTodo(Task* t)
{
	todo.push_back(t);
}

void Dashboard::removeFromTodo(unsigned id)
{
	int index = findTask(id);

	if (index == -1) throw std::exception("No such task in Dashboard!");

	todo.erase(index);
	std::cout << "Task removed successfully from dashboard!" << std::endl;
}

unsigned Dashboard::getSize() const
{
	return todo.size();
}

const Task* Dashboard::getTask(unsigned index) const
{
	if (index > todo.size()) throw std::exception("Invalid index!");

	return todo[index];
}

unsigned Dashboard::getTaskId(int index) const
{
	return todo[index]->getId();
}