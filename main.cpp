#include <iostream>
#include <string>

#include "parser/commandFactory.h"
#include "game/field.h"


int main() {
    CommandFactory factory;
    Field field; // поле
    FieldByUser f; // на случай create slave
    field.linkFieldByUser(f);

    while (true) {
        std::string cmd, args;
        std::getline(std::cin, cmd);
        size_t spacePos = cmd.find(' ');
        std::string commandName = cmd.substr(0, spacePos);
        if (spacePos == std::string::npos) {
           args = "";
        } else {
           args = cmd.substr(spacePos + 1);
        }

        // получаем соответствующую команду
        auto command = factory.getCommand(commandName);
        if (command) {
            command->execute(args, field, f); // выполняется команда через полиморфизм
        } else {
            std::cerr << "Unknown command: " << commandName << "\n";
        }
    }

    return 0;
}
