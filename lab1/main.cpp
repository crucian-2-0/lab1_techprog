#include <iostream>
#include <locale>
#include <limits>
#include "List.h"

using namespace std;

// ОЧищение потока ввода после ошибки
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    setlocale(LC_ALL, "Russian");

    List list;
    int choice, value, index;

    do {
        cout << "\n========== МЕНЮ (тест List) ==========" << endl;
        cout << "1 - Добавить элемент в конец" << endl;
        cout << "2 - Удалить элемент из начала" << endl;
        cout << "3 - Вывести список" << endl;
        cout << "4 - Вставить по индексу" << endl;
        cout << "5 - Удалить по индексу" << endl;
        cout << "6 - Получить элемент по индексу" << endl;
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
            cout << "Введите значение: ";
            cin >> value;
            list.add(value);
            break;
        case 2:
            try {
                value = list.remove();
                cout << "Удалён элемент: " << value << endl;
            }
            //если что то пошло не так (очередь пуста), то генерируется исключение (в popFront), здесь мы его принимаем и выводим
            catch (const exception& e) { 
                cout << "Ошибка: " << e.what() << endl;
            }
            break;
        case 3:
            list.print();
            break;
        case 4:
            cout << "Введите индекс: ";
            cin >> index;
            cout << "Введите значение: ";
            cin >> value;
            try {
                list.insertAt(index, value);
                cout << "Элемент вставлен." << endl;
            }
            //если что то пошло не так (индекс вне диапазона), то генерируется исключение (в popFront), здесь мы его принимаем и выводим
            catch (const exception& e) {
                cout << "Ошибка: " << e.what() << endl;
            }
            break;
        case 5:
            cout << "Введите индекс: ";
            cin >> index;
            try {
                list.removeAt(index);
                cout << "Элемент удалён." << endl;
            }
            //если что то пошло не так (индекс вне диапазона), то генерируется исключение (в popFront), здесь мы его принимаем и выводим
            catch (const exception& e) {
                cout << "Ошибка: " << e.what() << endl;
            }
            break;
        case 6:
            cout << "Введите индекс: ";
            cin >> index;
            try {
                value = list.getAt(index);
                cout << "Элемент [" << index << "] = " << value << endl;
            }
            //если что то пошло не так (индекс вне диапазона), то генерируется исключение (в popFront), здесь мы его принимаем и выводим
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