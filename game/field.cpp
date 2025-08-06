#include <iomanip>

#include "field.h"
#include "../parser/command.h"
#include "ctime"
#include "fstream"
#include <set>


Field::~Field() {
    for (auto& [key, ship] : map) {
        delete ship;
    }
    map.clear(); 
}

void Field::printField() {
    std::vector<std::vector<char>> grid(width, std::vector<char>(heigth, '.')); // '.' - пустая ячейка

    std::cout << "  ";
    for (int j = 0; j < heigth; j++) {
        std::cout << j << " ";
    }
    std::cout << "\n";

    for (const auto& entry : map) {
        const auto& [coords, ship] = entry;
        int x = coords.first;
        int y = coords.second;

        if (x >= 0 && x < width && y >= 0 && y < heigth && ship != nullptr) {
            grid[x][y] = '#'; // здесь строки - `x`, а столбцы - `y`
        }
    }

    for (int i = 0; i < width; ++i) {
        std::cout << i << " "; 
        for (int j = 0; j < heigth; ++j) {
            std::cout << grid[i][j] << ' ';
        }
        std::cout << '\n';
    }
}



bool Field::ifPossible(int x, int y, int size, bool horizontal) {
    for (int i = 0; i < size; ++i) {
        int newX = horizontal ? x + i : x;
        int newY = horizontal ? y : y + i;

        if (newX < 0 || newY < 0 || newX >= width || newY >= heigth) {
            return false; 
        }
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                int neighborX = newX + dx;
                int neighborY = newY + dy;

                if (neighborX < 0 || neighborY < 0 || neighborX >= width || neighborY >= heigth) {
                    continue;
                }

                // проверяем занята ли соседняя ячейка
                if (map.find({neighborX, neighborY}) != map.end()) {
                    return false; 
                }
            }
        }
        
    }
    return true; // все свободно
}

void Field::placeShip(int x, int y, int size, bool horizontal) {
    Ship* ship = new Ship(x, y, size, (bool)horizontal);
    for (int i = 0; i < size; ++i) {
        int newX = horizontal ? x + i : x;
        int newY = horizontal ? y : y + i;

        map[{newX, newY}] = ship;
    }
}

void Field::makeField() {
    srand(time(0));

    width = rand() % (20 - 10 + 1) + 10;
    heigth = rand() % (20 - 10 + 1) + 10;
    int k = 0, count = 0, size, hor, x, y;

    while (k < 20 and count < 200) { //200
        x = rand() % width;
        y = rand() % heigth;
        hor = rand() % 2; 
        size = rand() % 4 + 1;
        if (ifPossible(x, y, size, (bool)hor)) {
            
            placeShip(x, y, size, (bool)hor);
            k++;
            switch (size) {
                case 1 : count1++;break;
                case 2 : count2++;break;
                case 3 : count3++;break;
                case 4 : count4++;break;
                default: break;
            }
        }
        count++;
    }
    //printField();
    sumOfShips = count1 + count2 * 2 + count3 * 3 + count4 * 4;

    return;
}

void Field::placeShips() {
    int toplace1 = count1;
    int toplace2 = count2;
    int toplace3 = count3;
    int toplace4 = count4;
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < heigth; ++y) {
            if (toplace4 > 0 && ifPossible(x, y, 4, true)) {
                placeShip(x, y, 4, true);
                toplace4--;
            } else if (toplace3 > 0 && ifPossible(x, y, 3, true)) {
                placeShip(x, y, 3, true);
                toplace3--;
            } else if (toplace2 > 0 && ifPossible(x, y, 2, true)) {
                placeShip(x, y, 2, true);
                toplace2--;
            } else if (toplace1 > 0 && ifPossible(x, y, 1, true)) {
                placeShip(x, y, 1, true);
                toplace1--;
            }

            if (toplace1 == 0 && toplace2 == 0 && toplace3 == 0 && toplace4 == 0) {
                return;
            }
        }
    }
    if (toplace1 + toplace2 + toplace3 + toplace4 > 0) {
        std::cerr << "Ships wasn't place\n";
        exit(0);
    }
}

