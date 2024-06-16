#pragma once
#include "Command.h"

class RegisterCommand : public Command
{

public:
	RegisterCommand(System* s);

	void execute() const override;
};

