#pragma once
#include "Command.h"

class ExitCommand : public Command
{

public:
	ExitCommand(System* s);

	void execute() const override;
};
