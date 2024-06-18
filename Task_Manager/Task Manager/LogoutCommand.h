#pragma once
#include "Command.h"

class LogoutCommand : public Command
{

public:
	LogoutCommand(System* s);

	void execute() const override;
};
