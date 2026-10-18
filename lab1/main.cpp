#include <iostream>
#include <locale>
#include <limits>
#include <string>
#include "Keeper.h"
#include "List.h"
#include "Deque.h"
#include "Stack.h"

using namespace std;

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void containerMenu(Queue* container) {
    int choice, value, index;

    do {
        cout << "\n--- Меню контейнера (" << container->getType() << ") ---" << endl;
        cout << "1 - Добавить элемент (в конец)" << endl;
        cout << "2 - Удалить элемент (из начала)" << endl;
        cout << "3 - Вывести контейнер (через print)" << endl;
        cout << "4 - Изменить элемент по индексу" << endl;

        if (container->getType() == "List") {
            cout << "5 - Вставить по индексу" << endl;
            cout << "6 - Удалить по индексу" << endl;
            cout << "7 - Получить элемент по индексу" << endl;
        }
        else if (container->getType() == "Deque") {
            cout << "5 - Добавить элемент (в начало)" << endl;
            cout << "6 - Удалить элемент (с конца)" << endl;
        }
        else if (container->getType() == "Stack") {
            cout << "5 - Посмотреть вершину" << endl;
        }

        cout << "8 - Вывести через operator<< (демонстрация)" << endl;
        cout << "0 - Назад в главное меню" << endl;
        cout << "Выберите действие: ";

        cin >> choice;
        if (cin.fail()) {
            clearInput();
            cout << "Ошибка ввода!" << endl;
            continue;
        }

        switch (choice) {
        case 1:
            cout << "Введите значение: ";
            cin >> value;
            container->add(value);
            break;
        case 2:
            try {
                value = container->remove();
                cout << "Удалён элемент: " << value << endl;
            }
            catch (const exception& e) {
                cout << "Ошибка: " << e.what() << endl;
            }
            break;
        case 3:
            container->print();
            break;
        case 4:
            cout << "Введите индекс: ";
            cin >> index;
            cout << "Введите новое значение: ";
            cin >> value;
            try {
                container->setAt(index, value);
                cout << "Элемент изменён." << endl;
            }
            catch (const exception& e) {
                cout << "Ошибка: " << e.what() << endl;
            }
            break;
        case 5:
            if (container->getType() == "List") {
                cout << "Введите индекс: ";
                cin >> index;
                cout << "Введите значение: ";
                cin >> value;
                try {
                    dynamic_cast<List*>(container)->insertAt(index, value);
                    cout << "Элемент вставлен." << endl;
                }
                catch (const exception& e) {
                    cout << "Ошибка: " << e.what() << endl;
                }
            }
            else if (container->getType() == "Deque") {
                cout << "Введите значение: ";
                cin >> value;
                dynamic_cast<Deque*>(container)->pushFront(value);
                cout << "Элемент добавлен в начало." << endl;
            }
            else if (container->getType() == "Stack") {
                try {
                    value = dynamic_cast<Stack*>(container)->peek();
                    cout << "Вершина стека: " << value << endl;
                }
                catch (const exception& e) {
                    cout << "Ошибка: " << e.what() << endl;
                }
            }
            break;
        case 6:
            if (container->getType() == "List") {
                cout << "Введите индекс: ";
                cin >> index;
                try {
                    dynamic_cast<List*>(container)->removeAt(index);
                    cout << "Элемент удалён." << endl;
                }
                catch (const exception& e) {
                    cout << "Ошибка: " << e.what() << endl;
                }
            }
            else if (container->getType() == "Deque") {
                try {
                    value = dynamic_cast<Deque*>(container)->popBack();
                    cout << "Удалён с конца: " << value << endl;
                }
                catch (const exception& e) {
                    cout << "Ошибка: " << e.what() << endl;
                }
            }
            break;
        case 7:
            if (container->getType() == "List") {
                cout << "Введите индекс: ";
                cin >> index;
                try {
                    value = container->getAt(index);
                    cout << "Элемент [" << index << "] = " << value << endl;
                }
                catch (const exception& e) {
                    cout << "Ошибка: " << e.what() << endl;
                }
            }
            break;
        case 8:
            cout << "Содержимое контейнера: " << *container << endl;
            break;
        case 0:
            break;
        default:
            cout << "Неверный выбор!" << endl;
        }
    } while (choice != 0);
}

int main() {
    setlocale(LC_ALL, "Russian");

    Keeper keeper;
    int choice, type, index;
    string filename;

    do {
        cout << "\n========== ГЛАВНОЕ МЕНЮ ==========" << endl;
        cout << "1 - Добавить контейнер" << endl;
        cout << "2 - Удалить контейнер" << endl;
        cout << "3 - Показать все контейнеры" << endl;
        cout << "4 - Работать с контейнером" << endl;
        cout << "5 - Сохранить в файл" << endl;
        cout << "6 - Загрузить из файла" << endl;
        cout << "0 - Выход" << endl;
        cout << "Выберите действие: ";

        cin >> choice;
        if (cin.fail()) {
            clearInput();
            cout << "Ошибка ввода!" << endl;
            continue;
        }

        switch (choice) {
        case 1:
            cout << "Выберите тип контейнера:" << endl;
            cout << "1 - List" << endl;
            cout << "2 - Deque" << endl;
            cout << "3 - Stack" << endl;
            cout << "Ваш выбор: ";
            cin >> type;
            try {
                keeper.addContainer(type);
                cout << "Контейнер добавлен." << endl;
            }
            catch (const exception& e) {
                cout << "Ошибка: " << e.what() << endl;
            }
            break;
        case 2:
            cout << "Введите индекс контейнера для удаления (0-" << keeper.getCount() - 1 << "): ";
            cin >> index;
            try {
                keeper.removeContainer(index);
                cout << "Контейнер удалён." << endl;
            }
            catch (const exception& e) {
                cout << "Ошибка: " << e.what() << endl;
            }
            break;
        case 3:
            keeper.printAll();
            break;
        case 4:
            cout << "Введите индекс контейнера (0-" << keeper.getCount() - 1 << "): ";
            cin >> index;
            try {
                containerMenu(keeper.getContainer(index));
            }
            catch (const exception& e) {
                cout << "Ошибка: " << e.what() << endl;
            }
            break;
        case 5:
            cout << "Введите имя файла для сохранения: ";
            cin >> filename;
            try {
                keeper.saveToFile(filename);
            }
            catch (const exception& e) {
                cout << "Ошибка: " << e.what() << endl;
            }
            break;
        case 6:
            cout << "Введите имя файла для загрузки: ";
            cin >> filename;
            try {
                keeper.loadFromFile(filename);
            }
            catch (const exception& e) {
                cout << "Ошибка: " << e.what() << endl;
            }
            break;
        case 0:
            cout << "Завершение работы." << endl;
            break;
        default:
            cout << "Неверный выбор!" << endl;
        }
    } while (choice != 0);

    return 0;
} 