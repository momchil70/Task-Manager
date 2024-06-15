#pragma once
#include "String.h"
#include "Date.h"
#include "Optional.hpp"
#include "DatePool.h"

enum class Status {
	ON_HOLD,
	IN_PROGRESS,
	DONE,
	OVERDUE
};


class Task
{
	static unsigned nextId;
	String name;
	unsigned id = 0;
	Status s =  Status::ON_HOLD;
	String description;
	Optional<Date> date;

public:

	Task() = default;

	Task(const String& _name, const String& due_date, const String& _description);

	const String& getName() const;

	const String& getDescription() const;

	Status getStatus() const;

	unsigned getId() const;

	void setStatus(Status _s);

	void setName(String newName);

	void setDescription(String newDescr);

	const Date& getTaskDate() const;

	bool hasDate() const;

	void clearDate(); // using it for temp while adding. The pool is managed by ~Task()

	void setDate(const Date* d);

	~Task();

	friend std::ostream& operator<<(std::ostream& os, const Task& t);

};

bool operator==(const Task& left, const Task& right);
