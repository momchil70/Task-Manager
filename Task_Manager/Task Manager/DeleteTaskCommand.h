#pragma once
#include "Command.h"

class DeleteTaskCommand : public Command
{
public:
	DeleteTaskCommand(System* s);

	void execute() const override;
};

