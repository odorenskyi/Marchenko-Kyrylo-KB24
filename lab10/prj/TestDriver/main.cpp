#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <windows.h>
#include "ModulesMarchenko.h"

// Функція для створення файлу з текстом і повернення його імені
std::string createTestFile(const std::string& filename, const std::string& content) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не вдалося створити тестовий файл: " << filename << std::endl;
        return "";
    }
    file << content;
    file.close();
    return filename;
}

// Функція для зчитування вмісту файлу
std::string readFileContent(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не вдалося відкрити файл для читання: " << filename << std::endl;
        return "";
    }
    std::string content((std::istreambuf_iterator<char>(file)),
                      std::istreambuf_iterator<char>());
    file.close();
    return content;
}

// Функція для запису результатів тестування у лог-файл
void logTestResult(const std::string& testName, bool passed, const std::string& details = "") {
    static std::ofstream logFile("test_results.log", std::ios::app);
    if (!logFile.is_open()) {
        logFile.open("test_results.log");
    }

    std::time_t now = std::time(nullptr);
    logFile << "--- Тест: " << testName << " ---" << std::endl;
    logFile << "Час: " << std::ctime(&now);
    logFile << "Результат: " << (passed ? "PASSED" : "FAILED") << std::endl;
    if (!details.empty()) {
        logFile << "Деталі: " << details << std::endl;
    }
    logFile << "----------------------------" << std::endl << std::endl;

    // Також виводимо на консоль
    std::cout << "Тест: " << testName << " - " << (passed ? "PASSED" : "FAILED") << std::endl;
    if (!details.empty()) {
        std::cout << "Деталі: " << details << std::endl;
    }
}

// Тестування функції task10_1
void testTask10_1() {
    std::cout << "\n=== Тестування функції task10_1 ===\n";

    // Тест 1: Правильний текст
    std::string correctText =
        "Як парость виноградної лози, плекайте мову.\n"
        "Пильно й ненастанно політь бур'ян.\n"
        "Чистіша від сльози вона хай буде.\n"
        "Вірно і слухняно нехай вона щоразу служить вам, \n"
        "Хоч і живе своїм живим життям.";

    std::string inFile1 = createTestFile("test10_1_input1.txt", correctText);
    std::string outFile1 = "test10_1_output1.txt";

    bool result1 = task10_1(inFile1.c_str(), outFile1.c_str());
    std::string outContent1 = readFileContent(outFile1);

    bool test1Passed = result1 && (outContent1.find("У тексті вірша немає пунктуаційних помилок") != std::string::npos);
    logTestResult("task10_1 - коректний текст", test1Passed);

    // Тест 2: Текст з помилками
    std::string incorrectText =
        "Як парость виноградної лози плекайте мову\n"
        "Пильно й ненастанно політь бур'ян\n"
        "Чистіша від сльози вона хай буде\n"
        "Вірно і слухняно нехай вона щоразу служить вам\n"
        "Хоч і живе своїм живим життям";

    std::string inFile2 = createTestFile("test10_1_input2.txt", incorrectText);
    std::string outFile2 = "test10_1_output2.txt";

    bool result2 = task10_1(inFile2.c_str(), outFile2.c_str());
    std::string outContent2 = readFileContent(outFile2);

    bool test2Passed = result2 && (outContent2.find("У тексті вірша є пунктуаційні помилки") != std::string::npos);
    logTestResult("task10_1 - текст з помилками", test2Passed);

    // Тест 3: Неіснуючий файл
    bool result3 = task10_1("nonexistent_file.txt", "test10_1_output3.txt");
    bool test3Passed = !result3;
    logTestResult("task10_1 - неіснуючий файл", test3Passed);
}

