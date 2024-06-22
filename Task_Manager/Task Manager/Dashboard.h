#pragma once
#include "Task.h"
#include "CollabTask.h"
#include "Vector.hpp"
#include "Optional.hpp"


class Dashboard
{
	MyVector<unsigned> todo;


	int findTask(unsigned id) const;
public:

	void addTodo(unsigned id);

	void removeFromTodo(unsigned id);

	unsigned getSize() const;

	unsigned getTask(unsigned index) const;

};

