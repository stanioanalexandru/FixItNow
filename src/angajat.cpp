#include "angajat.h"
#include <iostream>
#include <string>
int Angajat::generatorId = 1;

Angajat::Angajat(string nume, string prenume, string cnp, tm dataAngajarii, string oras)
    : id(generatorId++), nume(nume), prenume(prenume), cnp(cnp), 
      dataAngajarii(dataAngajarii), oras(oras) 
{

    if (cnp.length() != 13) {
        throw invalid_argument("CNP invalid: Lungimea trebuie sa fie de 13 cifre.");
        cout<<endl;
    }
    
    // Calcul varsta la angajare
    int anNastere = getAnNastere();
    int lunaNastere = getLunaNastere();
    int ziNastere = getZiNastere();

    int anAngajare = 1900 + dataAngajarii.tm_year;
    int lunaAngajare = dataAngajarii.tm_mon + 1; 
    int ziAngajare = dataAngajarii.tm_mday;
    int varsta = anAngajare - anNastere;

    // daca nu a avut inca ziua de nastere in anul angajarii
    if (lunaAngajare < lunaNastere || (lunaAngajare == lunaNastere && ziAngajare < ziNastere)) {
        varsta--;
    }
    // Verificare eligibilitate (minim 16 ani)
    if (varsta < 16) {
        throw invalid_argument("Eroare: Angajatul trebuie sa aiba minim 16 ani la data angajarii.");
    }
}
int Angajat::getId() const {
    return id;
}

string Angajat::getCNP() const {
    return cnp;
}

string Angajat::getNume() const 
{
    return this->nume;
}

string Angajat::getPrenume() const 
{
    return this->prenume;
}

int Angajat::getAnNastere() const {
    int s = cnp[0] - '0'; 
    int aa = stoi(cnp.substr(1, 2)); 

    int secol = 0;
    if (s == 1 || s == 2) secol = 1900;       // 1900-1999
    else if (s == 3 || s == 4) secol = 1800;  // 1800-1899
    else if (s == 5 || s == 6) secol = 2000;  // 2000-2099
    else secol = 1900; 

    return secol + aa;
}

int Angajat::getLunaNastere() const {
    return stoi(cnp.substr(3, 2));
}

int Angajat::getZiNastere() const {
    return stoi(cnp.substr(5, 2));
}

void Angajat::modificaNume(string numeNou, string prenumeNou) {
    nume = numeNou;
    prenume = prenumeNou;
}

void Angajat::afisare() const {
    cout << "ID: " << id << " | " << nume << " " << prenume<< " | CNP: " << cnp << " | Oras: " << oras << " | Data Angajare: " << (1900 + dataAngajarii.tm_year) << "-" << (dataAngajarii.tm_mon + 1) << "-" << dataAngajarii.tm_mday << "\n";
}