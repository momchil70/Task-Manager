#pragma once
#include "User.h"
#include "Container.hpp"
#include "Task.h"

class Collaboration
{
	String name;
	unsigned id;
	const User* creator = nullptr;
	Container<Task> tasks;
	MyVector<User*> participants;

	

public:
	Collaboration() = default;

	bool isUserIn(const User& u) const;

	Collaboration(const User& creator, const String& name, unsigned _id);

	void listTasks() const;

	void addUser(User& user);

	void addTask(const Task& t);

	const String& getName() const;

	unsigned getId() const;

	Task* getLastTask();
};

