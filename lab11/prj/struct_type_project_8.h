#ifndef STRUCT_TYPE_PROJECT_N_H
#define STRUCT_TYPE_PROJECT_N_H

#pragma once
#include <string>

struct PostalRecord {
    int index;
    std::string region;
    std::string district;
    std::string city;
    std::string postOffice;
    PostalRecord* next;
};


#endif // STRUCT_TYPE_PROJECT_N_H
