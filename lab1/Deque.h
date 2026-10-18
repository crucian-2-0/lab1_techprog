#ifndef DEQUE_H
#define DEQUE_H

#include "Queue.h"

// Класс Дек — наследник очереди
class Deque : public Queue {
public:
    Deque();
    Deque(int initialValue); //НЕ используется
    Deque(const Deque& other);
    virtual ~Deque();

    // Реализация виртуальных методов
    void add(int value) override; //добавление в конец
    int remove() override; //удаление из начала
    void print() const override; //вывести на экран
    void save(std::ofstream& out) const override; //сохранить в файл
    void load(std::ifstream& in) override; //загрузить из файла
    std::string getType() const override; //вернуть название типа

    // Дополнительные методы дека
    void pushFront(int value); //добавление в начало
    void pushBack(int value); //добавление в конец
    int popFront(); //удаление из начала
    int popBack(); //удаление с конца

    friend std::ostream& operator<<(std::ostream& os, const Deque& d);
};

#endif