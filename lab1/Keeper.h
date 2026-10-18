#ifndef KEEPER_H
#define KEEPER_H

#include "Queue.h"
#include <string>

// Класс Хранилище — хранит указатели на объекты Queue
class Keeper {
private:
    Queue** containers; //динамический массив указателей
    int size; //текущее количество контейнеров
    int capacity; //вместимость массива

    void resize(); //расширение массива при необходимости

public:
    Keeper();
    Keeper(int initialCapacity); //НЕ используется (нужно для вып. требований)
    Keeper(const Keeper& other); //НЕ используется (нужно для вып. требований)
    ~Keeper();

    void addContainer(int type);
    void removeContainer(int index);
    void printAll() const;
    int getCount() const;
    Queue* getContainer(int index) const;
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};

#endif