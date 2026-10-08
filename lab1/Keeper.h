#ifndef KEEPER_H
#define KEEPER_H

#include "Queue.h"
#include <vector>
#include <string>

// Класс "Хранилище" — хранит указатели на объекты Queue
class Keeper {
private:
    std::vector<Queue*> containers;  //массив указателей на Base (Queue)

public:
    Keeper();
    ~Keeper();

    // Добавление контейнера по типу (1 - List, 2 - Deque, 3 - Stack)
    void addContainer(int type);

    // Удаление контейнера по индексу
    void removeContainer(int index);

    // Вывод всех контейнеров
    void printAll() const;

    // Получить количество контейнеров
    int getCount() const;

    // Получить контейнер по индексу
    Queue* getContainer(int index) const;

    // Сохранение всех контейнеров в файл
    void saveToFile(const std::string& filename) const;

    // Загрузка всех контейнеров из файла
    void loadFromFile(const std::string& filename);
};

#endif