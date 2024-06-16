#pragma once
#include "Command.h"

class UpdateTaskCommand : public Command
{
	bool marker;
public:
	UpdateTaskCommand(System* s, bool marker);

	void execute() const override;
};

