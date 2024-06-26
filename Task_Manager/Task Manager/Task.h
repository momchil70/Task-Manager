#pragma once
#include <fstream>
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
protected:
	String userGivenDate;
	String name;
	unsigned id = 0;
	Status s =  Status::ON_HOLD;
	String description;
	Optional<Date> date;

public:

	Task() = default;

	Task(const String& _name, const String& due_date, const String& _description, unsigned id);

	const String& getName() const;

	const String& getDescription() const;

	Status getStatus() const;

	const String& getUserGiven() const;

	unsigned getId() const;

	void setStatus(Status _s);

	void setName(String newName);

	void setDescription(String newDescr);

	const Date& getTaskDate() const;

	bool hasDate() const;

	void clearDate(); // using it for temp while adding. The pool is managed by ~Task()

	void setDate(const Date* d);

	virtual ~Task();

	virtual bool isCollabTask() const;

	virtual Task* clone() const;

	virtual void saveToDataBase(std::ofstream& ofs) const;

	virtual void getFromDataBase(std::ifstream& ifs);

	virtual void print() const;

	virtual const String& getAsignee() const;

	virtual unsigned getCollabId() const;
};

bool operator==(const Task& left, const Task& right);
