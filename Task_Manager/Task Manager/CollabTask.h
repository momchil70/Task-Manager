#pragma once
#include "Task.h"
#include "Optional.h"

class CollabTask: public Task
{
	Optional<String> asignee;

public:

	void asignUser(const String& username);

	bool isCollabTask() const override;

	Task* clone() const override;

	void saveToDataBase(std::ofstream& ofs) const override;

	void getFromDataBase(std::ifstream& ifs) override;
};

