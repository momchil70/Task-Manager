#pragma once
#include "Task.h"
#include "CollabTask.h"
#include "Vector.hpp"
#include "Optional.hpp"
#include "Container.hpp"


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

