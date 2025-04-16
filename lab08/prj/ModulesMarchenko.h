#ifndef MODULESMARCHENKO_H_INCLUDED
#define MODULESMARCHENKO_H_INCLUDED

double s_calculation(double x, double y, double z);

// Структура для зберігання результату обчислення зарплати
struct SalaryInfo {
    double grossSalary; // Нарахована заробітна плата (грн.)
    double totalTaxes;  // Сума податків (грн.)
    double netSalary;   // Сума до виплати (грн.)
};

SalaryInfo calculateSalary(int daysWorked);

// Структура для зберігання результату конвертації розміру шкарпеток
struct SockSize {
    int size_US;         // Розмір за системою США (та Великобританії)
    std::string size_EU; // Розмір за системою ЄС (діапазон)
    bool valid;          // Прапорець для перевірки коректності вводу
};

SockSize convertSockSize(int size_UA);
int countBinarySymbols(unsigned int N);

#endif // MODULESMARCHENKO_H_INCLUDED
