#ifndef LIST_H
#define LIST_H

#include "Queue.h"

// Класс Список — наследник очереди
class List : public Queue {
public:
    List(); //пустой конструктор
    List(const List& other); //конструктор копирования
    virtual ~List(); //виртуальный деструктор

    // Реализация виртуальных методов
    void add(int value) override; //добавление в конец
    int remove() override; //удаление из начала
    void print() const override; //вывести на экран
    void save(std::ofstream& out) const override; //сохранить в файл
    void load(std::ifstream& in) override; //загрузить из файла
    std::string getType() const override; //вернуть название типа

    // Дополнительные методы списка
    void insertAt(int index, int value); //вставка по индексу
    void removeAt(int index); //удаление по индексу
    int getAt(int index) const; //получить элемент по индексу
};

#endif