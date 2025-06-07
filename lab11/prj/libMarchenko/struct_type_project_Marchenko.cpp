#include "struct_type_project_Marchenko.h"
#include <iostream>
#include <fstream>
#include <iomanip>

void Marchenko::printAll(PostalRecord* head) {
    std::cout << std::left
              << std::setw(8) << "Index"
              << std::setw(15) << "Region"
              << std::setw(15) << "District"
              << std::setw(20) << "City"
              << std::setw(25) << "PostOffice"
              << "\n";
    for (auto* cur = head; cur; cur = cur->next) {
        std::cout
            << std::setw(8) << cur->index
            << std::setw(15) << cur->region
            << std::setw(15) << cur->district
            << std::setw(20) << cur->city
            << std::setw(25) << cur->postOffice
            << "\n";
    }
}

bool Marchenko::saveAndExit(PostalRecord* head, const std::string& filename) {
    std::ofstream fout(filename);
    if (!fout.is_open()) return false;
    for (auto* cur = head; cur; cur = cur->next) {
        fout << cur->index << ' '
             << cur->region << ' '
             << cur->district << ' '
             << cur->city << ' '
             << cur->postOffice << "\n";
    }
    fout.close();
    return true;
}
