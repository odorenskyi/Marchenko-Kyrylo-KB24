#include <iostream>
#include <iomanip>
#include <cmath>
#include "ModulesMarchenko.h" // Заголовковий файл бібліотеки з реалізаціями функцій задач 9.1, 9.2 та 9.3

// Функція для порівняння чисел з плаваючою комою з точністю ε
bool areEqual(double a, double b, double epsilon = 0.001) {
    return std::fabs(a - b) < epsilon;
}

// Функція тестування задачі 9.1
void testTask9_1() {
    std::cout << "=== Тестування задачі 9.1: Зарплата та податки ===" << std::endl;

    bool allPassed = true;

    // Тест-кейс 1: Кількість днів = 0
    {
        int daysWorked = 0;
        SalaryInfo result = calculateSalary(daysWorked);
        double expGross = 0;
        double expTaxes = 0;
        double expNet = 0;
        bool passed = areEqual(result.grossSalary, expGross) &&
                      areEqual(result.totalTaxes, expTaxes) &&
                      areEqual(result.netSalary, expNet);
        std::cout << "[TC1] Вхід: daysWorked = " << daysWorked << std::endl;
        std::cout << "      Отримано: grossSalary = " << result.grossSalary
                  << ", totalTaxes = " << result.totalTaxes
                  << ", netSalary = " << result.netSalary << std::endl;
        std::cout << "      Очікувано: " << expGross << ", " << expTaxes << ", " << expNet
                  << " -> " << (passed ? "PASSED" : "FAILED") << std::endl << std::endl;
        allPassed = allPassed && passed;
    }

    // Тест-кейс 2: Кількість днів = 5
    {
        int daysWorked = 5;
        SalaryInfo result = calculateSalary(daysWorked);
        double expGross = 5 * 8 * 450;          // 18000 грн
        double expTaxes = expGross * 0.15 +        // 15%
                          expGross * 0.02 +        // 2%
                          expGross * 0.006 +       // 0.6%
                          expGross * 0.01;         // 1%
        double expNet = expGross - expTaxes;       // 18000 - 3348 = 14652 грн (заокруглено)
        bool passed = areEqual(result.grossSalary, expGross) &&
                      areEqual(result.totalTaxes, expTaxes) &&
                      areEqual(result.netSalary, expNet);
        std::cout << "[TC2] Вхід: daysWorked = " << daysWorked << std::endl;
        std::cout << "      Отримано: grossSalary = " << result.grossSalary
                  << ", totalTaxes = " << result.totalTaxes
                  << ", netSalary = " << result.netSalary << std::endl;
        std::cout << "      Очікувано: " << expGross << ", " << expTaxes << ", " << expNet
                  << " -> " << (passed ? "PASSED" : "FAILED") << std::endl << std::endl;
        allPassed = allPassed && passed;
    }

    // Тест-кейс 3: Кількість днів = 10
    {
        int daysWorked = 10;
        SalaryInfo result = calculateSalary(daysWorked);
        double expGross = 10 * 8 * 450;         // 36000 грн
        double expTaxes = expGross * 0.15 +       // 15%
                          expGross * 0.02 +       // 2%
                          expGross * 0.006 +      // 0.6%
                          expGross * 0.01;        // 1%
        double expNet = expGross - expTaxes;      // 36000 - 6696 = 29304 грн (заокруглено)
        bool passed = areEqual(result.grossSalary, expGross) &&
                      areEqual(result.totalTaxes, expTaxes) &&
                      areEqual(result.netSalary, expNet);
        std::cout << "[TC3] Вхід: daysWorked = " << daysWorked << std::endl;
        std::cout << "      Отримано: grossSalary = " << result.grossSalary
                  << ", totalTaxes = " << result.totalTaxes
                  << ", netSalary = " << result.netSalary << std::endl;
        std::cout << "      Очікувано: " << expGross << ", " << expTaxes << ", " << expNet
                  << " -> " << (passed ? "PASSED" : "FAILED") << std::endl << std::endl;
        allPassed = allPassed && passed;
    }

    std::cout << "Результат тестування задачі 9.1: " << (allPassed ? "ВСІ ТЕСТИ PASSED" : "Є FAILED тести") << std::endl << std::endl;
}

