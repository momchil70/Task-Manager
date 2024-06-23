#include "CommandExecutor.h"

void CommandExecutor::executeCommands() 
{
    String command;
    while (system->isRunning()) {
        std::cout << "->";
        std::cin >> command;

        try {
            if (command != "login" && command != "register" && command != "exit" && system->getActiveIndex() == -1) {
                throw std::exception("No logged user! Try again!");
                continue;
            }

            Command* current = createCommand(command, system);
            current->execute();
            delete current;
        }
        catch (std::exception& e) {
            std::cout << e.what() << std::endl;
            char buffer[1024];
            std::cin.getline(buffer, 1024); // to clean the rest of the junk on the row
        }
    }
}
