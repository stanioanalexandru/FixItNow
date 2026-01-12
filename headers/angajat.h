#pragma once
#include <string>
#include <ctime>
using namespace std;
class Angajat {
protected:
    const int id;
    string nume;
    string prenume;
    string cnp;
    tm dataAngajarii{};
    string oras;

    static int generatorId;

public:
    Angajat(string nume, string prenume, string cnp,tm dataAngajarii, string oras);
    virtual ~Angajat() = default;
    int getId() const;
    string getCNP() const;
    void modificaNume(string numeNou, string prenumeNou);
    string getNume() const;
    string getPrenume() const;
    int getZiNastere() const;
    int getLunaNastere() const;
    int getAnNastere() const;
    virtual double calculeazaSalariu() const = 0;
    virtual void afisare() const;
};
