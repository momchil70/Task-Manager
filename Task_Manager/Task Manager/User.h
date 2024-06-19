#pragma once
#include <fstream>
#include "Container.hpp"
#include "Task.h"
#include "CollabTask.h"
#include "String.h"
#include "Dashboard.h"
#include <assert.h>


class User
{
	Container<Task> tasks;
	Dashboard dash;
	String name = "";
	unsigned pass = 0;

	int findTask(unsigned id) const;
	int findTask(const String& name) const;

	bool checkForCopy(const Task& t);

	void readDashboard(std::ifstream& ifs);

	void saveDashboard(std::ofstream& ofs) const;
public:
	User() = default;

	User(const String& name, unsigned pass);

	void add_task(const String& name, const String& date, const String& description, unsigned id);
	void asign(Task* t);

	void updateTaskName(unsigned id, const String& name);

	void updateTaskDescription(unsigned id, const String& description);

	void startTask(unsigned id);

	unsigned deleteTask(unsigned id);
	void deleteTask(const Task* task);

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

	void saveToDatabase(std::ofstream& ofs) const;

	void getFromDataBase(std::ifstream& ifs);

	void configDashboard(const Date& today);

	void configTasks(const Date& today);

	bool containsId(unsigned id) const;
};

bool operator==(const User& lhs, const User& rhs);
bool operator!=(const User& lhs, const User& rhs);