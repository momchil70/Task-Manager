#pragma once
#include "Command.h"

class ListCollabsCommand : public Command
{
public:
	ListCollabsCommand(System* s);

	void execute() const override;
};

