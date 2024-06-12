#include "Dashboard.h"

int Dashboard::findTask(unsigned id) const
{
	for (int i = 0; i < todo.size(); i++) {
		if (id == todo[i].getId()) return i;
	}
	return -1;
}

void Dashboard::addTodo(const Task& t)
{
	todo.push_back(t);
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

const Task& Dashboard::getTask(unsigned index) const
{
	return todo[index];
}
