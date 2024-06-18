#pragma once
#include "Command.h"

class FinishCommand : public Command
{

public:
	FinishCommand(System* s);

	void execute() const override;
};

