#pragma once
#include "Command.h"

class StartTaskCommand : public Command
{

public:
	StartTaskCommand(System* s);

	void execute() const override;
};

