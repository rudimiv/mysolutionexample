#include "task.h"
#include "tinyxml/tinyxml.h"
#include "tinyxml/tinystr.h"

std::ostream& operator<<(std::ostream& x, Task &a){
    x<<"Number of Nodes: "<<a.N<<"\t"<<"MaxPrice: "<<a.max_price<<"\n";
    for(int i = 0; i < a.N; i++){
        x<<"--------\n";
        x<<"soft\n";
        for(int k = 0; k < a.prog_number[i]; k++) {
            x<<a.prog_modules[i][k]->get_price()<<"\t"<<a.prog_modules[i][k]->get_relability()<<"\n";
        }
        x<<"\nhardware\n";
        for(int k = 0; k < a.hardware_number[i]; k++) {
             x<<a.hardware_modules[i][k]->get_price()<<"\t"<<a.hardware_modules[i][k]->get_relability()<<"\n";
        }
    }
    return x;
}

Task::Task(const char *file){
    TiXmlDocument doc(file);
    if(!doc.LoadFile()){
        std::cout<<"FileError\n";
        exit(1);
    }
    TiXmlHandle hdoc(&doc);

    //получение цены
    TiXmlElement * syst = hdoc.FirstChild("system").ToElement();
    max_price = atol(syst->Attribute("limitcost"));

    //считаем количество узлов
    TiXmlElement *module = hdoc.FirstChild("system").FirstChild("module").ToElement();
    N = 0;
    for(module; module; module = module->NextSiblingElement()) N++;

    //выделяем память под указтели на узлы
    prog_modules = new Module**[N];
    hardware_modules = new Module**[N];

    prog_number = new int[N];
    hardware_number = new int[N];
    //проход по модулям
    for(int i = 0; i < N; i++){
        int sw_modules = 0;
        int hw_modules = 0;
        //unsigned price;
        //double relability;
        //считаем количество software module
        TiXmlNode *modul = hdoc.FirstChild("system").Child("module",i).Node();
        TiXmlNode *sw_r = 0;
        while((sw_r = modul->IterateChildren("sw", sw_r))) sw_modules++;

        //считаем количество hardware module
        TiXmlNode *hw_r = 0;
        while((hw_r = modul->IterateChildren("hw", hw_r))) hw_modules++;

        prog_number[i] = sw_modules;
        hardware_number[i] = hw_modules;
        //выделяем память
        prog_modules[i] = new Module*[sw_modules];
        hardware_modules[i] = new Module*[hw_modules];

        //заполнение модулями
        TiXmlElement *elem;
        sw_r = 0;
        int k = 0;
        while((sw_r = modul->IterateChildren("sw", sw_r))) {
            elem = sw_r->ToElement();
            prog_modules[i][k++] = new Module(atol(elem->Attribute("cost")), atof(elem->Attribute("rel")));
        }

        k = 0;
        while((sw_r = modul->IterateChildren("hw", sw_r))) {
            elem = sw_r->ToElement();
            hardware_modules[i][k++] = new Module(atol(elem->Attribute("cost")), atof(elem->Attribute("rel")));
        }
    }
}


Task::~Task(){
    //освобождение памяти
    for(int i = 0; i < N; i++){
        for(int k = 0; k < prog_number[i]; k++) delete prog_modules[i][k];
        for(int k = 0; k < hardware_number[i]; k++) delete hardware_modules[i][k];
        delete []prog_modules[i];
        delete []hardware_modules[i];
    }

    delete []prog_modules;
    delete []hardware_modules;

    delete []prog_number;
    delete []hardware_number;
}

int Task::get_number_of_nodes() const{
    return N;
}


unsigned Task::get_max_price() const{
    return max_price;
}
