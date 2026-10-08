#ifndef STACK_H
#define STACK_H

#include "Queue.h"

// Класс "Стек" — наследник очереди
class Stack : public Queue {
public:
    Stack();
    Stack(const Stack& other);
    virtual ~Stack();

    // Реализация виртуальных методов
    void add(int value) override; //добавление на вершину (в конец)
    int remove() override; //удаление с вершины (с конца)
    void print() const override;
    void save(std::ofstream& out) const override;
    void load(std::ifstream& in) override;
    std::string getType() const override;

    // Дополнительные методы стека
    void push(int value); //то же, что add
    int pop(); //то же, что remove
    int peek() const; //посмотреть вершину без удаления
};

#endif