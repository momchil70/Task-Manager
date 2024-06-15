#pragma once
#include "Vector.hpp"
#include "Task.h"
#include "String.h"
#include "Dashboard.h"


class User
{
	MyVector<Task> tasks;
	Dashboard dash;
	String name = "";
	unsigned pass = 0;


	int findTask(unsigned id) const;
	int findTask(const String& name) const;

	bool checkForCopy(const Task& t);

public:
	User() = default;

	User(const String& name, unsigned pass);

	void add_task(); //tuk trqbva da si priema parametrite momche

	void updateTaskName(unsigned id, const String& name);

	void updateTaskDescription(unsigned id, const String& description);

	void startTask(unsigned id);

	void deleteTask(unsigned id);

	void listTasks(const String& date) const;

	void listTasks() const;

	void getTask(const String& name) const;

	void getTask(unsigned id) const;

	void listCompleted() const;

	void finishTask(unsigned id);

	void listDashboard() const;

	void addTaskToDashboard(unsigned id);

	void removeTaskFromDashboard(unsigned id);

	const String& getName() const;

	unsigned getPass() const;
};
