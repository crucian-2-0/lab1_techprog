#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

// Класс элемента очереди
class Element {
private:
    int data;
    Element* prev;

public:
    Element(); //пустой конструктор
    Element(int value, Element* p = nullptr); //с параметрами
    Element(const Element& other); //копирования
    ~Element();

    int getData() const;
    Element* getPrev() const;
    void setData(int value);
    void setPrev(Element* p);
};

// Абстрактный базовый класс "Очередь"
class Queue {
private:
    Element* head; //начало очереди (отсюда извлекаем)
    Element* tail; //конец очереди (сюда добавляем)

protected:
    int count; //количество элементов

    // Защищённые методы для доступа в наследниках
    Element* getHead() const;
    Element* getTail() const;
    void setHead(Element* h);
    void setTail(Element* t);

public:
    // Конструкторы и деструктор
    Queue(); //пустой конструктор (создает пустую очередь)
    Queue(int initialValue); //с  параметрами (НЕ используется)
    Queue(const Queue& other); //конструктор копирования
    virtual ~Queue(); //нужен, чтобы при удалении объекта через указатель на Queue вызывались дестукторы наследников

    // Оператор присваивания
    Queue& operator=(const Queue& other);

    // Базовые операции очереди (не виртуальные)
    void pushBack(int value); //добавить в конец
    int popFront(); //извлечь из начала
    bool isEmpty() const; //проверка на пустоту
    int getCount() const; //получение количества элементов
    void clear(); //очистка очереди

    // Методы для просмотра/установки значений по индексу
    int getAt(int index) const;
    void setAt(int idex, int value);

    // Чисто виртуальные методы (интерфейс для наследников)
    virtual void add(int value) = 0; //добавить элемент
    virtual int remove() = 0; //извлечь элемент
    virtual void print() const = 0; //вывести на экран
    virtual void save(std::ofstream& out) const = 0; //сохранить в файл
    virtual void load(std::ifstream& in) = 0; //загрузить из файла
    virtual std::string getType() const = 0; //вернуть название типа

    // Перегрузка оператора вывода
    friend std::ostream& operator<<(std::ostream& os, const Queue& q);
};

#endif