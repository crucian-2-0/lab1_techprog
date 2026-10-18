#include "Keeper.h"
#include "List.h"
#include "Deque.h"
#include "Stack.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

Keeper::Keeper() : containers(nullptr), size(0), capacity(0) {
    std::cout << "+Keeper" << std::endl;
}

//НЕ используется (нужно для вып. требований)
Keeper::Keeper(int initialCapacity) : size(0), capacity(initialCapacity) {
    std::cout << "+Keeper(param)" << std::endl;
    containers = new Queue * [capacity];
}

//НЕ используется (нужно для вып. требований)
// Глубокое копирование
Keeper::Keeper(const Keeper& other) : size(other.size), capacity(other.capacity) {
    std::cout << "+Keeper(copy)" << std::endl;
    containers = new Queue * [capacity];
    for (int i = 0; i < size && i < capacity; i++) {
        std::string type = other.containers[i]->getType();
        if (type == "List") {
            containers[i] = new List(*dynamic_cast<List*>(other.containers[i]));
        }
        else if (type == "Deque") {
            containers[i] = new Deque(*dynamic_cast<Deque*>(other.containers[i]));
        }
        else if (type == "Stack") {
            containers[i] = new Stack(*dynamic_cast<Stack*>(other.containers[i]));
        }
        else {
            containers[i] = nullptr; // на всякий случай
        }
    }
}

Keeper::~Keeper() {
    std::cout << "-Keeper" << std::endl;
    for (int i = 0; i < size; i++) {
        delete containers[i];
    }
    delete[] containers;
}

// Расширение массива
void Keeper::resize() {
    int newCapacity = (capacity == 0) ? 2 : capacity * 2;
    Queue** newContainers = new Queue * [newCapacity];

    for (int i = 0; i < size && i < newCapacity; i++) {
        newContainers[i] = containers[i];
    }

    delete[] containers;
    containers = newContainers;
    capacity = newCapacity;
}

void Keeper::addContainer(int type) {
    Queue* newContainer = nullptr;

    switch (type) {
    case 1: newContainer = new List(); break;
    case 2: newContainer = new Deque(); break;
    case 3: newContainer = new Stack(); break;
    default: throw std::invalid_argument("Неверный тип контейнера!");
    }

    if (size >= capacity) {
        resize();
    }
    containers[size++] = newContainer;
}

void Keeper::removeContainer(int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Индекс вне диапазона хранилища.");
    }
    delete containers[index];
    for (int i = index; i < size - 1; i++) {
        containers[i] = containers[i + 1];
    }
    size--;
}

void Keeper::printAll() const {
    if (size == 0) {
        std::cout << "Хранилище пусто." << std::endl;
        return;
    }

    for (int i = 0; i < size; i++) {
        std::cout << "--- Контейнер #" << i << " (" << containers[i]->getType() << ") ---" << std::endl;
        containers[i]->print();
    }
}

int Keeper::getCount() const {return size;}

Queue* Keeper::getContainer(int index) const {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Индекс вне диапазона хранилища.");
    }
    return containers[index];
}

void Keeper::saveToFile(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out.is_open()) {
        throw std::runtime_error("Ошибка открытия файла для записи!");
    }

    out << size << std::endl;
    for (int i = 0; i < size; i++) {
        containers[i]->save(out);
    }

    out.close();
    std::cout << "Данные сохранены в файл: " << filename << std::endl;
}

void Keeper::loadFromFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in.is_open()) {
        throw std::runtime_error("Ошибка открытия файла для чтения!");
    }

    for (int i = 0; i < size; i++) {
        delete containers[i];
    }
    size = 0;

    int n;
    in >> n;

    for (int i = 0; i < n; i++) {
        std::string type;
        in >> type;

        Queue* newContainer = nullptr;
        if (type == "List") newContainer = new List();
        else if (type == "Deque") newContainer = new Deque();
        else if (type == "Stack") newContainer = new Stack();
        else throw std::runtime_error("Неизвестный тип контейнера в файле!");

        newContainer->load(in);

        if (size >= capacity) {resize();}
        containers[size++] = newContainer;
    }

    in.close();
    std::cout << "Данные загружены из файла: " << filename << std::endl;
}