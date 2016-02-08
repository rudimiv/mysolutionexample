#include "module.h"

unsigned Module::get_price() const{
    return price;
}
double Module::get_relability() const{
    return relability;
}

Module::Module(unsigned p_price, double p_relability):price(p_price), relability(p_relability){}
