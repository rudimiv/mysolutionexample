#include "greedy_alghorithm.h"
#include <iostream>

bool check_price(Solution **solutions, int N,const unsigned max_cost);
bool check_price_less(Solution **solutions, int N, const unsigned max_cost);
void exhaust_recursive(unsigned i, unsigned N, unsigned price, Solution **best, Solution *curr);



//оптимизированный к цене
Solution find_solution_opt_price(const int MaxIter, const Task &a){
    int flag = 0;
    unsigned long long iteration = 0;
    int IterCount = 0;//счетчик итераций

    unsigned max_price = a.get_max_price();
    //генерируем перую конфигурацию
    Solution *best_solution = 0;
    Solution *curr_solution = new Solution(a);

    int number_of_nodes = a.get_number_of_nodes();
    Solution **offspring_solutions = new Solution*[number_of_nodes];
    while(IterCount < MaxIter){
        iteration++;
        //меняем решения
        for(int i = 0; i < number_of_nodes; i++) offspring_solutions[i] = new Solution(*curr_solution, i);


        Solution *last = curr_solution;
        //поиск лучшего
        if(check_price(offspring_solutions, number_of_nodes, max_price)) {
            for(int i = 0; i < number_of_nodes; i++){
                if(offspring_solutions[i]->get_price() <= max_price){
                    //по цене все ок, сооптимизируем по надежности
                    //меняем на более лучшее решение
                    if(curr_solution->get_price() > max_price){
                        curr_solution = offspring_solutions[i];
                        continue;
                    }
                    if(offspring_solutions[i]->get_relability() > curr_solution->get_relability()){
                        curr_solution = offspring_solutions[i];
                    }
                }
            }

        } else {

            //не будем убивать более дешевое решение
            //будем оптимизровать по цене в этой ветке
            if(check_price_less(offspring_solutions, number_of_nodes, curr_solution->get_price())){
                //просто поиск лучшего по цене
                for(int k = 0; k < number_of_nodes; k++){
                    if(curr_solution->get_price() > offspring_solutions[k]->get_price()){
                        curr_solution = offspring_solutions[k];
                    }
                }
            }
            //иначе оставляем
        }

        if(last != curr_solution) delete last;

        //осовождение памяти
        for(int k = 0; k < number_of_nodes; k++)
            if(offspring_solutions[k] != curr_solution) delete offspring_solutions[k];

        //сравнение решений
        if(curr_solution->get_price() > max_price) continue;
        else{
            if(!flag) std::cout<<"found_price\n";
            flag = 1;
        }
        //первое заполнение
        if(!best_solution){
            std::cout<<"first_best\n";
            best_solution = new Solution(*curr_solution);
            IterCount = 0;
            continue;
        }
        if(curr_solution->get_relability() > best_solution->get_relability()){
            std::cout<<"change_the_best\n";
            IterCount = 0;
            delete best_solution;
            best_solution = new Solution(*curr_solution);
        } else IterCount++;

    }

    Solution res(*best_solution);
    delete best_solution;
    if(curr_solution) delete curr_solution;
    delete []offspring_solutions;

    std::cout<<"number_of_iterations:\t"<<iteration<<"\n";
    return res;
}


//классический алгоритм
Solution find_solution(const int MaxIter, const Task &a){
    unsigned long long iteration = 0;
    int IterCount = 0;//счетчик итераций

    unsigned max_price = a.get_max_price();
    unsigned number_of_nodes = a.get_number_of_nodes();
    //генерируем перую конфигурацию
    Solution *curr_solution = new Solution(a);
    Solution *best_solution = 0;

    //массив для потомков
    Solution **offspring_solutions = new Solution*[number_of_nodes];

    do{
        if(curr_solution->get_price() <= max_price){
            if(!best_solution){
                best_solution = new Solution(*curr_solution);
                IterCount = 0;
            } else{
                if(best_solution->get_relability() < curr_solution->get_relability()){
                    delete best_solution;
                    best_solution = new Solution(*curr_solution);
                    IterCount = 0;
                } else IterCount++;//прощел очередную проверку
            }
        }

        //генерируем потомков
        for(unsigned i = 0; i < number_of_nodes; i++){
            offspring_solutions[i] = new Solution(*curr_solution, i);
        }

        if(check_price(offspring_solutions, number_of_nodes, max_price)){
            //присутствуют решения проходящие по цене
            for(unsigned i = 0; i < number_of_nodes; i++){
                if(offspring_solutions[i]->get_price() <= max_price){
                    if(offspring_solutions[i]->get_relability() > curr_solution->get_relability()){
                        delete curr_solution;
                        curr_solution = offspring_solutions[i];
                        offspring_solutions[i] = 0;
                    }
                }
            }
        } else {
            //их нету. Просто выбираем по надежности
            for(unsigned i = 0; i < number_of_nodes; i++){
                if(offspring_solutions[i]->get_relability() > curr_solution->get_relability()){
                    delete curr_solution;
                    curr_solution = offspring_solutions[i];
                    offspring_solutions[i] = 0;
                }
            }
        }

        //чистим память
        for(unsigned i = 0; i < number_of_nodes; i++)
            if(curr_solution != offspring_solutions[i] && offspring_solutions[i]) delete offspring_solutions[i];

        //так-как алгоритм работает плохо то оставим отладочный вывод
        //std::cout<<"curr: price="<<curr_solution->get_price()<<" relabale="<<curr_solution->get_relability()<<std::endl;
        //if(best_solution) std::cout<<"best: price="<<best_solution->get_price()<<" relabale="<<best_solution->get_relability()<<std::endl;
        getchar();
        iteration++;
    } while(IterCount < MaxIter);


    std::cout<<"iterations: "<<iteration<<std::endl;
    Solution res = Solution(*best_solution);
    delete best_solution;
    if(curr_solution) delete curr_solution;
    delete []offspring_solutions;

    return res;
}

//полный перебор
Solution exhaustive_alghorithm(const Task &a) {
    Solution *best = 0;
    Solution curr(a);
    curr.set_to_simple();
    unsigned price = a.get_max_price();

    exhaust_recursive(0, a.get_number_of_nodes(), price, &best, &curr);

    Solution res(*best);
    delete best;
    return res;
}


void exhaust_recursive(unsigned i, unsigned N, unsigned price, Solution **best, Solution *curr){
    if(i >= N){
        //cout<<*curr;
        //cout<<"////////////////////////////////////////////////\n";
        //оцениваем
        if(!(*best)){//еще не найдено проходящего по цене
            if(curr->get_price() <= price){//нашли
                *best = new Solution(*curr);
            }
        } else {
            if(curr->get_price() <= price){//сравниваем именно с price!!
                if(curr->get_relability() > (*best)->get_relability()) {
                    delete *best;
                    *best = new Solution(*curr);
                }
            }
        }
        return;
    }


    do{
        exhaust_recursive(i + 1, N, price, best, curr);
    }while(curr->change_node_to_next(i));
}


//функция проверяет есть ли в массиве решения проходящие по цене
bool check_price(Solution **solutions, int N, const unsigned max_cost){
    bool res = false;

    for(int i = 0; i < N; i++){
        if(solutions[i]->get_price() <= max_cost){
            res = true;
            break;
        }
    }

    return res;
}


bool check_price_less(Solution **solutions, int N, const unsigned max_cost){
    bool res = false;

    for(int i = 0; i < N; i++){
        if(solutions[i]->get_price() < max_cost){
            res = true;
            break;
        }
    }

    return res;
}
