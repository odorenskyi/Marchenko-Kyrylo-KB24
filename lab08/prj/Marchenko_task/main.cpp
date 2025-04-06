#include <iostream>
#include <iomanip>
#include <cmath>
#include "ModulesMarchenko.h"

using namespace std;

// 8.2.1 Функція для виведення інформації про розробника
void printDeveloperInfo() {
    cout << "Марченко Кирило ©" << endl;
}

// 8.2.2 Функція для обчислення логічного виразу
// Передбачається, що символи a, b трактуються за їх ASCII кодами.
int evaluateLogic(char a, char b) {
    int codeA = static_cast<int>(a);
    int codeB = static_cast<int>(b);
    // Обчислення виразу |a - 22| <= b + 5
    if (abs(codeA - 22) <= (codeB + 5))
        return 1;
    else
        return 0;
}

// 8.2.3 Функція для виведення чисел у різних системах числення та обчислення S
void printNumbersAndS(double x, double y, double z) {
    // Вивід чисел у десятковій системі
    cout << "Десяткова система: " << x << " " << y << " " << z << endl;
    // Вивід чисел у шістнадцятковій системі
    cout << "Шістнадцяткова система: "
         << hex << static_cast<int>(x) << " "
         << hex << static_cast<int>(y) << " "
         << hex << static_cast<int>(z) << dec << endl;

    // Обчислення S за допомогою s_calculation()
    double S = s_calculation(x, y, z);
    cout << "S = " << S << endl;
}

int main() {
    double x, y, z;
    char a, b;

    // Послідовне введення даних
    cout << "Введіть x: ";
    cin >> x;
    cout << "Введіть y: ";
    cin >> y;
    cout << "Введіть z: ";
    cin >> z;
    cout << "Введіть символ a: ";
    cin >> a;
    cout << "Введіть символ b: ";
    cin >> b;

    // Виклик підзадач
    printDeveloperInfo();

    int logicResult = evaluateLogic(a, b);
    cout << "Результат логічного виразу (1/0): " << logicResult << endl;

    printNumbersAndS(x, y, z);

    return 0;
}
