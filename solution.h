#ifndef SOLUTION_H_INCLUDED
#define SOLUTION_H_INCLUDED
#include "module.h"
#include "task.h"
#include "tinyxml/tinyxml.h"
//const - важен
std::ostream& operator<<(std::ostream& x, const Solution &a);

class Node{
    unsigned number_of_possible_prog_modules;
    unsigned number_of_possible_hardware_modules;

    unsigned cur_prog_number;
    unsigned cur_hardware_number;

    Module *prog_module;
    Module *hardware_module;
    Module **possible_prog_modules;
    Module **possible_hardware_modules;
public:
   /* Node(Module * p_m, Module * h_m, Module **p_p_m, Module **p_h_m) :
        prog_module(p_m), hardware_module(h_m), possible_prog_modules(p_p_m), possible_hardware_modules(p_h_m) { }*/
    Node() {
        prog_module = hardware_module = NULL; possible_hardware_modules = possible_prog_modules = NULL;
    }

    void set_possibles(unsigned prog_number, unsigned hardware_number, Module **poss_progs, Module **poss_hard){
        number_of_possible_prog_modules = prog_number;
        number_of_possible_hardware_modules = hardware_number;
        possible_prog_modules = poss_progs;
        possible_hardware_modules = poss_hard;
    }
    void set_modules(Module *prog, Module *hard){
        int i = 0;
        while(prog != possible_prog_modules[i]) i++;
        cur_prog_number = i;

        i = 0;
        while(hard != possible_hardware_modules[i]) i++;
        cur_hardware_number = i;

        prog_module = prog;
        hardware_module = hard;
    }

    void set_modules_by_numbers(unsigned s_n, unsigned h_n){
        cur_prog_number = s_n;
        cur_hardware_number = h_n;
        prog_module = possible_prog_modules[s_n];
        hardware_module = possible_hardware_modules[h_n];
    }

    unsigned get_prog_number() const{
        return cur_prog_number;
    }

    unsigned get_hardware_number() const{
        return cur_hardware_number;
    }

    unsigned get_number_of_prog_modules() const{
        return number_of_possible_prog_modules;
    }

    unsigned get_number_of_hardware_modules() const{
        return number_of_possible_hardware_modules;
    }

    unsigned get_price() const{
        return prog_module->get_price() + hardware_module->get_price();
    }

    unsigned get_prog_price() const{
        return prog_module->get_price();
    }

    unsigned get_hardware_price() const{
        return hardware_module->get_price();
    }

    double get_prog_relability() const{
        return prog_module->get_relability();
    }

    double get_hardware_relability() const{
        return hardware_module->get_relability();
    }

    double get_relability() const{
        return prog_module->get_relability() * hardware_module->get_relability();
    }

    //для отладки
    friend std::ostream& operator<<(std::ostream& x, const Solution &a);
};

class Solution{
    unsigned N; //количество узлов
    Node *nodes;//массив узлов
public:
    Solution(const Task &a);
    Solution(const Solution &p);
    Solution(const Solution &p, unsigned k);
    ~Solution();

    unsigned get_price() const;
    double get_relability() const;
    unsigned get_number_of_nodes() const;
    void ToXML(const char* filename, const Task &a, const unsigned MaxIter) const;
    int change_node_to_next(unsigned node_number);
    void set_to_simple();
    friend std::ostream& operator<<(std::ostream& x, const Solution &a);
};
























#endif // SOLUTION_H_INCLUDED
