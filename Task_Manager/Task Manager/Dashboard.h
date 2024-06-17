#pragma once
#include "Task.h"
#include "CollabTask.h"
#include "Vector.hpp"
#include "Optional.hpp"
#include "Container.hpp"


class Dashboard
{
	MyVector<Task*> todo;


	int findTask(unsigned id) const;
public:

	void addTodo(Task* t);

	void removeFromTodo(unsigned id);

	unsigned getSize() const;

	const Task* getTask(unsigned index) const;

	unsigned getTaskId(int index) const;

	void print() const;
};

