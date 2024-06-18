#pragma once
#include "Command.h"

class AsignTaskCommand : public Command
{
public:
	AsignTaskCommand(System* s);

	void execute() const override;
};

