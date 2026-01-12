#include "tehnician.h"
#include "cerere_reparatie.h"
#include <iostream>

Tehnician::Tehnician(string nume, string prenume, string cnp, tm data, string oras)
    : Angajat(nume, prenume, cnp, data, oras) {}
    
void Tehnician::adaugaSpecializare(const string& tip, const string& marca) {
    tipuri.push_back(tip);
    marci.push_back(marca);
}

bool Tehnician::poateRepara(const string& tip, const string& marca) const {
    bool tipOk = false;
    bool marcaOk = false;
    for (const auto& t : tipuri) if (t == tip) tipOk = true;
    for (const auto& m : marci) if (m == marca) marcaOk = true;
    return tipOk && marcaOk;
}

bool Tehnician::poatePreluaCerere() const {
    return cereriActive.size() < 3;
}

void Tehnician::adaugaCerere(CerereReparatie* c) {
    cereriActive.push_back(c);
}

void Tehnician::finalizeazaCerere(CerereReparatie* c, double durata) {
    totalDurataMunca += durata;
    valoareReparatii += c->getPret();

    for (auto it = cereriActive.begin(); it != cereriActive.end(); ++it) {
        if ((*it)->getId() == c->getId()) {
            cereriCompletate.push_back(*it);
            cereriActive.erase(it);
            break;
        }
    }
}

double Tehnician::getDurataMunca() const {
    return totalDurataMunca;
}

double Tehnician::calculeazaSalariu() const {
    double baza = 4000;
    
    time_t now = time(0);
    tm* ltm = localtime(&now);
    int aniVechime = (1900 + ltm->tm_year) - (1900 + dataAngajarii.tm_year);
    double bonusFidelitate = (aniVechime / 3) * 0.05 * baza;
    double bonusReparatii = valoareReparatii * 0.02;
    double transport = (oras != "Bucuresti") ? 400 : 0;
    return baza + bonusFidelitate + bonusReparatii + transport;
}

bool Tehnician::areCereriActive() const {
    return !cereriActive.empty();
}

void Tehnician::simuleazaTic() {
    if (cereriActive.empty()) return;

    //fifo
    CerereReparatie* cerereCurenta = cereriActive.front();

    cerereCurenta->scadeDurata();
    
    cout << "   [Tehnician " << nume << "] lucreaza la cererea ID " << cerereCurenta->getId() << ". Timp ramas: " << cerereCurenta->getDurata() << endl;

    if (cerereCurenta->getDurata() <= 0) {
        cerereCurenta->finalizeaza();
        finalizeazaCerere(cerereCurenta, 0); 
        cout << "   [Tehnician " << nume << "] A FINALIZAT cererea ID " << cerereCurenta->getId() << "!" << endl;

    }
}

