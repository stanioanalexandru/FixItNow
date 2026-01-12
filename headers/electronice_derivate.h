#pragma once
#include "electrocasnic.h"
#include <iostream>

class Frigider : public Electrocasnic
{
    bool areCongelator;

public:
    Frigider(const string &marca, const string &model, int an, double pret, bool congelator) : Electrocasnic("Frigider", marca, model, an, pret), areCongelator(congelator) {}

    void afisare() const override
    {
        cout << "Frigider " << marca << " " << model << ", Congelator: " << (areCongelator ? "Da" : "Nu") << endl;
    }
};

class Televizor : public Electrocasnic
{
    string diagonala;

public:
    Televizor(const string &marca, const string &model, int an, double pret, string diag): Electrocasnic("TV", marca, model, an, pret), diagonala(diag) {}

    void afisare() const override
    {
        cout << "TV " << marca << " " << model << ", Diagonala: " << diagonala << endl;
    }
};

class MasinaSpalat : public Electrocasnic
{
    int capacitateKg;

public:
    MasinaSpalat(const string &marca, const string &model, int an, double pret, int cap): Electrocasnic("MasinaSpalat", marca, model, an, pret), capacitateKg(cap) {}

    void afisare() const override
    {
        cout << "Masina Spalat " << marca << " " << model << ", Capacitate: " << capacitateKg << "kg" << endl;
    }
};