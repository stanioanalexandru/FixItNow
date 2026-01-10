#pragma once
#include <vector>
#include <queue>
#include <map>
#include <iostream>
#include "Angajat.h"
#include "cerere_reparatie.h"
using namespace std;

class Service
{
    static Service *instance;
    vector<Angajat *> angajati;
    queue<CerereReparatie *> cereriAsteptare;
    vector<CerereReparatie *> cereriActive;     // lista pentru monitorizare
    vector<CerereReparatie *> cereriFinalizate; // istoric

    map<string, vector<string>> modeleSuportate;
    map<string, int> statisticaRefuzuri;

    Service() = default;

public:
    static Service &getInstance();

    Service(const Service &) = delete;
    Service &operator=(const Service &) = delete;
    void adaugaAngajat(Angajat *a);
    void stergeAngajat(string cnp);
    void adaugaCerere(CerereReparatie *c);
    void afiseazaAngajati() const;
    void modificaNumeAngajat(string cnp, string numeNou, string prenumeNou);
    void simularePas();
    bool verificaStaffMinim() const;
    void ruleazaSimulare();

    // gestiune modele suportate
    void adaugaModelSuportat(const string &marca, const string &model);
    void stergeModelSuportat(const string &marca, const string &model);
    bool verificaCompatibilitate(const string &marca, const string &model);
    void afiseazaModeleSuportate() const;

    // statistica refuzuri
    void inregistreazaCerereRespinsa(const string &marca, const string &model);
    void afiseazaStatisticaRefuzuri() const;

    // incarcare date din fisiere csv
    void incarcaCereriDinFisier(const string &numeFisier);
    void incarcaModeleDinFisier(const string &numeFisier);
    void incarcaAngajatiDinFisier(const string &numeFisier);
    void incarcaSpecializariDinFisier(const string &numeFisier);


    ~Service();
};