#include "struct_type_project_Ivanov.h"

bool Ivanov::addRecord(PostalRecord*& head, const PostalRecord& newRec) {
    auto* node = new PostalRecord(newRec);
    node->next = head;
    head = node;
    return true;
}

bool Ivanov::deleteRecord(PostalRecord*& head, int index, const std::string& city) {
    PostalRecord* prev = nullptr;
    for (auto* cur = head; cur; prev = cur, cur = cur->next) {
        if (cur->index == index && cur->city == city) {
            if (prev) prev->next = cur->next;
            else head = cur->next;
            delete cur;
            return true;
        }
    }
    return false;
}
