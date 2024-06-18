#pragma once
#include "Command.h"

class CreateCollabCommand : public Command
{
public:
	CreateCollabCommand(System* s);

	void execute() const override;
};

