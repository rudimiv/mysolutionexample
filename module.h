#ifndef MODULE_H_INCLUDED
#define MODULE_H_INCLUDED

class Module{
    unsigned price;
    double relability;
public:
    Module(unsigned p_price, double p_relability);
    unsigned get_price() const;
    double get_relability() const;
};

#endif // MODULE_H_INCLUDED
