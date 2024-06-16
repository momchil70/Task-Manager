#pragma once
#include "Command.h"

class LoginCommand: public Command
{

public:
	LoginCommand(System* s);

	void execute() const override;
};

