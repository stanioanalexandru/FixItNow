#include "Service.h"
#include "tehnician.h"
#include "receptioner.h"
#include "supervizor.h"
#include "electronice_derivate.h"
#include <iostream>
#include <limits>
#include <time.h>
#include <chrono>
#include <thread>
using namespace std;

void afisareMeniu()
{
    cout << "\n=== MENU FIXITNOW SERVICE ===" << endl;
    cout << "1. Adaugare Angajat" << endl;
    cout << "2. Adaugare Cerere Reparatie" << endl;
    cout << "3. Afisare Angajati si Salarii" << endl;
    cout << "4. Simulare Alocare (Pas cu Pas)" << endl;
    cout << "5. Modificare Angajat" << endl;
    cout << "6. Gestiune electrocasnice" << endl;
    cout << "7. Incarca date din fisiere" << endl;
    cout << "8. Genereaza rapoarte CSV" << endl;
    cout << "0. Iesire" << endl;
    cout << "Optiune: ";
}

int main()
{
    Service &svc = Service::getInstance();

    tm data{};
    data.tm_year = 120; // 2020
    Tehnician *t1 = new Tehnician("Popescu", "Ion", "1900101123456", data, "Brasov");
    t1->adaugaSpecializare("TV", "Samsung");
    svc.adaugaAngajat(t1);

    int optiune;
    do
    {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        afisareMeniu();
        cin >> optiune;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (optiune)
        {
        case 1:
        {
            string tip, nume, pren, cnp, oras;
            cout << "Tip (T/R/S): ";
            cin >> tip;
            cout << "Nume: ";
            cin >> nume;
            cout << "Prenume: ";
            cin >> pren;
            cout << "CNP: ";
            cin >> cnp;
            cout << "Oras: ";
            cin >> oras;

            tm dataAzi{};
            time_t t = time(0);
            tm *now = localtime(&t);
            dataAzi = *now;
            try
            {
                if (tip == "T")
                {
                    Tehnician *tehnicianNou = new Tehnician(nume, pren, cnp, dataAzi, oras);
                    cout << "\n--- Adaugare Specializari Tehnician ---" << endl;
                    char continua = 'y';
                    while (continua == 'y' || continua == 'Y')
                    {
                        string tipAparat, marcaAparat;
                        cout << "Tip aparat (ex: TV, Frigider): ";
                        cin >> tipAparat;
                        cout << "Marca (ex: Samsung, Arctic): ";
                        cin >> marcaAparat;

                        tehnicianNou->adaugaSpecializare(tipAparat, marcaAparat);

                        cout << "Mai adaugi o specializare? (y/n): ";
                        cin >> continua;
                    }
                    svc.adaugaAngajat(tehnicianNou);
                }
                else if (tip == "R" || tip == "r")
                    svc.adaugaAngajat(new Receptioner(nume, pren, cnp, dataAzi, oras));
                else if (tip == "S" || tip == "s")
                    svc.adaugaAngajat(new Supervizor(nume, pren, cnp, dataAzi, oras));
                else
                    throw invalid_argument("Tip de angajat invalid");

                cout << "Angajat adaugat cu succes!" << endl;
            }
            catch (const exception &e)
            {
                cout << "EROARE la adaugare: " << e.what() << endl;
            }
            break;
        }
        case 2:
        {
            int tipAparat;
            cout << "Selectati tipul (1-TV, 2-Frigider, 3-Masina Spalat): ";
            cin >> tipAparat;

            string marca, model;
            int an;
            double pret;

            cout << "Marca: ";
            cin >> marca;
            cout << "Model: ";
            cin >> model;
            cout << "An fabricatie: ";
            cin >> an;
            cout << "Pret catalog: ";
            cin >> pret;

            Electrocasnic *electrocasnicNou = nullptr;

            if (tipAparat == 1)
            {
                string diag;
                cout << "Diagonala (ex: 100cm): ";
                cin >> diag;
                electrocasnicNou = new Televizor(marca, model, an, pret, diag);
            }
            else if (tipAparat == 2)
            {
                int areCong;
                cout << "Are congelator? (1-Da, 0-Nu): ";
                cin >> areCong;
                electrocasnicNou = new Frigider(marca, model, an, pret, (areCong == 1));
            }
            else if (tipAparat == 3)
            {
                int cap;
                cout << "Capacitate (kg): ";
                cin >> cap;
                electrocasnicNou = new MasinaSpalat(marca, model, an, pret, cap);
            }
            else
            {
                cout << "Tip de aparat invalid! Cererea anulata." << endl;
                break;
            }

            int complexitate;
            cout << "Complexitate defectiune (1-5): ";
            cin >> complexitate;

            tm dataCurenta{};
            svc.adaugaCerere(new CerereReparatie(electrocasnicNou, dataCurenta, complexitate));

            break;
        }
        case 3:
            svc.afiseazaAngajati();
            break;
        case 4:
            cout << "Rulare simulare..." << endl;
            svc.ruleazaSimulare();
            break;
        case 5:
        {
            cout << "     Alege ce modificare doresti sa faci:" << endl;
            cout << "1. Modifica numele" << endl;
            cout << "2. Sterge Angajat" << endl;
            int alegere;
            cin >> alegere;
            switch (alegere)
            {
            case 1:
            {
                string cnp, numeNou, prenumeNou;
                cout << "Introduceti CNP-ul angajatului: ";
                cin >> cnp;
                cout << "Introduceti noul nume: ";
                cin >> numeNou;
                cout << "Introduceti noul prenume: ";
                cin >> prenumeNou;

                svc.modificaNumeAngajat(cnp, numeNou, prenumeNou);
                break;
            }
            case 2:
            {
                string cnp;
                cout << "Introduceti CNP-ul angajatului pe care doriti sa-l stergeti: ";
                cin >> cnp;
                svc.stergeAngajat(cnp);
                break;
            }
            }
            break;
        }
        case 6:
        {
            int subOptiune;
            cout << "\n--- Gestiune Electrocasnice ---" << endl;
            cout << "1. Adauga Model Suportat" << endl;
            cout << "2. Sterge Model Suportat" << endl;
            cout << "3. Afiseaza Toate Modelele Suportate" << endl;
            cout << "4. Afiseaza Statistica Refuzuri (Neserviceabile)" << endl;
            cout << "0. Inapoi" << endl;
            cout << "Alegere: ";
            cin >> subOptiune;

            if (subOptiune == 1)
            {
                string m, mod;
                cout << "Marca: ";
                cin >> m;
                cout << "Model: ";
                cin >> mod;
                svc.adaugaModelSuportat(m, mod);
            }
            else if (subOptiune == 2)
            {
                string m, mod;
                cout << "Marca: ";
                cin >> m;
                cout << "Model: ";
                cin >> mod;
                svc.stergeModelSuportat(m, mod);
            }
            else if (subOptiune == 3)
            {
                svc.afiseazaModeleSuportate();
            }
            else if (subOptiune == 4)
            {
                svc.afiseazaStatisticaRefuzuri();
            }
            break;
        }
        case 7:
        {
            // 1. Modele
            cout << "1. Incarcare modele..." << endl;
            svc.incarcaModeleDinFisier("./tests/modele.txt");
            cout << endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));

            // 2. Angajati
            cout << "2. Incarcare angajati..." << endl;
            svc.incarcaAngajatiDinFisier("./tests/angajati.txt");
            cout << endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));

            // 3. Cereri
            cout << "3. Incarcare cereri..." << endl;
            svc.incarcaCereriDinFisier("./tests/cereri.txt");
            cout << endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));

            cout << "4. Incarcare specializari tehnicieni..." << endl;
            svc.incarcaSpecializariDinFisier("./tests/specializari.txt");
            cout << endl;

            cout << "Initializare gata! Poti rula simularea (Optiunea 4)." << endl;
            break;
        case 0:
            cout << "La revedere!" << endl;
            break;
        default:
            cout << "Optiune invalida!" << endl;
            break;
        }
        case 8:
            svc.genereazaRapoarte();
            break;
        }
    } while (optiune != 0);
    return 0;
}
