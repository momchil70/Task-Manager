#pragma once
#include "User.h"
#include "Task.h"

class Collaboration
{
	String name;
	unsigned id = 0;
	const User* creator = nullptr;
	Task** tasks = nullptr;
	int capacity = 4;
	int count = 0;
	MyVector<User*> participants;

	unsigned findTask(unsigned id) const;

	void resize(int newCap);
	void free();
	void copyFrom(const Collaboration& other);
	void moveFrom(Collaboration&& other);
	int findFreeIndex() const;
public:
	Collaboration();
	Collaboration(const Collaboration& other);
	Collaboration(Collaboration&& other);
	Collaboration& operator=(const Collaboration& other);
	Collaboration& operator=(Collaboration&& other);
	~Collaboration();

	bool isUserIn(const User& u) const;

	Collaboration(const User& creator, const String& name, unsigned _id);

	void listTasks() const;

	void addUser(User& user);

	void addTask(Task*& t);

	const String& getName() const;

	unsigned getId() const;

	unsigned getTasksCapacity() const;

	const Task* getTask(unsigned index) const;

	Task* getTaskById(unsigned id);

	const User& getCreator() const;

	void removeTask(unsigned id);



	void saveToDatabase(std::ofstream& ofs) const;
};

