#pragma once
#include "Command.h"

class RemoveFromDashCommand : public Command
{
public:
	RemoveFromDashCommand(System* s);

	void execute() const override;
};

