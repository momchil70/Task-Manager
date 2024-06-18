#pragma once
#include "Task.h"
#include "String.h"

class CollabTask: public Task
{
	String asignee;

public:
	CollabTask() = default;

	CollabTask(const String& _name, const String& due_date, const String& _description, const String& asignee);

	bool isCollabTask() const override;

	Task* clone() const override;

	void saveToDataBase(std::ofstream& ofs) const override;

	void getFromDataBase(std::ifstream& ifs) override;

	void print() const override;
};


