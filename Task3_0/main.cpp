#include <iostream>
#include <vector>
#include <windows.h>
#include <string>
#include <algorithm>

using namespace std;

struct task
{
    string name;
    string description;
    bool complete;
    int id;

    friend ostream& operator << (ostream& os, const task& t);
};

ostream& operator<<(ostream& os, const task& t) {
    os << "ID: " << t.id
       << ", Name: " << t.name
       << ", Description: " << t.description
       << ", Status: " << (t.complete ? "Completed" : "Not completed");
    return os;
}

vector<task> listTasks;
static int ident = 1;

void showMenu();
void addTask();
void Edit();
void Delete();
void Info();
void Exit();

int main()
{
    cout << "Hello in task manager!!!" << endl;
    showMenu();
    return 0;
}

void addTask()
{
    task newTask;
    cout << "\nAdd task." << endl;
    cout << "Input task name: ";
    cin >> newTask.name;
    cout << "Input task description: ";
    cin >> newTask.description;
    newTask.complete = false;
    newTask.id = ident++;
    listTasks.push_back(newTask);
    cout << "Task added successfully!" << endl;
    Sleep(1000);
}

void showMenu()
{
    int choice = -1;
    while (choice != 5) {
        //system("cls");
        cout << "Choose action:" << endl
             << "1. Add task." << endl
             << "2. Edit task." << endl
             << "3. Delete task." << endl
             << "4. Tasks list." << endl
             << "5. Exit." << endl
             << "Action: ";

        cin >> choice;

        switch (choice) {
        case 1: addTask(); break;
        case 2: Edit(); break;
        case 3: Delete(); break;
        case 4: Info(); break;
        case 5: Exit(); break;
        default:
            cout << "Invalid choice! Try again.\n";
            Sleep(1000);
        }
    }
}

void Info()
{
    cout << "\nTask List:\n";
    for (const auto& n : listTasks) {
        cout << n << endl;
    }
    cout << endl;
    Sleep(500   );
}

void Edit()
{
    Info();
    int id_x;
    cout << "Input task ID to edit: ";
    cin >> id_x;

    auto it = find_if(listTasks.begin(), listTasks.end(),[id_x](const task& t) { return t.id == id_x; });

    if (it == listTasks.end()) {
        cout << "Error: Task with ID " << id_x << " not found!\n";
        Sleep(1000);
        return;
    }

    cout << "What do you want to change?\n"
         << "1. Name\n2. Description\n3. Status\nChoice: ";

    int edit_choice;
    cin >> edit_choice;

    switch (edit_choice) {
    case 1:
        cout << "Enter new name: ";
        cin >> it->name;
        break;
    case 2:
        cout << "Enter new description: ";
        cin >> it->description;
        break;
    case 3:
        cout << "Mark as completed? (1 - Yes, 0 - No): ";
        cin >> it->complete;
        break;
    default:
        cout << "Invalid choice!\n";
        Sleep(1000);
    }
}

void Delete()
{
    Info();
    int id_x;
    cout << "Input task ID to delete: ";
    cin >> id_x;

    auto it = find_if(listTasks.begin(), listTasks.end(),[id_x](const task& t) { return t.id == id_x; });

    if (it != listTasks.end()) {
        listTasks.erase(it);
        cout << "Task deleted successfully!\n";
    } else {
        cout << "Error: Task not found!\n";
    }
    Sleep(1000);
}

void Exit()
{
    cout << "Goodbye..." << endl;
    Sleep(1000);
}
