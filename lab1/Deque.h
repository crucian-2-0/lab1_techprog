#ifndef DEQUE_H
#define DEQUE_H

#include "Queue.h"

// Класс "Дек" — наследник очереди
class Deque : public Queue {
public:
    Deque();
    Deque(const Deque& other);
    virtual ~Deque();

    // Реализация виртуальных методов
    void add(int value) override; //добавление в конец
    int remove() override; //удаление из начала
    void print() const override;
    void save(std::ofstream& out) const override;
    void load(std::ifstream& in) override;
    std::string getType() const override;

    // Дополнительные методы дека
    void pushFront(int value); //добавление в начало
    void pushBack(int value); //добавление в конец
    int popFront(); //удаление из начала
    int popBack(); //удаление с конца
};

#endif