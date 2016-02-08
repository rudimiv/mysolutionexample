#ifndef TASK_H_INCLUDED
#define TASK_H_INCLUDED
#include <iostream>
#include "module.h"

class Solution;

class Task{
    int N;
    unsigned max_price;
    Module ***prog_modules;
    Module ***hardware_modules;
    int *prog_number;
    int *hardware_number;
public:
    Task(const char *file = "input.xml");
    ~Task();
    int get_number_of_nodes() const;
    unsigned get_max_price() const;
    friend std::ostream& operator<<(std::ostream& x, Task &a);
    friend Solution;
};

#endif // TASK_H_INCLUDED
