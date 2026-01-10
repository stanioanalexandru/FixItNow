#pragma once
#include "Angajat.h"
#include <vector>
#include <string>

class CerereReparatie;

class Tehnician : public Angajat
{
    vector<string> tipuri;
    vector<string> marci;

    vector<CerereReparatie *> cereriActive;
    vector<CerereReparatie*> cereriCompletate;

    double totalDurataMunca = 0;
    double valoareReparatii = 0;

public:
    Tehnician(string nume, string prenume, string cnp, tm data, string oras);
    void adaugaSpecializare(const string &tip, const string &marca);
    bool poateRepara(const string &tip, const string &marca) const;
    bool poatePreluaCerere() const;
    void adaugaCerere(CerereReparatie *c);
    void finalizeazaCerere(CerereReparatie *c, double durata);
    double getDurataMunca() const;
    double calculeazaSalariu() const override;
    bool areCereriActive() const;
    void simuleazaTic();
    vector<CerereReparatie*> getIstoricCereri() const { return cereriCompletate; }
};
