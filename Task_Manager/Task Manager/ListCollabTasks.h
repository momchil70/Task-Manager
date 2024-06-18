#pragma once
#include "Command.h"

class ListCollabTasks : public Command
{
public:
	ListCollabTasks(System* s);

	void execute() const override;
};

