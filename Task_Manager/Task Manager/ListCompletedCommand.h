#pragma once
#include "Command.h"

class ListCompletedCommand : public Command
{

public:
	ListCompletedCommand(System* s);

	void execute() const override;
};

