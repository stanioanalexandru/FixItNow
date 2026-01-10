#include "supervizor.h"

Supervizor::Supervizor(string nume, string prenume, string cnp, tm data, string oras)
    : Angajat(nume, prenume, cnp, data, oras) {}
double Supervizor::calculeazaSalariu() const
{
    double baza = 4000;

    time_t now = time(0);
    tm *ltm = localtime(&now);

    int aniVechime = (1900 + ltm->tm_year) - (1900 + dataAngajarii.tm_year);
    if (aniVechime < 0)
        aniVechime = 0;

    double bonusFidelitate = (aniVechime / 3) * 0.05 * baza;
    double sporConducere = baza * 0.20; // 20% spor specific supervizorului
    double transport = (oras != "Bucuresti") ? 400 : 0;

    return baza + bonusFidelitate + sporConducere + transport;
}