#include "Deque.h"

Deque::Deque() : Queue() {
    std::cout << "+Deque" << std::endl;
}

Deque::Deque(int initialValue) : Queue(initialValue) {
    std::cout << "+Deque(param)" << std::endl;
}

Deque::Deque(const Deque& other) : Queue(other) {
    std::cout << "+Deque(copy)" << std::endl;
}

Deque::~Deque() {
    std::cout << "-Deque" << std::endl;
}

// Добавление в конец (по умолчанию — как у очереди)
void Deque::add(int value) {
    pushBack(value);
}

// Удаление из начала (по умолчанию — как у очереди)
int Deque::remove() {
    return popFront();
}

// Вывод дека на экран
void Deque::print() const {
    if (isEmpty()) {
        std::cout << "Дек пуст." << std::endl;
        return;
    }

    std::cout << "Дек (от первого к последнему): ";
    int* values = new int[count];
    Element* current = getTail();
    for (int i = count - 1; i >= 0; i--) {
        values[i] = current->getData();
        current = current->getPrev();
    }
    for (int i = 0; i < count; i++) {
        std::cout << values[i] << " ";
    }
    delete[] values;
    std::cout << "(всего: " << count << ")" << std::endl;
}

// Сохранение в файл
void Deque::save(std::ofstream& out) const {
    out << getType() << " " << count << std::endl;
    int* values = new int[count];
    Element* current = getTail();
    for (int i = count - 1; i >= 0; i--) {
        values[i] = current->getData();
        current = current->getPrev();
    }
    for (int i = 0; i < count; i++) {
        out << values[i] << " ";
    }
    out << std::endl;
    delete[] values;
}

// Загрузка из файла
void Deque::load(std::ifstream& in) {
    clear();
    int n;
    in >> n;
    for (int i = 0; i < n; i++) {
        int value;
        in >> value;
        pushBack(value);
    }
}

// Получить тип контейнера
std::string Deque::getType() const {
    return "Deque";
}

// Добавление в начало
void Deque::pushFront(int value) {
    // Собираем все значения
    int oldCount = count;
    int* values = new int[oldCount];
    Element* current = getTail();
    for (int i = oldCount - 1; i >= 0; i--) {
        values[i] = current->getData();
        current = current->getPrev();
    }

    // Очищаем дек
    clear();

    // Добавляем новый элемент в начало
    pushBack(value);

    // Добавляем все старые элементы
    for (int i = 0; i < oldCount; i++) {
        pushBack(values[i]);
    }
    delete[] values;
}

// Добавление в конец (уже есть в базовом классе, но для явности)
void Deque::pushBack(int value) {
    Queue::pushBack(value);
}

// Удаление из начала
int Deque::popFront() {
    return Queue::popFront();
}

// Удаление с конца
int Deque::popBack() {
    if (isEmpty()) {
        throw std::runtime_error("Дек пуст! Невозможно удалить с конца.");
    }

    Element* oldTail = getTail();
    int value = oldTail->getData();

    if (getHead() == getTail()) {
        setHead(nullptr);
        setTail(nullptr);
    }
    else {
        setTail(oldTail->getPrev());
    }
    delete oldTail;
    count--;
    return value;
}

// Переопределение оператора вывода
std::ostream& operator<<(std::ostream& os, const Deque& d) {
    os << static_cast<const Queue&>(d);
    return os;
}