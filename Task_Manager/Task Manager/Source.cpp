#include <iostream>
#include "CommandExecutor.h"


int main() {
    System s;
	CommandExecutor ce(&s);
	ce.executeCommands();
}