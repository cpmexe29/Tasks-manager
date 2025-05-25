#include <iostream>
#include <vector> // добавлет векторы, нужны для сохранения заметок в процессе работы программы
#include <windows.h> // функция Sleep() - пауза для удобства
#include <string> // работа со строками

using namespace std;

struct task // структура каждой заметки, хранит всю информацию о заметке
{
    string name; // имя
    string description; // описание
    bool complete; // статус выполнения True/False
    int id; // порядковый id номер

    friend ostream& operator << (ostream& os, const task& t); // позволяет выводить в консоль сразу всю структуру
};

ostream& operator<<(ostream& os, const task& t) { // шаблон вывода всей структуры (информации о заметке) в консоль
    os << "ID: " << t.id // вывод ID заметки
       << ", Name: " << t.name //вывод имени заметки
       << ", Description: " << t.description // вывод описания заметки
       << ", Status: " << (t.complete ? "Completed" : "Not completed"); // вывод статуса заметки
    return os; // возвращает полноценную структуру в консоль
}

vector<task> listTasks; // вектор (тип структуры <task>), хранит все структуры заметки
static int ident = 1; // порядковый id счётчик

// _Объявление функций (описание ниже main)_ //
void showMenu(); // функция главного меню
void addTask(); // функция добавления заметки
void Edit(); // функция редактирования заметки
void Delete(); // функция удаления заметки
void List(); // функция выводит список всех заметок
void Exit(); // функция выхода из программы

int main() // _main_
{
    cout << "Hello in task manager!!!" << endl;
    showMenu(); // показывает главное меню при запуске программы
    return 0;
}

void addTask() // функция добавления заметки
{
    task newTask; // объект типа структуры <task>
    cout << "\nAdd task." << endl;
    cout << "Input task name: ";
    cin >> newTask.name; // ввод имени заметки
    cout << "Input task description: ";
    cin >> newTask.description; // ввод описания заметки
    newTask.complete = false; // статус выполнения заметки (по умолчанию False)
    newTask.id = ident++; // обновляет id счетчик ПОСЛЕ добавления задачи
    listTasks.push_back(newTask); // добавление объекта в вектор
    cout << "Task added successfully!" << endl;
    Sleep(1000); // пауза...
}

void showMenu() // функция главного меню
{
    int choice = 0; // вспомогательная переменная (выбор действия в меню)
    while (choice != 5) { // вызывает меню каждый раз после завершения действия (если действие не выход из программы) позволяет избежать бесконечную рекурсию и переполнение стека, в следствие краш программы
        cout << "Choose action:" << endl
             << "1. Add task." << endl
             << "2. Edit task." << endl
             << "3. Delete task." << endl
             << "4. Tasks list." << endl
             << "5. Exit." << endl
             << "Action: ";

        cin >> choice; // ввод выбора...

        switch (choice) { // выбирает действие по введённой переменной
        case 1: addTask(); break;
        case 2: Edit(); break;
        case 3: Delete(); break;
        case 4: List(); break;
        case 5: Exit(); break;
        default:
            cout << "Invalid choice! Try again.\n"; // не правильный выбор (chose > 5)
            Sleep(1000);
        }
    }
}

void List() // функция выводит список всех заметок
{
    cout << "\nTask List:\n";
    for (const auto& n : listTasks) { // перебирает массив с заметками
        cout << n << endl;
    }
    cout << endl;
    Sleep(500);
}

void Edit() // функция редактирования заметки
{
    List(); // выводит список всех заметок для выбора нужной
    int id_x; // вспомогательная переменная, обозначает выбор заметки по id
    cout << "Input task ID to edit: ";
    cin >> id_x; // ввод вспомогательной переменной (ввод id заметки для редактирования)

    auto it = find_if(listTasks.begin(), listTasks.end(),[id_x](const task& t) { return t.id == id_x; }); // переменная (итератор) равна поиску нужной заметки в масиве по id

    if (it == listTasks.end()) { // если заметки с введённым id нет, выводит ошибку
        cout << "Error: Task with ID " << id_x << " not found!\n";
        Sleep(1000);
        return;
    }

    cout << "What do you want to change?\n" // меню редактирования заметки
         << "1. Name\n2. Description\n3. Status\nChoice: ";

    int edit_choice; // вспомогательная переменная обозначает выбор действия в меню редактирования
    cin >> edit_choice; // ввод действия по редактированию

    switch (edit_choice) {
    case 1:
        cout << "Enter new name: ";
        cin >> it->name; // ввод нового имени заметки и запись его в объект структуры
        break;
    case 2:
        cout << "Enter new description: ";
        cin >> it->description; // ввод нового описания заметки и запись его в объект структуры
        break;
    case 3:
        cout << "Mark as completed? (1 - Yes, 0 - No): ";
        cin >> it->complete; //ввод нового статуса выполнения заметки и запись его в объект структуры
        break;
    default:
        cout << "Invalid choice!\n"; // выбрано не правильное действие в меню редактирования
        Sleep(1000);
    }
}

void Delete() // функция удаления заметки
{
    List(); // список всех заметок
    int id_x; // вспомогательная переменная обозначает id заметкидля удаления
    cout << "Input task ID to delete: ";
    cin >> id_x; // ввод вспомогательное переменной для удаления

    auto it = find_if(listTasks.begin(), listTasks.end(),[id_x](const task& t) { return t.id == id_x; }); // переменная (итератор) равна поиску нужной заметки в масиве по id

    if (it != listTasks.end()) {
        listTasks.erase(it); // удаление заметки в масиве по id
        cout << "Task deleted successfully!\n";
    } else {
        cout << "Error: Task not found!\n"; // не найдена заметка по id
    }
    Sleep(1000);
}

void Exit() // функция выхода из программы, не вызывает меню выбора дейсвия в следствии программа возвращается в main и завершает выполнение успешно (код 0)
{
    cout << "Goodbye..." << endl;
    Sleep(1000);
}