// Функція тестування задачі 9.2
void testTask9_2() {
    std::cout << "=== Тестування задачі 9.2: Конвертація розміру шкарпеток ===" << std::endl;

    bool allPassed = true;

    // Тест-кейс 1: UA розмір = 23, очікувано: США 8, ЄС "37/38"
    {
        int uaSize = 23;
        SockSize result = convertSockSize(uaSize);
        bool passed = result.valid && (result.size_US == 8) && (result.size_EU == "37/38");
        std::cout << "[TC1] Вхід: uaSize = " << uaSize << std::endl;
        std::cout << "      Отримано: US = " << result.size_US
                  << ", EU = " << result.size_EU << std::endl;
        std::cout << "      Очікувано: US = 8, EU = 37/38 -> " << (passed ? "PASSED" : "FAILED") << std::endl << std::endl;
        allPassed = allPassed && passed;
    }

    // Тест-кейс 2: UA розмір = 27, очікувано: США 10, ЄС "41/42"
    {
        int uaSize = 27;
        SockSize result = convertSockSize(uaSize);
        bool passed = result.valid && (result.size_US == 10) && (result.size_EU == "41/42");
        std::cout << "[TC2] Вхід: uaSize = " << uaSize << std::endl;
        std::cout << "      Отримано: US = " << result.size_US
                  << ", EU = " << result.size_EU << std::endl;
        std::cout << "      Очікувано: US = 10, EU = 41/42 -> " << (passed ? "PASSED" : "FAILED") << std::endl << std::endl;
        allPassed = allPassed && passed;
    }

    // Тест-кейс 3: UA розмір = 31, очікувано: США 12, ЄС "45/46"
    {
        int uaSize = 31;
        SockSize result = convertSockSize(uaSize);
        bool passed = result.valid && (result.size_US == 12) && (result.size_EU == "45/46");
        std::cout << "[TC3] Вхід: uaSize = " << uaSize << std::endl;
        std::cout << "      Отримано: US = " << result.size_US
                  << ", EU = " << result.size_EU << std::endl;
        std::cout << "      Очікувано: US = 12, EU = 45/46 -> " << (passed ? "PASSED" : "FAILED") << std::endl << std::endl;
        allPassed = allPassed && passed;
    }

    std::cout << "Результат тестування задачі 9.2: " << (allPassed ? "ВСІ ТЕСТИ PASSED" : "Є FAILED тести") << std::endl << std::endl;
}

// Функція тестування задачі 9.3
void testTask9_3() {
    std::cout << "=== Тестування задачі 9.3: Підрахунок бінарних символів ===" << std::endl;

    bool allPassed = true;

    // Тест-кейс 1: N = 0, двійкове представлення "0" → очікується 1 нуль
    {
        unsigned int N = 0;
        int result = countBinarySymbols(N);
        int exp = 1; // Для "0" маємо один символ '0'
        bool passed = (result == exp);
        std::cout << "[TC1] Вхід: N = " << N << std::endl;
        std::cout << "      Отримано: " << result << std::endl;
        std::cout << "      Очікувано: " << exp << " -> " << (passed ? "PASSED" : "FAILED") << std::endl << std::endl;
        allPassed = allPassed && passed;
    }

    // Тест-кейс 2: N = 6, двійкове представлення "110"; молодший біт = 0, підрахунок нулів має дати 1
    {
        unsigned int N = 6; // binary "110"
        int result = countBinarySymbols(N);
        int exp = 1; // лише одна '0'
        bool passed = (result == exp);
        std::cout << "[TC2] Вхід: N = " << N << std::endl;
        std::cout << "      Отримано: " << result << std::endl;
        std::cout << "      Очікувано: " << exp << " -> " << (passed ? "PASSED" : "FAILED") << std::endl << std::endl;
        allPassed = allPassed && passed;
    }

    // Тест-кейс 3: N = 7, двійкове представлення "111"; молодший біт = 1, підрахунок одиниць має дати 3
    {
        unsigned int N = 7; // binary "111"
        int result = countBinarySymbols(N);
        int exp = 3; // усі 3 біти - '1'
        bool passed = (result == exp);
        std::cout << "[TC3] Вхід: N = " << N << std::endl;
        std::cout << "      Отримано: " << result << std::endl;
        std::cout << "      Очікувано: " << exp << " -> " << (passed ? "PASSED" : "FAILED") << std::endl << std::endl;
        allPassed = allPassed && passed;
    }

    std::cout << "Результат тестування задачі 9.3: " << (allPassed ? "ВСІ ТЕСТИ PASSED" : "Є FAILED тести") << std::endl << std::endl;
}

int main() {
    std::cout << "=== Тестовий драйвер для модульного тестування задач 9.1, 9.2 та 9.3 ===" << std::endl << std::endl;
    // Тестування кожного модуля з використанням розроблених наборів контрольних прикладів
    testTask9_1();
    testTask9_2();
    testTask9_3();

    std::cout << "=== Завершення тестування ===" << std::endl;
    return 0;
}
