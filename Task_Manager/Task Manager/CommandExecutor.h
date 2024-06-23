#pragma once
#include "Command.h"
#include "CommandFactory.h"


class CommandExecutor {
    System* system = nullptr;

public:
    CommandExecutor(System* system) : system(system) {}

    void executeCommands();
};
