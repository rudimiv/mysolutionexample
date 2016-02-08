/*
    Задание по спецкурсу ЛВК
    Выполняет студент 205 групы Иванов Дмитрий Александрович
    В качестве библиотеки для парсинга XML использовалвавсь TinyXML
*/

#include <iostream>
#include <ctime>
#include <cstdlib>
#include "task.h"
#include "solution.h"
#include "greedy_alghorithm.h"

using namespace std;

/*
    0 параметр - имя входного файла(без него не работает
    1 параметр - MaxIter(по умолчанию 100)
    2 параметр - имя выходного файла(по умолчанию out.xml)
*/
int main(int argc, char *argv[]){
    /*unsigned MaxIter = 0;
    if(argc < 2){
        cout<<"please input parametrs\n";
        return 0;
    }
    if(argc == 2) MaxIter = 100;
    if(argc > 2) MaxIter = atoi(argv[2]);

    srand(time(0));
    Task task(argv[1]);

    Solution res_sol = find_solution_opt_price(MaxIter, task);


    //Запись в файл результата
    if(argc == 4) res_sol.ToXML(argv[3], task, MaxIter);
    else res_sol.ToXML("out.xml", task, MaxIter);*/

    Task a("example.xml");
    Solution res = exhaustive_alghorithm(a);
    cout<<res;

    Task c("example.xml");
    Solution res3 = find_solution_opt_price(123, c);
    cout<<res3;


    Task b("example.xml");
    Solution res2 = find_solution(123, b);
    cout<<res2;
    return 0;
}
