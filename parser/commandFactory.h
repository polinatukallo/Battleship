#ifndef COMMANDFACTORY_H
#define COMMANDFACTORY_H

#include "command.h"
#include <unordered_map>
#include <memory>
#include <string>

class CommandFactory {
private:
    std::unordered_map<std::string, std::shared_ptr<Command>> commands; 
    /* std::shared_ptr применяется для управления временем жизни объектов команд
    Избежать ручного удаления объектов */

public:
    CommandFactory() {
        commands["ping"] = std::make_shared<PingCommand>();
        commands["exit"] = std::make_shared<ExitCommand>();
        commands["set"] = std::make_shared<SetCommand>();
        commands["create"] = std::make_shared<CreateRole>();
        commands["start"] = std::make_shared<Start>();
        commands["stop"] = std::make_shared<Stop>();
        commands["get"] = std::make_shared<GetCommand>();
        commands["shot"] = std::make_shared<Shot>();
        commands["finished"] = std::make_shared<Finished>();
        commands["win"] = std::make_shared<Win>();
        commands["lose"] = std::make_shared<Lose>();
        commands["dump"] = std::make_shared<Dump>();
        commands["load"] = std::make_shared<Load>();
    }

    std::shared_ptr<Command> getCommand(const std::string& name) {
        if (commands.find(name) != commands.end()) {
            return commands[name];
        }
        return nullptr; // если команда не найдена
    }
};

#endif // COMMANDFACTORY_H
