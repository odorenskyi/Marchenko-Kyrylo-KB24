#include <iostream>
#include <string>
#include <vector>
#include <limits>

#include "struct_type_project_8.h"         // Опис PostalRecord
#include "struct_type_project_Kurtiak.h"   // loadData, searchByIndex
#include "struct_type_project_Ivanov.h"    // addRecord, deleteRecord
#include "struct_type_project_Marchenko.h" // printAll, saveAndExit

void printMenu() {
    std::cout << "\n<<< Довідник Укрпошти >>>\n";
    std::cout << "1. Завантажити і показати кількість" << std::endl;
    std::cout << "2. Показати всі записи" << std::endl;
    std::cout << "3. Цикл: Додати і Видалити" << std::endl;
    std::cout << "4. Зберегти та завершити" << std::endl;
    std::cout << "Ваш вибір: ";
}

int main() {
    system("chcp 65001 && cls");
    PostalRecord* head = nullptr;
    std::string fn = "data.txt";
    int opt;

    while (true) {
        printMenu(); std::cin >> opt; std::cin.ignore();
        if (opt == 1) {
            Kurtiak::loadData(fn, head);
            int cnt = 0; for (auto*p=head; p; p=p->next) cnt++;
            std::cout << "Завантажено " << cnt << " запис(ів).\n";
        } else if (opt == 2) {
            Marchenko::printAll(head);
        } else if (opt == 3) {
            PostalRecord r; int i; std::string c;
            std::cout << "Індекс для додавання: "; std::cin >> i; std::cin.ignore(); r.index = i;
            std::cout << "Індекс для видалення: "; std::cin >> i; std::cin.ignore();
            std::cout << "Місто для видалення: "; std::getline(std::cin, c);
            r.city = ""; Ivanov::addRecord(head, r);
            Ivanov::deleteRecord(head, i, c);
        } else if (opt == 4) {
            Marchenko::saveAndExit(head, fn);
            std::cout << "Дані збережено. До побачення!\n";
            break;
        } else std::cout << "Невірний вибір.\n";
    }
    return 0;
}
