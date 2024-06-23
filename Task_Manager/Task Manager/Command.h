#pragma once
#include <iostream>
#include "String.h"
#include "System.h"

class System;

class Command
{
protected:
	System* system;

public:

	Command(System* s);
	virtual void execute() const = 0;
	virtual ~Command() = default;
};

