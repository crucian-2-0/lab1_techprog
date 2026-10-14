#include "List.h"

List::List() : Queue() {} //вызов конструктора базового класса

List::List(const List& other) : Queue(other) {} //вызов конструктора копирования

List::~List() {} //пуст, потому что вся работа делается в Queue::~Queue()

// Добавление в конец
void List::add(int value) {
    pushBack(value);
}

// Удаление из начала
int List::remove() {
    return popFront();
}

// Вывод списка на экран
void List::print() const {
    if (isEmpty()) {
        std::cout << "Список пуст." << std::endl;
        return;
    }

    std::cout << "Список (от первого к последнему): ";
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
void List::save(std::ofstream& out) const {
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
void List::load(std::ifstream& in) {
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
std::string List::getType() const {
    return "List";
}

void List::insertAt(int index, int value) {
    if (index < 0 || index > count) {
        throw std::out_of_range("Индекс вне диапазона списка.");
    }

    // Сохраняем текущее количество элементов ДО очистки
    int oldCount = count;

    // Собираем все значения
    int* values = new int[oldCount];
    Element* current = getTail();
    for (int i = oldCount - 1; i >= 0; i--) {
        values[i] = current->getData();
        current = current->getPrev();
    }

    // Очищаем список (count станет 0)
    clear();

    // Добавляем элементы обратно, используя oldCount
    for (int i = 0; i < oldCount; i++) {
        if (i == index) {
            pushBack(value);
        }
        pushBack(values[i]);
    }
    // Если вставка в конец
    if (index == oldCount) {
        pushBack(value);
    }
    delete[] values;
}

void List::removeAt(int index) {
    if (index < 0 || index >= count) {
        throw std::out_of_range("Индекс вне диапазона списка.");
    }

    int oldCount = count;

    int* values = new int[oldCount];
    Element* current = getTail();
    for (int i = oldCount - 1; i >= 0; i--) {
        values[i] = current->getData();
        current = current->getPrev();
    }

    clear();

    for (int i = 0; i < oldCount; i++) {
        if (i != index) {
            pushBack(values[i]);
        }
    }
    delete[] values;
}

int List::getAt(int index) const {
    if (index < 0 || index >= count) {
        throw std::out_of_range("Индекс вне диапазона списка.");
    }

    // Здесь count не меняется, но на всякий случай сохраним
    int oldCount = count;

    int* values = new int[oldCount];
    Element* temp = getTail();
    for (int i = oldCount - 1; i >= 0; i--) {
        values[i] = temp->getData();
        temp = temp->getPrev();
    }
    int result = values[index];
    delete[] values;
    return result;
}
