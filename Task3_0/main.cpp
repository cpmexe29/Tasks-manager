#include <iostream>
#include <fstream> // работа с файлами
#include <string> // работа со строками
#include <Windows.h> // функция Sleep(); пауза для комфортабельного использования
#include <ctime> // помогает создать рандомные числа в диапазоне
#include <cstdio> // удаление файла с данными аккаунта Acc.txt

using namespace std;

class Account // класс включает в себя все данные аккаунта, а также функцию SUp - регистрация, SIn - аутентификация
{
private: // приватное тело класса, видно только данному классу
    string cartNum; // номер карты
    string pin_kod; // пин-код

    string SIn_cartNum; // Дополнительная переменная для аутентификации, должна быть равна cartNum (в ином случае номер карты не верен)
    string SIn_pin_kod; // Дополнительная переменная для аутентификации, должна быть равна pin_kod (в ином случае пин-код не верен)

    float balance; // баланс карты (float для безопасности и более удобной записи данных переменной в файл)

    int startB = 2; // вспомогательные переменная для обозначения области рандомных чисел - минимальное значение рандомного числа (в будущем баланса)
    int endB = 10000; // вспомогательна переменная для обозначения области рандомных чисел - максимальное значение рандомног числа (в будущем баланса)

    ofstream OFfile; // объект файла формата ofstream (только ввод данных в файлу), нужен для регистрации (записывает данные переменных в файл)
    ifstream IFfile; // объект файла формата ifstream (только чтение данных в файле), нужен для аутентификации (сравнивать введёные данные пользователя с истинными(те которые указали при регистрации)
public: // публичное тело класса, видно на всей области программы

    ~Account() { // деструктор - выполняется при завершении программы или выхода из класса
        if (OFfile.is_open())
            OFfile.close(); // если файл открыт - программа его закрывает(OFstream)
        cout << "File Acc is closed...." << endl;
        if(IFfile.is_open())
            IFfile.close(); // если файл открыт - программа его закрывает(IFstream)
        cout << "File Acc is closed...." << endl;
        cartNum = "0"; // обнуление данных пользователя
        pin_kod = "0"; // обнуление данных пользователя
        balance = 0; // обнуление данных пользователя
    }

    void SUp() // Sign up, регистрация
    {
        OFfile.open("Acc.txt", ios::out); // открытие файла для записи
        if(OFfile.is_open()) // выполняется если файл открыт
        {
            cout << "Sign Up your Account..." << endl;
            cout << "Input cart number(5 numbers): ";
            cin >> cartNum; // вводим номер карты (регистрируем)
            if(cartNum.size() == 5) // номер карты должен быть по размеру в 5 символов (для удобства)
            {
                OFfile << cartNum << endl; // если размер номера карты = 5 символов(True), записываем номер карты в файл
            }
            else // Размер карты НЕ 5 символов(False)
            {
                cout << "Wrong Cart Num Size..." << endl;
                Sleep(500);
                exit(0);
            }
            cout << "Input pin-kod(4 numbers)"; // вводим пин-код(регистрация)
            cin >> pin_kod;
            if(pin_kod.size() == 4) // пин-код должен быть по размеру 4 символа(True), как в жизни)))
            {
                OFfile << pin_kod << endl; // записываем пин-код в файл
            }
            else // Размер пин-кода НЕ 4 символа(False)
            {
                cout << "Wrong pin-kod size..." << endl;
                Sleep(500);
                exit(0);
            }
            Sleep(10);
            system("cls"); // очищаем консоль
            cout << "Account has been created..." << endl; // аккаунт создан
            balance = rand() % (endB - startB + 1) + startB; // вычисляем баланс аккаунта рандомно в диапазоне от 2 до 10000
            cout << "Your balance = " << balance << endl;
            OFfile << balance << endl; // записываем баланс в файл
            return;
        }
        else  // файл не открыт, регистрация не возможна
        {
            cout << "Error, File not open..." << endl;
            Sleep(500);
            exit(0);
        }

    }

