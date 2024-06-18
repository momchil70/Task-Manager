#include "Collaboration.h"

bool Collaboration::isUserIn(const User& u) const
{
	if (u == *creator) return true;
	int size = participants.size();
	for (int i = 0; i < size; i++) {
		if (u == *participants[i]) return true;
	}
	return false;
}

Collaboration::Collaboration(const User& creator, const String& name, unsigned _id)
{
	this->creator = &creator;
	this->name = name;
	id = _id;
}

void Collaboration::listTasks() const
{
	int size = tasks.getSize();
	for (int i = 0; i < size; i++) {
		tasks[i]->print();
	}
}

void Collaboration::addUser(User& user)
{
	participants.push_back(&user);
}

void Collaboration::addTask(const Task& t)
{
	tasks.add(t);
}

const String& Collaboration::getName() const
{
	return name;
}

unsigned Collaboration::getId() const
{
	return id;
}

Task* Collaboration::getLastTask()
{
	return tasks[tasks.getSize() - 1];
}
