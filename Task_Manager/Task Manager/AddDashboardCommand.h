#pragma once
#include "Command.h"

class AddDashboardCommand: public Command
{
public:
	AddDashboardCommand(System* s);

	void execute() const override;
};

