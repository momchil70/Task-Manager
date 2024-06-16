#pragma once
#include "Command.h"

class ListTasksCommand : public Command
{

public:
	ListTasksCommand(System* s);

	void execute() const override;
};

