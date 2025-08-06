
#include <iostream>
#include <cstdlib> // Для exit()
#include <sstream> // для std::istringstream
#include <fstream>
#include "ctime"


#include "command.h"
#include "../game/field.h"
//#include "../main.cpp"

//FieldByUser f;


void SetCommand::execute(const std::string& args, Field& field, FieldByUser& f) {
    std::istringstream iss(args);
    std::string secArgs, thirdArgs, fourthArgs;
    iss >> secArgs >> thirdArgs >> fourthArgs;
     
    if (secArgs == "width") {
        int width = std::stoi(thirdArgs);
        f.w = width;

    } else if (secArgs == "heigth") {
        int heigth = std::stoi(thirdArgs);
        f.h = heigth;

    } else if (secArgs == "count") {
        int whichCount = std::stoi(thirdArgs);
        int count = std::stoi(fourthArgs);
        switch (whichCount) {
            case 1 : f.fcount1 = count;break;
            case 2 : f.fcount2 = count;break;
            case 3 : f.fcount3 = count;break;
            case 4 : f.fcount4 = count;break;
            default : break;
        }
    } else if (secArgs == "strategy"){
        if (thirdArgs == "ordered") {
            f.strategy = 1;
        } else if (thirdArgs == "custom") {
            f.strategy = 2;
        }
    } else if (secArgs == "result") {
        if (thirdArgs == "miss") {
            
        } else if (thirdArgs == "hit") {
            field.afterShot(); // --
        } else if (thirdArgs == "kill") {
            field.afterShot();
        }
    }
    std::cout << "ok\n";
}

void CreateRole::execute(const std::string& args, Field& field, FieldByUser& f) {
    if (args == "master") { // компьютер - мастер
    field.makeField();
    } else if (args == "slave") {
        f.ifWasSet = true;
    }
    std::cout << "ok\n";
}

void GetCommand::execute(const std::string& args, Field& field, FieldByUser& f) {
    std::istringstream iss(args);
    std::string secArgs, thirdArgs;
    iss >> secArgs >> thirdArgs;
    if (secArgs == "width") {
        std::cout << (f.w == 0 ? field.getWidth() : f.w) << '\n';
    } else if (secArgs == "heigth") {
        std::cout << (f.h == 0 ? field.getHeigth() : f.h) << '\n';
    } else if (secArgs == "count") {
        if (!field.ifWasStarted) {
            switch (std::stoi(thirdArgs)) {
                case 1 : 
                std::cout << (f.fcount1 == 0 ? field.getCount1() : f.fcount1) << '\n';break;
                case 2 : 
                std::cout << (f.fcount2 == 0 ? field.getCount2() : f.fcount2) << '\n';break;
                case 3 : 
                std::cout << (f.fcount3 == 0 ? field.getCount3() : f.fcount3) << '\n';break;
                case 4 : 
                std::cout << (f.fcount4 == 0 ? field.getCount4() : f.fcount4) << '\n';break;
                default : break;
            }
        } else {
            switch (std::stoi(thirdArgs)) {
                case 1 : 
                std::cout << field.getCount1() << '\n';break;
                case 2 : 
                std::cout << field.getCount2() << '\n';break;
                case 3 : 
                std::cout << field.getCount3() << '\n';break;
                case 4 : 
                std::cout << field.getCount4() << '\n';break;
                default : break;
            }
        }
    }
} 


void Shot::execute(const std::string& args, Field& field, FieldByUser& f) {
        if (args != "") { // мы стреляем по кораблю компьютера
            int x = std::stoi(args.substr(0, args.find(' ')));
            int y = std::stoi(args.substr(args.find(' ') + 1));
            field.shot(x, y);
        } else { // компьютер стреляет по нгам
            field.shot();
        }
}

void Start::execute(const std::string& args, Field& field, FieldByUser& f) {
    std::cout << "ok\n";
    if (f.ifWasSet) { // режим slave
        if (f.w == 0 or f.h == 0 or (f.fcount1 + f.fcount2 + f.fcount3 + f.fcount4 == 0) or f.strategy == 0) {
            std::cerr << "Not all parameters was set!\n";
            exit(0);
        } 
        field.createFieldByParameters();
    }
    field.ifWasStarted = true;
    field.printField();
    std::cout << "Game can be started\n";
}

void Dump::execute(const std::string& args, Field& field, FieldByUser& f) {
    field.dump(args);  
}

void Load::execute(const std::string& args, Field& field, FieldByUser& f) {
    field.load(args);
}

void Lose::execute(const std::string& args, Field& field, FieldByUser& f) {
    if (field.getSumOfShips() <= 0) {
        std::cout << "yes\n";
    } else {
        std::cout << "no\n";
    }
}

void Win::execute(const std::string& args, Field& field, FieldByUser& f) {
    if (field.getSumOfShips() > 0 and field.getCount1() + field.getCount2() + field.getCount3() + field.getCount4() == 0) {
        std::cout << "yes\n";
    } else {
        std::cout << "no\n";
    }
}

void Finished::execute(const std::string& args, Field& field, FieldByUser& f) {
    if (field.getIfFinished()) {
        std::cout << "yes\n";
    } else {
        std::cout << "no\n";
    }
}

void Stop::execute(const std::string& args, Field& field, FieldByUser& f) {
    field.setIfFinished();
    std::cout << "ok\n";
}
