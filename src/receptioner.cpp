#include "receptioner.h"

Receptioner::Receptioner(string nume, string prenume, string cnp, tm data, string oras)
    : Angajat(nume, prenume, cnp, data, oras) {}
    
void Receptioner::adaugaCerere(int idCerere) {
    cereriInregistrate.push_back(idCerere);
}

double Receptioner::calculeazaSalariu() const {
    double salariu = 4000;
    return salariu;
}