// Тестування функції task10_2
void testTask10_2() {
    std::cout << "\n=== Тестування функції task10_2 ===\n";

    // Тест 1: Дозапис дати до існуючого файлу
    std::string text = "Тестовий текст для дозапису дати.\n";
    std::string inFile1 = createTestFile("test10_2_input1.txt", text);

    bool result1 = task10_2(inFile1.c_str());
    std::string outContent1 = readFileContent(inFile1);

    // Перевіряємо, чи є дата у форматі ДД.ММ.РРРР
    bool hasDate = false;
    if (outContent1.size() > text.size()) {
        std::string addedText = outContent1.substr(text.size());
        // Шукаємо шаблон ДД.ММ.РРРР у доданому тексті
        // Спрощена перевірка - шукаємо 2 точки
        if (addedText.find('.') != std::string::npos &&
            addedText.find('.', addedText.find('.') + 1) != std::string::npos) {
            hasDate = true;
        }
    }

    bool test1Passed = result1 && hasDate;
    logTestResult("task10_2 - дозапис дати", test1Passed);

    // Тест 2: Порожній файл
    std::string inFile2 = createTestFile("test10_2_input2.txt", "");

    bool result2 = task10_2(inFile2.c_str());
    std::string outContent2 = readFileContent(inFile2);

    // Перевіряємо наявність дати
    hasDate = false;
    if (!outContent2.empty()) {
        // Спрощена перевірка - шукаємо 2 точки
        if (outContent2.find('.') != std::string::npos &&
            outContent2.find('.', outContent2.find('.') + 1) != std::string::npos) {
            hasDate = true;
        }
    }

    bool test2Passed = result2 && hasDate;
    logTestResult("task10_2 - порожній файл", test2Passed);

    // Тест 3: Неіснуючий файл
    bool result3 = task10_2("nonexistent_date_file.txt");
    bool test3Passed = !result3;
    logTestResult("task10_2 - неіснуючий файл", test3Passed);
}

// Тестування функції task10_3
void testTask10_3() {
    std::cout << "\n=== Тестування функції task10_3 ===\n";

    // Тест 1: Запис у новий файл
    std::string outFile1 = "test10_3_output1.txt";
    double x1 = 1.0, y1 = 2.0, z1 = 3.0;
    int b1 = 5;
    std::ofstream file1(outFile1);
    file1.close();
    bool result1 = task10_3(outFile1.c_str(), x1, y1, z1, b1);
    std::string outContent1 = readFileContent(outFile1);
    bool hasCalcResult = outContent1.find("Результат обчислення функції s_calculation") != std::string::npos;
    bool hasBinaryCode  = outContent1.find("у двійковому коді: 101") != std::string::npos;
    logTestResult("task10_3 - запис у новий файл", result1 && hasCalcResult && hasBinaryCode);

    // Тест 2: Дозапис у існуючий файл
    std::string outFile2 = "test10_3_output2.txt";
    std::ofstream file2(outFile2);
    file2 << "Існуючий текст.\n";
    file2.close();
    double x2 = -2.5, y2 = 0.0, z2 = 7.8;
    int b2 = 10;
    bool result2 = task10_3(outFile2.c_str(), x2, y2, z2, b2);
    std::string outContent2 = readFileContent(outFile2);
    bool hasCalc2 = outContent2.find("s_calculation(-2.500000, 0.000000, 7.800000)") != std::string::npos;
    bool hasBinary2 = outContent2.find("у двійковому коді: 1010") != std::string::npos;
    logTestResult("task10_3 - дозапис у існуючий файл", result2 && hasCalc2 && hasBinary2);

    // Тест 3: Недоступний файл
    bool result3 = task10_3("readonly.txt", 5.0, 6.0, 7.0, 255);
    logTestResult("task10_3 - файл без прав на запис", !result3);
}

int main() {
    setlocale(LC_ALL, "uk_UA.UTF-8");
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    testTask10_1();
    testTask10_2();
    testTask10_3();
    std::cout << "\nУсі тести виконані. Деталі в файлі test_results.log" << std::endl;
    return 0;
}