void Field::createFieldByParameters() {
    width = f->w;
    heigth = f->h;
    count1 = f->fcount1;
    count2 = f->fcount2;
    count3 = f->fcount3;
    count4 = f->fcount4;

    sumOfShips = count1 + count2 * 2 + count3 * 3 + count4 * 4;
    placeShips();
    //printField();

}


void Field::shot(int x, int y) { // мы делаем выстрел
    if (map.find({x, y}) == map.end()) { // корабля нет
        std::cout << "miss\n";
        return;
    }
    if (map[{x, y}] == nullptr) { // корабль там уже был пробит
        std::cout << "miss\n";
        return;
    }
    Ship* ship = map[{x, y}];
    if (ship->size - 1 == ship->hits) {
        std::cout << "kill\n";
        if (ship->size == 1) {
            count1--;
        }  if (ship->size == 2) {
            count2--;
        }  if (ship->size == 3) {
            count3--;
        }  if (ship->size == 4) {
            count4--;
        } 
        map[{x, y}] = nullptr;
    } else {
        std::cout << "hit\n";
        ship->hits++;
        map[{x, y}] = nullptr;
    }
    return;

}

void Field::shot() { // стреляет компьютер
    int& x = lastShot.first;
    int& y = lastShot.second;
    if (f->strategy == 1) { //ordered 
        if (x == -1 and y == -1) {
            x = 0;
            y = 0;
        } else {
            if (x + 1 < width) {
                x++;
            } else {
                y++;
                x = 0;
            }
        }
        
    } else if (f->strategy == 2) {
        x = 0; y = 0;
        while (wasShoot.find({x, y}) != wasShoot.end()) {
            srand(time(0));
            x = rand() % (width + 1);
            y = rand() % (heigth + 1);
        }
        wasShoot.insert({x, y});
    }
    std::cout << x << " " << y << '\n';

}

void Field::afterShot() {
    sumOfShips--;
}

//dump .\\files\\t.txt 
void Field::dump(const std::string& filePath) {
    std::set<Ship*> uniqueShips; 
    std::ofstream outFile(filePath);
    if (!outFile.is_open()) {
        std::cerr << "Couldn't open the file!\n";
        return;
    }

    outFile << width << " " << heigth << '\n';

    for (const auto& [key, ship] : map) {
        if (uniqueShips.find(ship) == uniqueShips.end()) {
            uniqueShips.insert(ship);  

            int minX = ship->xCoord;
            int minY = ship->yCoord;

            for (int i = 0; i < ship->size; ++i) {
                int newX = ship->orient ? ship->xCoord + i : ship->xCoord;
                int newY = ship->orient ? ship->yCoord : ship->yCoord + i;

                if (newX < minX || (newX == minX && newY < minY)) {
                    minX = newX;
                    minY = newY;
                }
            }

            outFile << ship->size << " "
                    << (ship->orient ? "v" : "h") << " "
                    << minX << " "
                    << minY << "\n";
        }
    }
    
}

void Field::load(const std::string& filePath) {
    std::ifstream inFile(filePath);
    if (!inFile.is_open()) {
        std::cerr << "Couldn't open the file!\n";
        return;
    }

    inFile >> width >> heigth;
    for (auto& [key, ship] : map) {
        delete ship;
    }
    map.clear();

    int size;
    char orientation;
    int x, y;

    while (inFile >> size >> orientation >> x >> y) {
        bool horizontal = (orientation == 'v'); 

        Ship* ship = new Ship(x, y, size, horizontal);

        for (int i = 0; i < size; ++i) {
            int newX = horizontal ? x + i : x;
            int newY = horizontal ? y : y + i;

            map[{newX, newY}] = ship;
        }
    }

    inFile.close();
}

int Field::getWidth() {
    return width;
}
int Field::getHeigth() {
    return heigth;
}
int Field::getCount1() {
    return count1;
}
int Field::getCount2() {
    return count2;
}
int Field::getCount3() {
    return count3;
}
int Field::getCount4() {
    return count4;
}
int Field::getSumOfShips() {
    return sumOfShips;
}
bool Field::getIfFinished() {
    return ifFinished;
}
void Field::setIfFinished() {
    ifFinished = true;
}