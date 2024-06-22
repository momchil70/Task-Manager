#include "Dashboard.h"

int Dashboard::findTask(unsigned id) const
{
	int size = todo.size();
	for (int i = 0; i < size; i++) {
		if (id == todo[i]) return i;
	}
	return -1;
}

void Dashboard::addTodo(unsigned id)
{
	todo.push_back(id);
}

void Dashboard::removeFromTodo(unsigned id)
{
	int index = findTask(id);

	if (index == -1) throw std::exception("No such task in Dashboard!");


	todo.erase(index);
}

unsigned Dashboard::getSize() const
{
	return todo.size();
}

unsigned Dashboard::getTask(unsigned index) const
{
	if (index > todo.size()) throw std::exception("Invalid index!");

	return todo[index];
}