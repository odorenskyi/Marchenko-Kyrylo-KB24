#ifndef STRUCT_TYPE_PROJECT_IVANOV_8_INCLUDED
#define STRUCT_TYPE_PROJECT_IVANOV_8_INCLUDED

#pragma once
#include "struct_type_project_8.h"

namespace Ivanov {
    bool addRecord(PostalRecord*& head, const PostalRecord& newRec);
    bool deleteRecord(PostalRecord*& head, int index, const std::string& city);
}

#endif // STRUCT_TYPE_PROJECT_IVANOV_8_INCLUDED
