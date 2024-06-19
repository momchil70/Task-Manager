#pragma once
#include "Task.h"
#include "String.h"

class CollabTask : public Task
{
	String asignee;
	unsigned collaborationID;

public:
	CollabTask() = default;

	CollabTask(const String& _name, const String& due_date, const String& _description, unsigned id, const String& asignee, unsigned collabID);

	bool isCollabTask() const override;

	Task* clone() const override;

	void saveToDataBase(std::ofstream& ofs) const override;

	void getFromDataBase(std::ifstream& ifs) override;

	void print() const override;

	const String& getAsignee() const override;

	unsigned getCollabId() const override;
};


