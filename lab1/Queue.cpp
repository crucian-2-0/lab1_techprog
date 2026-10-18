#include "Queue.h"

// РЕАЛИЗАЦИЯ КЛАССА Element
// Конструктор по умолчанию
Element::Element() : data(0), prev(nullptr) {
    std::cout << "+E" << std::endl;
}

// Конструктор с параметрами
Element::Element(int value, Element* p) : data(value), prev(p) {
    std::cout << "+E" << std::endl;
}

// Конструктор копирования !!!НЕ используется (нужно для вып. требований)
Element::Element(const Element& other) : data(other.data), prev(other.prev) {
    std::cout << "+E(copy)" << std::endl;
}

Element::~Element() {
    // prev не удаляем — это задача очереди Queue::~Queue()
    std::cout << "-E" << std::endl;
}

int Element::getData() const {return data;}
Element* Element::getPrev() const {return prev;}
void Element::setData(int value) {data = value;}
void Element::setPrev(Element* p) {prev = p;}

// РЕАЛИЗАЦИЯ КЛАССА Queue

// Конструктор по умолчанию
Queue::Queue() : head(nullptr), tail(nullptr), count(0) {
    std::cout << "+Q" << std::endl;
}

// Конструктор с параметром !!!НЕ используется (нужно для вып. требований)
Queue::Queue(int initialValue) : head(nullptr), tail(nullptr), count(0) {
    std::cout << "+Q(param)" << std::endl;
    pushBack(initialValue);
}

// Конструктор копирования (глубокое копирование)
Queue::Queue(const Queue& other) : head(nullptr), tail(nullptr), count(0) {
    std::cout << "+Q(copy)" << std::endl;
    if (!other.isEmpty()) {
        int* values = new int[other.count]; //выделение массива размером с other
        Element* current = other.tail;
        for (int i = other.count - 1; i >= 0; i--) { //записываем в массив значения в обратном порядке
            values[i] = current->getData();
            current = current->getPrev();
        }
        for (int i = 0; i < other.count; i++) { //добавляем все элементы из массива в this
            pushBack(values[i]);
        }
        delete[] values;
    }
}

// Деструктор
Queue::~Queue() {
    std::cout << "-Q" << std::endl;
    clear();
}

// Оператор присваивания
Queue& Queue::operator=(const Queue& other) {
    if (this != &other) {
        clear();
        if (!other.isEmpty()) { //работает как конструктор копирования
            int* values = new int[other.count];
            Element* current = other.tail;
            for (int i = other.count - 1; i >= 0; i--) {
                values[i] = current->getData();
                current = current->getPrev();
            }
            for (int i = 0; i < other.count; i++) {
                pushBack(values[i]);
            }
            delete[] values;
        }
    }
    return *this; //возвращает this (ссылку на текущий объект), чтобы можно было писать a=b=d
}

// Защищённые методы
Element* Queue::getHead() const {return head;}
Element* Queue::getTail() const {return tail;}
void Queue::setHead(Element* h) {head = h;}
void Queue::setTail(Element* t) {tail = t;}

// Добавление в конец
void Queue::pushBack(int value) {
    Element* newElement = new Element(value, tail);
    if (isEmpty()) { //если очередь пуста, новый элемент ПЕРВЫЙ 
        head = newElement;
        tail = newElement;
    }
    else {
        tail = newElement;
    }
    count++;
}

// Извлечение из начала
int Queue::popFront() {
    if (isEmpty()) { //если очередб пуста, генерирует исключение
        throw std::runtime_error("Очередь пуста! Невозможно извлечь элемент.");
    }
    // Сохранение укзателя на удаляемый элемент и его значения
    Element* temp = head;
    int value = temp->getData();

    if (head == tail) {
        head = nullptr;
        tail = nullptr;
    }
    else {
        Element* current = tail;
        while (current->getPrev() != head) { //идем от конца до элемента у которого prev=head, он становится новым началом
            current = current->getPrev();
        }
        head = current;
        head->setPrev(nullptr);
    }
    delete temp;
    count--;
    return value;
}

// Проверка на пустоту
bool Queue::isEmpty() const {return head == nullptr;}

// Количество элементов
int Queue::getCount() const {return count;}

// Очистка очереди
void Queue::clear() {
    while (!isEmpty()) {
        popFront();
    }
}

// Получить элемент по индексу
int Queue::getAt(int index) const {
    if (index < 0 || index >= count) {
        throw std::out_of_range("Индекс вне диапазона.");
    }
    int* values = new int[count];
    Element* temp = tail;
    for (int i = count - 1; i >= 0; i--) {
        values[i] = temp->getData();
        temp = temp->getPrev();
    }
    int result = values[index];
    delete[] values;
    return result;
}

// Установить значение по индексу
void Queue::setAt(int index, int value) {
    if (index < 0 || index >= count) {
        throw std::out_of_range("Индекс вне диапазона.");
    }
    int oldCount = count;
    int* values = new int[oldCount];
    Element* current = tail;
    for (int i = oldCount - 1; i >= 0; i--) {
        values[i] = current->getData();
        current = current->getPrev();
    }
    values[index] = value;
    clear();
    for (int i = 0; i < oldCount; i++) {
        pushBack(values[i]);
    }
    delete[] values;
}

// Перегрузка оператора вывода
std::ostream& operator<<(std::ostream& os, const Queue& q) {
    if (q.isEmpty()) {
        os << "(пусто)";
        return os;
    }
    int oldCount = q.count;
    int* values = new int[oldCount];
    Element* current = q.tail;
    for (int i = oldCount - 1; i >= 0; i--) {
        values[i] = current->getData();
        current = current->getPrev();
    }
    for (int i = 0; i < oldCount; i++) {
        os << values[i];
        if (i < oldCount - 1) os << " ";
    }
    delete[] values;
    return os;
}