    void SIn() // Sign In, аутентификация
    {
        IFfile.open("Acc.txt", ios::in); // открытие файла для чтения
        if(IFfile.is_open()) // если файл открыт
        {
            cout << "Sign In your Account..." << endl;
            cout << "Input cart number: ";
            cin >> SIn_cartNum; // вводим номер карты
            getline(IFfile, cartNum); // берем номер карты из файла и записываем в переменную cartNum
            IFfile.seekg(0); // перемещаем курсор чтения в файле в начало(в дальнейшем для удобства чтения данных с файла)
            if(SIn_cartNum == cartNum) // если номер карты совпадает с истинным (введёным при регистрации)
            {
                cout << "Input pin - kod: ";
                cin >> SIn_pin_kod; // вводим пин-код
                int target_line_number = 1; // переменная для удобства перемещения курсора чтения в файле - указывает номер нужной для чтения строки
                int line_count = 0; // переменная для удобства перемещения курсора в файле - указывает колличество пройденных строк
                while(getline(IFfile, pin_kod) && line_count < target_line_number) // чтение пин-кода + алгоритм для перемещения курсора чтения в файле на нужную строку для чтения нужной строки
                {
                    line_count++; // пройденные строки ++
                }
                IFfile.seekg(0); // сброс значения расположения курсора чтения в файле
                if(SIn_pin_kod == pin_kod) // если пин-код равен истиному (который указывался при регистрации)(True)
                {
                    system("cls"); // очистка консоли
                    cout << "Successful!!!..." << endl;
                    cout << "Your are logged in Account." << endl; // аккаунт успешно создан
                    cout << "Choose operation: \n" << "1.View balance. \n" << "2.Cash out. \n" << "3.Cash in. \n" << "4.Logout from account. \n" << "5.Delete Accaunt." << endl;
                    // выбор действия: 1.Показать баланс, 2.Снять деньги, 3.Положить деньги, 4.Выход из аккаунта, 5.Удаления аккаунта(удаление файла со всеми файлами)
                    int x1; // вспомогательная переменная для выбора действия в меню
                    cin >> x1; // ввод вспомогательной переменной, выбор действия в меню
                    IFfile.seekg(11); // перемещение курсора чтения в файле на 11 символов
                    IFfile >> balance; // запись данных из файла в переменную баланса
                    if(x1 == 1) // Выбор меню
                    {
                        system("cls"); // очистка консоли
                        cout << "Your Balance = " << balance << endl; // показывает баланс
                        Sleep(1000);
                        return; // возврат в функцию main()
                    }
                    else if(x1 == 2)
                    {
                        system("cls");
                        int CashOut; // переменная обозначает желаемое колличество денег для вывода
                        cout << "Cash Out..." << endl;
                        cout << "Cash = ";
                        cin >> CashOut; // ввод переменной - обозначает желаемое колличество денег для вывода
                        balance -= CashOut; // расчёт нового баланса
                        cout << "Balance = " << balance << endl;
                        Sleep(500);
                        return;
                    }
                    else if(x1 == 3)
                    {
                        system("cls");
                        int Cashin; // обозначает желаемое колличество денег для ввода
                        cout << "Cash In..." << endl;
                        cout << "Cash = ";
                        cin >> Cashin;// ввод переменной - обозначает желаемое колличество денег для ввода
                        balance += Cashin; // расчет нового баланса
                        cout << "Balance = " << balance << endl;
                        Sleep(500);
                        return;
                    }
                    else if(x1 == 4)
                    {
                        cout << "....Goodbye...." << endl; // выход из программы
                        cout << "....Exit......" << endl;
                        Sleep(500);
                        return;
                    }
                    else if(x1 == 5)
                    {
                        cout << "Accaunt DELETED....." << endl;
                        Sleep(50);
                        IFfile.close(); // закрытие файла для последующего удаления
                        remove("Acc.txt");  // удаление файла с данными
                        cout << "Successful." << endl;
                        Sleep(500);
                        return;
                    }
                    else
                    {
                        cout << "Uknown operation....." << endl; // неизвестная операция
                        Sleep(500);
                        exit(0);
                    }
                }
                else
                {
                    cout << "Wrong pin - kod..." << endl;
                    Sleep(500);
                    exit(0);
                }
            }
            else
            {
                cout << "Wrong cartNum..." << endl;
                Sleep(500);
                exit(0);
            }
        }
        else
        {
            cout << "File is not open for read..." << endl;
        }
    }

};

int main()
{
    srand(time(0)); // обновляет время выполнения программы, нужно для рандомных чисел
    int x = 0;
    cout << "_Online Bank_" << endl;
    cout << "Choose: \n" << "1.Sign up. \n" << "2.Sign in." << endl; // меню
    cin >> x;
    if(x == 1)
    {
        Account obj; // объект класса Account
        obj.SUp(); // вызов функции регистрации
    }
    else if(x == 2)
    {
        Account obj; // объект класса Account
        obj.SIn(); // вызов функции для аутентификации
    }
    else
    {
        cout << "Wrong!!!" << endl;
    }
    Sleep(500);
    return 0;
}
