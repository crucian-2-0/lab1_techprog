#ifndef LIST_H
#define LIST_H

#include "Queue.h"

// Класс "Список" — наследник очереди
class List : public Queue {
public:
    List();
    List(const List& other);
    virtual ~List();

    // Реализация виртуальных методов
    void add(int value) override; //добавление в конец
    int remove() override; //удаление из начала
    void print() const override;
    void save(std::ofstream& out) const override;
    void load(std::ifstream& in) override;
    std::string getType() const override;

    // Дополнительные методы списка
    void insertAt(int index, int value); //вставка по индексу
    void removeAt(int index); //удаление по индексу
    int getAt(int index) const; //получить элемент по индексу
};

#endif