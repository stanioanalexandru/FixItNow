#pragma once
#include "Angajat.h"
#include <vector>

class Receptioner : public Angajat
{

    vector<int> cereriInregistrate;

public:
    Receptioner(string nume, string prenume, string cnp, tm data, string oras);
    void adaugaCerere(int idCerere);
    double calculeazaSalariu() const override;
};
