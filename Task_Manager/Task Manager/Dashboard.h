#pragma once
#include "Task.h"
#include "Vector.hpp"


class Dashboard
{
	MyVector<Task> todo;

	Date today;

	int findTask(unsigned id) const;
public:

	void addTodo(const Task& t);

	void removeFromTodo(unsigned id);

	unsigned getSize() const;

	const Task& getTask(unsigned index) const;

	void setDate(const Date& d);

};
