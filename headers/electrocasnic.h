#ifndef ELECTROCASNIC_H
#define ELECTROCASNIC_H

#include <string>
using namespace std;

class Electrocasnic {
protected:
    string tip;
    string marca;
    string model;
    int anFabricatie;
    double pretCatalog;

public:
    Electrocasnic(const string& tip,const string& marca,const string& model,int an,double pret): tip(tip), marca(marca), model(model),anFabricatie(an), pretCatalog(pret) {}

    virtual ~Electrocasnic() {}
    virtual void afisare() const = 0;
    string getTip() const { return tip; }
    string getMarca() const { return marca; }
    string getModel() const { return model; }
    int getAnFabricatie() const { return anFabricatie; }
    double getPretCatalog() const { return pretCatalog; }
};

#endif
