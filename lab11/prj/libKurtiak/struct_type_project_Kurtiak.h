#ifndef STRUCT_TYPE_PROJECT_Kurtiak_H_INCLUDED
#define STRUCT_TYPE_PROJECT_Kurtiak_H_INCLUDED

#pragma once
#include "struct_type_project_8.h"
#include <vector>

namespace Kurtiak {
    // Завантаження даних з файлу в динамічну структуру
    bool loadData(const std::string& filename, PostalRecord*& head);
    // Пошук усіх записів із заданим індексом
    std::vector<PostalRecord*> searchByIndex(PostalRecord* head, int index);
}

#endif // STRUCT_TYPE_PROJECT_Kurtiak_H_INCLUDED
