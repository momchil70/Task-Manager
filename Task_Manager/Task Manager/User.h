#pragma once
#include <fstream>
#include "Container.hpp"
#include "Task.h"
#include "CollabTask.h"
#include "String.h"
#include "Dashboard.h"


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

	void add_task(const String& name, const String& date, const String& description); //tuk trqbva da si priema parametrite momche

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

	void saveToDatabase(std::ofstream& ofs) const;

	void getFromDataBase(std::ifstream& ifs);
};

