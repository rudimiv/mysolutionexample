#include <ctime>
#include <cstdlib>
#include <cstring>

#include "solution.h"
#include "tinyxml/tinystr.h"

Solution::Solution(const Task &a){
    N = a.N;
    nodes = new Node[a.N];

    srand(time(0));

    int s_n, h_n;
    for(unsigned i = 0; i < a.N; i++){
        nodes[i].set_possibles(a.prog_number[i], a.hardware_number[i], a.prog_modules[i], a.hardware_modules[i]);
        //устанавливаем рандомную конфигурацию
        s_n = rand() % a.prog_number[i];
        h_n = rand() % a.hardware_number[i];

        nodes[i].set_modules(a.prog_modules[i][s_n], a.hardware_modules[i][h_n]);
    }
}

Solution::Solution(const Solution &p){
    N = p.N;
    nodes = new Node[p.N];

    memcpy(nodes, p.nodes, N * sizeof(Node));
}

Solution::Solution(const Solution &p, unsigned k){
    N = p.N;
    //Копируем узлы
    nodes = new Node[p.N];
    memcpy(nodes, p.nodes, N * sizeof(Node));

    //изменяем к-узел
    //srand(time(0));


    unsigned s_n = rand() % nodes[k].get_number_of_prog_modules();
    //избавимся от возвращения к старому
    if(s_n == nodes[k].get_prog_number()) {
        if(s_n){
            if(s_n < nodes[k].get_number_of_prog_modules() - 1){
                if(rand()%2) s_n++;
                else s_n--;
            } else s_n--;
        } else s_n++;
    }
    if(nodes[k].get_number_of_prog_modules() == 1) s_n  = 0;
    unsigned h_n = rand() % nodes[k].get_number_of_hardware_modules();

    if(h_n == nodes[k].get_hardware_number()){
        if(h_n){
            if(h_n < nodes[k].get_number_of_hardware_modules() - 1){
                if(rand()%2) h_n++;
                else h_n--;
            } else h_n--;
        } else h_n++;
    }

    if(nodes[k].get_number_of_hardware_modules() == 1) h_n  = 0;
    nodes[k].set_modules_by_numbers(s_n, h_n);
}

Solution::~Solution(){
    delete[] nodes;
}
unsigned Solution::get_price() const{
    unsigned res = 0;

    for(unsigned i = 0; i < N; i++) res += nodes[i].get_price();

    return res;
}

double Solution::get_relability() const{
    double res = 1;

    for(unsigned i = 0; i < N; i++) res *= nodes[i].get_relability();

    return res;
}

unsigned Solution::get_number_of_nodes() const{
    return N;
}

//запись в файл
void Solution::ToXML(const char* filename, const Task &a, const unsigned MaxIter) const{
    TiXmlDocument doc;
    TiXmlElement* system_l = new TiXmlElement("system");
    system_l->SetAttribute("limitcost", a.get_max_price());
    system_l->SetDoubleAttribute("rel", this->get_relability());
    system_l->SetAttribute("iteration", MaxIter);
    doc.LinkEndChild(system_l);

    TiXmlElement** modules = new TiXmlElement*[N];
    TiXmlElement** hws = new TiXmlElement*[N];
    TiXmlElement** sws = new TiXmlElement*[N];

    for(unsigned i = 0; i < N; i++){
        modules[i] = new TiXmlElement("module");
        sws[i] = new TiXmlElement("sw");
        hws[i] = new TiXmlElement("hw");

        sws[i]->SetAttribute("num", nodes[i].get_prog_number() + 1);
        sws[i]->SetDoubleAttribute("rel", nodes[i].get_prog_relability());
        sws[i]->SetAttribute("cost", nodes[i].get_prog_price());

        hws[i]->SetAttribute("num", nodes[i].get_hardware_number() + 1);
        hws[i]->SetDoubleAttribute("rel", nodes[i].get_hardware_relability());
        hws[i]->SetAttribute("cost", nodes[i].get_hardware_price());


        modules[i]->SetAttribute("num", i + 1);
        modules[i]->LinkEndChild(sws[i]);
        modules[i]->LinkEndChild(hws[i]);

        system_l->LinkEndChild(modules[i]);
    }

    doc.SaveFile(filename);
    doc.Clear();
}

int Solution::change_node_to_next(unsigned node_number){
    if(node_number >= N) return -1;

    unsigned number_of_prog = nodes[node_number].get_number_of_prog_modules();
    unsigned number_of_hardware = nodes[node_number].get_number_of_hardware_modules();
    unsigned curr_prog = nodes[node_number].get_prog_number();
    unsigned curr_hardware = nodes[node_number].get_hardware_number();

    if(number_of_hardware == curr_hardware + 1 && number_of_prog == curr_prog + 1){
        nodes[node_number].set_modules_by_numbers(0, 0);
        return 0;
    }


    if(number_of_prog > curr_prog + 1){
        curr_prog++;
        nodes[node_number].set_modules_by_numbers(curr_prog, curr_hardware);
    } else {
        curr_prog = 0;
        curr_hardware++;
        nodes[node_number].set_modules_by_numbers(curr_prog, curr_hardware);
    }

    return 1;
}


//установка все в стартовые
void Solution::set_to_simple(){
    for(unsigned i = 0; i < N; ++i)
        nodes[i].set_modules_by_numbers(0, 0);
}

std::ostream& operator<<(std::ostream& x, const Solution &a){
    x<<"Number of Nodes: "<<a.N<<"\n";
    x<<"Common price: "<<a.get_price()<<"\n";
    x<<"Common realibility: "<<a.get_relability()<<"\n";
    for(unsigned i = 0; i < a.N; i++){

        x<<"--------\n";
        x<<"soft:\t"<<(a.nodes[i].prog_module)->get_relability()<<"\t"<<(a.nodes[i].prog_module)->get_price()<<"\n";
        x<<"\nhardware:\t"<<(a.nodes[i].hardware_module)->get_relability()<<"\t"<<(a.nodes[i].hardware_module)->get_price()<<"\n";

    }
    return x;
}














