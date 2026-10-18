#include "Stack.h"

Stack::Stack() : Queue() {
    std::cout << "+Stack" << std::endl;
}

Stack::Stack(int initialValue) : Queue(initialValue) {
    std::cout << "+Stack(param)" << std::endl;
}

Stack::Stack(const Stack& other) : Queue(other) {
    std::cout << "+Stack(copy)" << std::endl;
}
Stack::~Stack() {
    std::cout << "-Stack" << std::endl;
}

// Добавление на вершину стека (в конец очереди)
void Stack::add(int value) {
    pushBack(value);
}

// Удаление с вершины стека (с конца очереди)
int Stack::remove() {
    if (isEmpty()) {
        throw std::runtime_error("Стек пуст! Невозможно извлечь элемент.");
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

// Вывод стека на экран (вершина — первый)
void Stack::print() const {
    if (isEmpty()) {
        std::cout << "Стек пуст." << std::endl;
        return;
    }

    std::cout << "Стек (вершина -> основание): ";
    int* values = new int[count];
    Element* current = getTail();
    for (int i = count - 1; i >= 0; i--) {
        values[i] = current->getData();
        current = current->getPrev();
    }
    // Выводим в обратном порядке: сначала вершина (последний добавленный)
    for (int i = count - 1; i >= 0; i--) {
        std::cout << values[i] << " ";
    }
    delete[] values;
    std::cout << "(всего: " << count << ")" << std::endl;
}

// Сохранение в файл
void Stack::save(std::ofstream& out) const {
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
void Stack::load(std::ifstream& in) {
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
std::string Stack::getType() const {
    return "Stack";
}

// То же, что add
void Stack::push(int value) {
    add(value);
}

// То же, что remove
int Stack::pop() {
    return remove();
}

// Посмотреть вершину без удаления
int Stack::peek() const {
    if (isEmpty()) {
        throw std::runtime_error("Стек пуст! Невозможно посмотреть вершину.");
    }
    return getTail()->getData();
}

// Переопределение оператора вывода
std::ostream& operator<<(std::ostream& os, const Stack& s) {
    os << static_cast<const Queue&>(s);
    return os;
}