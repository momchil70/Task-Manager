#pragma once
#include "Command.h"

class ListDateCommand : public Command
{

public:
	ListDateCommand(System* s);

	void execute() const override;
};

