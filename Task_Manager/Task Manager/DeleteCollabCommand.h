#pragma once
#include "Command.h"

class DeleteCollabCommand : public Command
{
public:
	DeleteCollabCommand(System* s);

	void execute() const override;
};

