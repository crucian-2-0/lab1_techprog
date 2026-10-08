#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <fstream>
#include <string>

// Класс элемента очереди
class Element {
private:
    int data;
    Element* prev;

public:
    Element(int value = 0, Element* p = nullptr);
    ~Element();

    int getData() const;
    Element* getPrev() const;
    void setData(int value);
    void setPrev(Element* p);
};

// Абстрактный базовый класс "Очередь"
class Queue {
private:
    Element* head; //начало очереди (откуда извлекаем)
    Element* tail; //конец очереди (куда добавляем)
    int count; //количество элементов

protected:
    // Защищённые методы для доступа в наследниках
    Element* getHead() const;
    Element* getTail() const;
    void setHead(Element* h);
    void setTail(Element* t);

public:
    // Конструкторы и деструктор
    Queue();
    Queue(const Queue& other);
    virtual ~Queue();

    // Оператор присваивания
    Queue& operator=(const Queue& other);

    // Базовые операции очереди (не виртуальные)
    void pushBack(int value); //добавить в конец
    int popFront(); //извлечь из начала
    bool isEmpty() const;
    int getCount() const;
    void clear();

    // Чисто виртуальные методы (интерфейс для наследников)
    virtual void add(int value) = 0;
    virtual int remove() = 0;
    virtual void print() const = 0;
    virtual void save(std::ofstream& out) const = 0;
    virtual void load(std::ifstream& in) = 0;
    virtual std::string getType() const = 0;
};

#endif