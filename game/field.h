#ifndef FIELD_H
#define FIELD_H

#pragma once

#include <vector>
#include <unordered_map> 
#include <memory> // для уникальных указателей
#include <utility>
#include <set>

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2>& pair) const {
        auto hash1 = std::hash<T1>{}(pair.first);
        auto hash2 = std::hash<T2>{}(pair.second);
        return hash1 ^ (hash2 << 1); // XOR и сдвиг для комбинирования
    }
};


class Ship {
public:
    int size;
    bool orient; // 0 - horizontal, 1 - vertical
    int xCoord;
    int yCoord;
    int hits; //countOfDeadPoints

    Ship(int xCoord1, int yCoord1, int size1, bool orient1) :
    size(size1), orient(orient1), xCoord(xCoord1), yCoord(yCoord1), hits(0) {};

    
};

void makeFieldByUser();

struct FieldByUser {
    bool ifWasSet = false;
    int w = 5;
    int h = 5;
    int fcount1 = 0;
    int fcount2 = 2;
    int fcount3 = 0;
    int fcount4 = 0;
    int strategy = 2; // 1 - ordered ; 2 - custom
};

class Field {
private:
    FieldByUser* f; // структура для slave

    bool ifFinished = false; // для finished
    int width = 0;
    int heigth = 0;
    int count1 = 0;
    int count2 = 0;
    int count3 = 0;
    int count4 = 0;
    int sumOfShips = 0;
    std::set<std::pair<int, int>> wasShoot;
    std::unordered_map<std::pair<int, int>, Ship*, pair_hash> map; // поле
    std::pair <int, int> lastShot = {-1, -1};

    void placeShip(int x, int y, int size, bool horizontal);
    bool ifPossible(int x, int y, int size, bool orientation);    
    void placeShips();

public:
    ~Field();
    bool ifWasStarted = false;
    void printField();
    void shot(int x, int y);
    void shot();
    void afterShot();
    void createFieldByParameters();
    void makeField();

    void dump(const std::string& filePath);
    void load(const std::string& filePath);

    void linkFieldByUser(FieldByUser& f1) {
        f = &f1;
    }

    int getWidth();
    int getHeigth();
    int getCount1();
    int getCount2();
    int getCount3();
    int getCount4();
    int getSumOfShips();
    bool getIfFinished();
    void setIfFinished();
    
};



#endif // FIELD_H