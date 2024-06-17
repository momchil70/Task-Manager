#pragma once
#include "Command.h"

class ListTasksCommand : public Command
{
	bool marker;
public:
	ListTasksCommand(System* s, bool marker);

	void execute() const override;
};

