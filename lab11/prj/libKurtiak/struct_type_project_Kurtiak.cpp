#include "struct_type_project_Kurtiak.h"
#include <fstream>
#include <vector>

bool Kurtiak::loadData(const std::string& filename, PostalRecord*& head) {
    std::ifstream fin(filename);
    if (!fin.is_open()) return false;
    PostalRecord* tail = nullptr;
    while (!fin.eof()) {
        auto* rec = new PostalRecord{};
        if (!(fin >> rec->index >> rec->region >> rec->district
              >> rec->city >> rec->postOffice)) { delete rec; break; }
        rec->next = nullptr;
        if (!head) head = tail = rec;
        else { tail->next = rec; tail = rec; }
    }
    fin.close();
    return true;
}

std::vector<PostalRecord*> Kurtiak::searchByIndex(PostalRecord* head, int index) {
    std::vector<PostalRecord*> results;
    for (auto* cur = head; cur; cur = cur->next)
        if (cur->index == index) results.push_back(cur);
    return results;
}
