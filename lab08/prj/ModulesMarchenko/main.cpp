#include <cmath>
#include <stdexcept>
#include <iostream>
#include <string>
#include <bitset>
#include <algorithm>
#include <fstream>
#include <random>
#include <ctime>
#include <iomanip>
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
    // Отримання 32-бітного рядка з двійковим представленням числа N
    std::string binaryStr = std::bitset<32>(N).to_string();

    // Обрізаємо ведучі нулі, щоб аналізувати лише значущу частину
    size_t pos = binaryStr.find('1');
    if (pos != std::string::npos) {
        binaryStr = binaryStr.substr(pos);
    } else {
        // Якщо число 0, то встановлюємо рядок "0"
        binaryStr = "0";
    }

    // Перевірка молодшого біту (LSB)
    bool leastSignificantBit = (N & 1);
    // Використовуємо тернарний оператор для визначення, який символ рахувати:
    // якщо молодший біт = 0 – рахуємо '0', інакше – '1'.
    char targetChar = (leastSignificantBit == 0) ? '0' : '1';

    // Підрахунок символів targetChar у обрізаному рядку
    int count = std::count(binaryStr.begin(), binaryStr.end(), targetChar);
    return count;
}

bool task10_1(const char* inputFile, const char* outputFile) {
    // Відкриваємо вхідний файл для читання
    std::ifstream inFile(inputFile);
    if (!inFile.is_open()) {
        std::cerr << "Помилка відкриття вхідного файлу: " << inputFile << std::endl;
        return false;
    }

    // Зчитуємо вміст файлу
    std::string fileContent((std::istreambuf_iterator<char>(inFile)),
                          std::istreambuf_iterator<char>());
    inFile.close();

    // Генеруємо випадкове число від 10 до 100
    std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
    std::uniform_int_distribution<int> dist(10, 100);
    int randomNumber = dist(rng);

    // Перевіряємо пунктуаційні помилки
    // Оригінальний текст для порівняння
    const std::string originalText =
        "Як парость виноградної лози, плекайте мову.\n"
        "Пильно й ненастанно політь бур'ян.\n"
        "Чистіша від сльози вона хай буде.\n"
        "Вірно і слухняно нехай вона щоразу служить вам, \n"
        "Хоч і живе своїм живим життям.";

    bool hasPunctuationErrors = (fileContent != originalText);

    // Відкриваємо вихідний файл для запису
    std::ofstream outFile(outputFile);
    if (!outFile.is_open()) {
        std::cerr << "Помилка відкриття вихідного файлу: " << outputFile << std::endl;
        return false;
    }

    // Записуємо інформацію у вихідний файл
    outFile << "Автор: Кирило Марченко" << std::endl;
    outFile << "Організація: Центральноукраїський Національний Технічний Університет" << std::endl;
    outFile << "Місто: Кропивницький" << std::endl;
    outFile << "Країна: Україна" << std::endl;
    outFile << "Рік розробки: 2025" << std::endl << std::endl;

    outFile << "Випадкове число: " << randomNumber << std::endl << std::endl;

    if (hasPunctuationErrors) {
        outFile << "У тексті вірша є пунктуаційні помилки." << std::endl;
    } else {
        outFile << "У тексті вірша немає пунктуаційних помилок." << std::endl;
    }

    outFile.close();
    return true;
}

bool task10_2(const char* inputFile) {
    // Відкриваємо файл для дозапису
    std::ofstream outFile(inputFile, std::ios::app);
    if (!outFile.is_open()) {
        std::cerr << "Помилка відкриття файлу для дозапису: " << inputFile << std::endl;
        return false;
    }

    // Отримуємо поточну дату
    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);

    // Додаємо подвійний перенос рядка і записуємо дату у форматі "ДД.ММ.РРРР"
    outFile << std::endl << std::endl;
    outFile << std::setfill('0')
            << std::setw(2) << localTime->tm_mday << "."
            << std::setw(2) << (localTime->tm_mon + 1) << "."
            << (localTime->tm_year + 1900);

    outFile.close();
    return true;
}

bool task10_3(const char* outputFile, double x, double y, double z, int b) {
    // Обчислюємо результат за допомогою функції з заголовкового файлу
    double result = s_calculation(x, y, z);

    // Перетворюємо число b у двійковий код
    std::string binaryB;
    if (b == 0) {
        binaryB = "0";
    } else {
        while (b > 0) {
            binaryB = (b % 2 == 0 ? "0" : "1") + binaryB;
            b /= 2;
        }
    }

    // Відкриваємо вихідний файл для дозапису
    std::ofstream outFile(outputFile, std::ios::app);
    if (!outFile.is_open()) {
        std::cerr << "Помилка відкриття вихідного файлу для дозапису: " << outputFile << std::endl;
        return false;
    }

    // Записуємо результати у файл
    outFile << std::endl << std::endl;
    outFile << "Результат обчислення функції s_calculation("
            << x << ", " << y << ", " << z << ") = " << result << std::endl;
    outFile << "Число " << b << " у двійковому коді: " << binaryB;

    outFile.close();
    return true;
}
