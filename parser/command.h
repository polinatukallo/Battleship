#ifndef COMMAND_H
#define COMMAND_H
#pragma once

#include <string>
#include <iostream>
#include <cstdlib> // Для exit()
#include <sstream> // для std::istringstream

#include "../game/field.h"

class Command {
public:
    virtual ~Command() = default;
    virtual void execute(const std::string& args, Field& field, FieldByUser& f) = 0; 
};



class PingCommand : public Command {
public:
    void execute(const std::string& args, Field& field, FieldByUser& f) override {
        std::cout << "pong\n";
    }
};

class ExitCommand : public Command {
public:
    void execute(const std::string& args, Field& field, FieldByUser& f) override {
        std::cout << "ok\n";
        exit(0);
    }
};

class SetCommand : public Command {
public:
    void execute(const std::string& args, Field& field, FieldByUser& f) override;
};

class CreateRole : public Command {
public:
    void execute(const std::string& args, Field& field, FieldByUser& f) override;
};

class Start : public Command {
public:
    void execute(const std::string& args, Field& field, FieldByUser& f) override;
};

class Stop : public Command {
public:
    void execute(const std::string& argsv, Field& field, FieldByUser& f) override;
};

class GetCommand : public Command {
public:
    void execute(const std::string& args, Field& field, FieldByUser& f) override;
};

class Shot : public Command {
public: 
    void execute(const std::string& args, Field& field, FieldByUser& f) override;
};

class Finished : public Command {
public:
    void execute(const std::string& args, Field& field, FieldByUser& f) override;
};

class Win : public Command {
public:
    void execute(const std::string& args, Field& field, FieldByUser& f) override;
};

class Lose : public Command {
public:
    void execute(const std::string& args, Field& field, FieldByUser& f) override;
};

class Dump : public Command {
public:
    void execute(const std::string& args, Field& field, FieldByUser& f) override;
};

class Load : public Command {
public:
    void execute(const std::string& args, Field& field, FieldByUser& f) override;
};



#endif // COMMAND_H
