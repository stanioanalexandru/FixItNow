#pragma once
#include "Angajat.h"
class Supervizor : public Angajat {
public:

    Supervizor(string nume, string prenume, string cnp, tm data, string oras);
    double calculeazaSalariu() const override;
};
