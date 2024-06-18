#pragma once
#include "Command.h"

class GetTaskCommand : public Command
{
	bool marker;
public:
	GetTaskCommand(System* s, bool marker);

	void execute() const override;
};

