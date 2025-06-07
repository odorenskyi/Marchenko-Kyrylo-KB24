#ifndef STRUCT_TYPE_PROJECT_MARCHENKO_H_INCLUDED
#define STRUCT_TYPE_PROJECT_MARCHENKO_H_INCLUDED

#pragma once
#include "struct_type_project_8.h"

namespace Marchenko {
    void printAll(PostalRecord* head);
    bool saveAndExit(PostalRecord* head, const std::string& filename);
}

#endif // STRUCT_TYPE_PROJECT_MARCHENKO_H_INCLUDED
