#include <iostream>
#include "ModulesMarchenko.h"

using namespace std;

int main() {
    char command;       // Символ, що задає вибір функції
    char exitCommand;   // Символ для виходу з програми

    do {
        // Виведення меню вибору
        cout << "========================================" << endl;
        cout << "Введіть команду для виклику функції:" << endl;
        cout << "  v - s_calculation()" << endl;
        cout << "  n - задачa 9.1 (calculateSalary)" << endl;
        cout << "  m - задачa 9.2 (convertSockSize)" << endl;
        cout << "  q - задачa 9.3 (countBinarySymbols)" << endl;
        cout << "========================================" << endl;
        cout << "Ваш вибір: ";
        cin >> command;
        cout << endl;

        switch (command) {
            case 'v': {
                double x, y, z;
                cout << "Введіть x, y, z: ";
                cin >> x >> y >> z;
                cout << "Виклик функції s_calculation():" << endl;
                cout << s_calculation(x, y, z) << endl;
                break;
            }
            case 'n': {
                // Виклик задачі 9.1: розрахунок зарплати, податків та чистої виплати
                cout << "Виклик функції calculateSalary()." << endl;
                cout << "Введіть кількість відпрацьованих днів: ";
                int daysWorked;
                cin >> daysWorked;
                SalaryInfo salary = calculateSalary(daysWorked);
                cout << "Нарахована зарплата: " << salary.grossSalary << " грн" << endl;
                cout << "Податки: " << salary.totalTaxes << " грн" << endl;
                cout << "Чиста зарплата: " << salary.netSalary << " грн" << endl;
                break;
            }
            case 'm': {
                // Виклик задачі 9.2: конвертація розмірів шкарпеток
                cout << "Виклик функції convertSockSize()." << endl;
                cout << "Введіть розмір шкарпеток (український розмір): ";
                int sizeUA;
                cin >> sizeUA;
                SockSize sock = convertSockSize(sizeUA);
                if (!sock.valid) {
                    cout << "Некоректний розмір шкарпеток!" << endl;
                } else {
                    cout << "Розмір для США: " << sock.size_US << endl;
                    cout << "Розмір для ЄС: " << sock.size_EU << endl;
                }
                break;
            }
            case 'q': {
                // Виклик задачі 9.3: підрахунок кількості бінарних символів
                cout << "Виклик функції countBinarySymbols()." << endl;
                cout << "Введіть натуральне число: ";
                unsigned int N;
                cin >> N;
                int count = countBinarySymbols(N);
                // Виводимо інформацію залежно від молодшого біта
                if ((N & 1) == 0)
                    cout << "Молодший біт = 0, кількість двійкових нулів: " << count << endl;
                else
                    cout << "Молодший біт = 1, кількість двійкових одиниць: " << count << endl;
                break;
            }
            default:
                // Якщо введено некоректний символ – повідомлення про помилку з звуковим сигналом
                cout << "Некоректне введення! " << "\a" << endl;
                break;
        }

        // Запит чи бажає користувач вийти
        cout << endl << "Для виходу введіть 'w' або 'W', або будь-який інший символ для продовження: ";
        cin >> exitCommand;
        cout << endl;

    } while (exitCommand != 'w' && exitCommand != 'W');

    cout << "Програма завершена." << endl;
    return 0;
}
