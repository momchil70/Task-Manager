#pragma once
#include "Command.h"

class AddTaskCommand : public Command
{

public:
	AddTaskCommand(System* s);

	void execute() const override;
};

