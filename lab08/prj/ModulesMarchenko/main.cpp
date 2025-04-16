#include <cmath>
#include <stdexcept>
#include <iostream>
#include <string>
#include <bitset>
#include <algorithm>
#include "ModulesMarchenko.h"

const double EPSILON = 1e-9;

double s_calculation(double x, double y, double z) {
    // Перевірка для виразу |y-z| (щоб уникнути ділення на 0)
    if (std::fabs(y - z) < EPSILON) {
        return NAN;
    }

    // Обчислення першого терму: (x/|y-z|)^3
    double term1 = std::pow(x / std::fabs(y - z), 3);

    // Перевірка для виразу під квадратним коренем у знаменнику другого терму:
    // √(|z+x| * y) - перевіряємо, що y > 0 та |z+x| > 0
    if (y <= 0 || std::fabs(z + x) < EPSILON) {
        return NAN;
    }
    double sqrtDenom = std::sqrt(std::fabs(z + x) * y);
    double term2 = (x * x + z) / sqrtDenom;

    // Перевірка знаменника для третього терму: 2*y + π
    double denominator = 2 * y + M_PI;
    if (std::fabs(denominator) < EPSILON) {
        return NAN;
    }
    double term3 = std::cos(x * z * z) / denominator;

    // Обчислення виразу під квадратним коренем
    double innerExpression = term1 + term2 - term3;
    if (innerExpression < 0) {
        return NAN;
    }

    // Обчислення кінцевого значення S
    double S = 1 + std::sqrt(innerExpression);
    return S;
}

// ================================
// Задача 9.1: Обчислення зарплати, податків та суми до виплати
// ================================

// Функція calculateSalary розраховує нараховану суму зарплати, податкові відрахування та чисту суму до виплати
SalaryInfo calculateSalary(int daysWorked) {
    const int HOURS_PER_DAY = 8;
    const int RATE_PER_HOUR = 450;
    // Обчислення загальної нарахованої зарплати
    double grossSalary = daysWorked * HOURS_PER_DAY * RATE_PER_HOUR;

    // Розрахунок відрахувань:
    // 15% податку на прибуток фізособи, 2% до Пенсійного фонду, 0,6% до Фонду соц. страхування безробіття, 1% - страхування при втраті працездатності
    double taxIncome = grossSalary * 0.15;
    double taxPension = grossSalary * 0.02;
    double taxUnemployment = grossSalary * 0.006;
    double taxTemporary = grossSalary * 0.01;

    double totalTaxes = taxIncome + taxPension + taxUnemployment + taxTemporary;
    double netSalary = grossSalary - totalTaxes;

    SalaryInfo info = { grossSalary, totalTaxes, netSalary };
    return info;
}

// ================================
// Задача 9.2: Конвертація розміру чоловічих шкарпеток (Україна → США та ЄС)
// ================================

// Функція convertSockSize приймає розмір в українській системі і повертає відповідники для США та ЄС
SockSize convertSockSize(int size_UA) {
    SockSize result;
    result.valid = true;

    if (size_UA == 23) {
        result.size_US = 8;
        result.size_EU = "37/38";
    }
    else if (size_UA == 25) {
        result.size_US = 9;
        result.size_EU = "39/40";
    }
    else if (size_UA == 27) {
        result.size_US = 10;
        result.size_EU = "41/42";
    }
    else if (size_UA == 29) {
        result.size_US = 11;
        result.size_EU = "43/44";
    }
    else if (size_UA == 31) {
        result.size_US = 12;
        result.size_EU = "45/46";
    }
    else {
        // Якщо розмір не належить до визначеної таблиці - прапорець valid встановлюємо в false
        result.valid = false;
        result.size_US = -1;
        result.size_EU = "";
    }

    return result;
}

// ================================
// Задача 9.3: Підрахунок кількості бінарних символів залежно від молодшого біта
// ================================

// Функція countBinarySymbols приймає натуральне число N та повертає:
// - Кількість двійкових "0", якщо молодший біт D0 рівний 0,
// - Кількість двійкових "1", якщо D0 рівний 1.
// Підрахунок здійснюється за допомогою тернарного оператора.
int countBinarySymbols(unsigned int N) {
    // Отримання рядка, що містить двійкове представлення числа N
    // За умовчанням використовуємо 32-бітне представлення
    std::string binaryStr = std::bitset<32>(N).to_string();

    // Для аналізу можна видалити ведучі нулі, якщо потрібно:
    // size_t pos = binaryStr.find('1');
    // if (pos != std::string::npos) binaryStr = binaryStr.substr(pos);
    // else binaryStr = "0";

    // Перевірка молодшого біту:
    bool leastSignificantBit = (N & 1);
    // Використання тернарного оператора для вибору символу, який потрібно рахувати:
    char targetChar = (leastSignificantBit == 0) ? '0' : '1';

    // Підрахунок за допомогою std::count
    int count = std::count(binaryStr.begin(), binaryStr.end(), targetChar);
    return count;
}
