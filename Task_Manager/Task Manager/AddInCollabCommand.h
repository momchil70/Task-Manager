#pragma once
#include "Command.h"

class AddInCollabCommand : public Command
{
public:
	AddInCollabCommand(System* s);

	void execute() const override;
};

