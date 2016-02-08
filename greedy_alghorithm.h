#ifndef GREEDY_ALGHORITHM_H_INCLUDED
#define GREEDY_ALGHORITHM_H_INCLUDED
#include "solution.h"
#include <iostream>

Solution find_solution(const int MaxIter, const Task &a);
Solution find_solution_opt_price(const int MaxIter, const Task &a);
Solution exhaustive_alghorithm(const Task &a);//полный перебор
#endif // GREEDY_ALGHORITHM_H_INCLUDED
