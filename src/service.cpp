#include "Service.h"
#include "supervizor.h"
#include "receptioner.h"
#include "tehnician.h"
#include "electrocasnic.h"
#include "electronice_derivate.h"
#include <string.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <thread>
#include <chrono>

Service *Service::instance = nullptr;

Service &Service::getInstance()
{
    if (!instance)
        instance = new Service();
    return *instance;
}

bool readCSVLine(ifstream &f, vector<string> &out)
{
    out.clear();
    string line;
    if (!getline(f, line))
        return false;

    string field;
    stringstream ss(line);

    while (getline(ss, field, ','))
    {
        field.erase(0, field.find_first_not_of(" \t\r\n"));
        field.erase(field.find_last_not_of(" \t\r\n") + 1);
        out.push_back(field);
    }
    return true;
}

void Service::adaugaAngajat(Angajat *a)
{
    angajati.push_back(a);
}
void Service::stergeAngajat(string cnp_dat)
{
    bool gasit = false;
    for (auto it = angajati.begin(); it != angajati.end(); ++it)
    {
        if ((*it)->getCNP() == cnp_dat)
        {
            gasit = true;

            cout << "Sunteti sigur ca doriti stergerea din sistem a angajatului "
                 << (*it)->getNume() << " " << (*it)->getPrenume() << "? (Y/N): ";
            string raspuns;
            cin >> raspuns;

            if (raspuns == "Y" || raspuns == "y")
            {
                delete *it;
                angajati.erase(it);
                cout << "Angajatul a fost sters cu succes." << endl;
            }
            else
            {
                cout << "Stergerea a fost anulata." << endl;
            }
            return;
        }
    }

    if (!gasit)
    {
        cout << "Angajatul cu CNP-ul dat nu a fost gasit in sistem." << endl;
    }
}
void Service::afiseazaAngajati() const
{
    for (auto a : angajati)
    {
        a->afisare();
        cout << " Salariu curent: " << a->calculeazaSalariu() << endl;
    }
}

void Service::modificaNumeAngajat(string cnpCautat, string numeNou, string prenumeNou)
{
    bool gasit = false;
    for (auto ang : angajati)
    {
        if (ang->getCNP() == cnpCautat)
        {
            ang->modificaNume(numeNou, prenumeNou);
            cout << "Numele a fost actualizat cu succes." << endl;
            gasit = true;
            break;
        }
    }
    if (!gasit)
    {
        cout << "Nu s-a gasit niciun angajat cu CNP-ul: " << cnpCautat << endl;
    }
}

void Service::simularePas()
{
    static int timp = 0;
    timp++;
    cout << "\n--- [Timp " << timp << "] ---" << endl;

    for (auto ang : angajati)
    {
        Tehnician *t = dynamic_cast<Tehnician *>(ang);
        if (t)
        {
            // Procesare cereri active (acceseaza vectorul intern printr-o metoda sau friend class)
            // Nota: Pentru simplitate, presupunem o metoda publica in Tehnician sau acces direct
            // Aici ar trebui sa iterezi prin cererile active ale tehnicianului, dar vectorul e privat in header-ul tau.
            // Solutie: Adauga in Tehnician: vector<CerereReparatie*>& getCereriActive() { return cereriActive; }
        }
    }

    // Alocare cereri din asteptare
    if (!cereriAsteptare.empty())
    {
        CerereReparatie *c = cereriAsteptare.front();

        Tehnician *bestTech = nullptr;
        double minLoad = 999999;

        for (auto ang : angajati)
        {
            Tehnician *t = dynamic_cast<Tehnician *>(ang);
            // Accesam private members prin metode get
            // Electrocasnicul trebuie accesat din cerere (adauga getAparat in CerereReparatie)
            // if (t && t->poatePreluaCerere() && t->poateRepara(tip, marca)) { ... }
        }
    }
}

bool Service::verificaStaffMinim() const
{
    int nrTehnicieni = 0;
    int nrReceptioneri = 0;
    int nrSupervizori = 0;

    for (auto ang : angajati)
    {
        if (dynamic_cast<Tehnician *>(ang))
            nrTehnicieni++;
        else if (dynamic_cast<Receptioner *>(ang))
            nrReceptioneri++;
        else if (dynamic_cast<Supervizor *>(ang))
            nrSupervizori++;
    }

    if (nrTehnicieni < 3 || nrReceptioneri < 1 || nrSupervizori < 1)
    {
        cout << "\n[EROARE CRITICA] Service-ul nu poate functiona!" << endl;
        cout << "Necesar: Min 3 Tehnicieni, 1 Receptioner, 1 Supervizor." << endl;
        cout << "Curent: " << nrTehnicieni << " T, " << nrReceptioneri << " R, " << nrSupervizori << " S." << endl;
        return false;
    }
    return true;
}

void Service::adaugaCerere(CerereReparatie *c)
{
    Electrocasnic *el = c->getAparat();
    if (verificaCompatibilitate(el->getMarca(), el->getModel()))
    {
        cereriAsteptare.push(c);
        cout << "[INFO] Cerere inregistrata cu succes (ID: " << c->getId() << ")" << endl;
    }
    else
    {
        cout << "[ATENTIE] Modelul " << el->getMarca() << " " << el->getModel()
             << " nu este suportat de service!" << endl;
        inregistreazaCerereRespinsa(el->getMarca(), el->getModel());
        delete c;
    }
}

void Service::ruleazaSimulare()
{

    if (!verificaStaffMinim())
    {
        return;
    }
    cout << "\n=== START SIMULARE ===" << endl;

    int timp = 0;
    bool activitateInCurs = true;

    while (activitateInCurs)
    {
        timp++;
        cout << "\n--- [Timp " << timp << "] ---" << endl;
        activitateInCurs = false; // Presupunem ca am terminat, daca nu gasim nimic de facut

        // 1. PROCESARE REPARATII ACTIVE (Tehnicienii lucreaza)
        for (auto ang : angajati)
        {
            Tehnician *t = dynamic_cast<Tehnician *>(ang);
            if (t)
            {
                // Presupunem ca am adaugat metoda publica in Tehnician:
                // vector<CerereReparatie*>& getCereriActive();
                // Daca nu ai acces direct, trebuie sa adaugi o metoda in Tehnician "proceseazaTic()"

                // Varianta simplificata: Tehnicianul are o metoda care avanseaza munca
                // Vom implementa o metoda ajutatoare in Tehnician mai jos
                t->simuleazaTic();

                if (t->areCereriActive())
                    activitateInCurs = true;
            }
        }

        // 2. ALOCARE CERERI DIN ASTEPTARE
        if (!cereriAsteptare.empty())
        {
            activitateInCurs = true; // Mai avem cereri de alocat

            // Luam prima cerere
            CerereReparatie *cerere = cereriAsteptare.front();
            Electrocasnic *ap = cerere->getAparat();

            Tehnician *celMaiBunTech = nullptr;

            // Cautam un tehnician potrivit
            for (auto ang : angajati)
            {
                Tehnician *t = dynamic_cast<Tehnician *>(ang);
                if (t)
                {
                    // Verificam 3 conditii:
                    // A. Sa stie sa repare (Marca + Tip)
                    // B. Sa aiba < 3 cereri active
                    // C. (Optional) Sa fie cel mai liber

                    bool compatibil = t->poateRepara(ap->getTip(), ap->getMarca());
                    bool areLoc = t->poatePreluaCerere(); // < 3 cereri

                    if (compatibil && areLoc)
                    {
                        celMaiBunTech = t;
                        break; // L-am gasit pe primul disponibil (poti rafina logica pt "incarcare egala")
                    }
                }
            }

            if (celMaiBunTech)
            {
                celMaiBunTech->adaugaCerere(cerere);
                cereriAsteptare.pop(); // Scoatem din coada de asteptare
                cout << ">> Cererea ID " << cerere->getId() << " (" << ap->getMarca()
                     << ") alocata tehnicianului " << celMaiBunTech->getNume() << endl;
            }
            else
            {
                cout << ">> Cererea ID " << cerere->getId() << " ramane in asteptare (niciun tehnician disponibil)." << endl;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        if (cereriAsteptare.empty())
        {
            bool cinevaLucreaza = false;
            for (auto ang : angajati)
            {
                Tehnician *t = dynamic_cast<Tehnician *>(ang);
                if (t && t->areCereriActive())
                    cinevaLucreaza = true;
            }
            if (!cinevaLucreaza)
                activitateInCurs = false;
        }
    }
    cout << "\n=== SIMULARE FINALIZATA ===" << endl;
}

void Service::adaugaModelSuportat(const string &marca, const string &model)
{
    vector<string> &modele = modeleSuportate[marca];
    for (const string &m : modele)
    {
        if (m == model)
        {
            cout << "Modelul " << model << " de la " << marca << " exista deja." << endl;
            return;
        }
    }
    modele.push_back(model);
    cout << "Adaugat cu succes: " << marca << " - " << model << endl;
}

void Service::stergeModelSuportat(const string &marca, const string &model)
{
    if (modeleSuportate.find(marca) != modeleSuportate.end())
    {
        vector<string> &modele = modeleSuportate[marca];
        auto it = remove(modele.begin(), modele.end(), model);
        if (it != modele.end())
        {
            modele.erase(it, modele.end());
            cout << "Model sters cu succes." << endl;
            // daca nu mai sunt modele sterg marca
            if (modele.empty())
            {
                modeleSuportate.erase(marca);
            }
        }
        else
        {
            cout << "Modelul nu a fost gasit." << endl;
        }
    }
    else
    {
        cout << "Marca nu exista in baza de date." << endl;
    }
}

bool Service::verificaCompatibilitate(const string &marca, const string &model)
{
    if (modeleSuportate.find(marca) != modeleSuportate.end())
    {
        const vector<string> &modele = modeleSuportate.at(marca);
        for (const string &m : modele)
        {
            if (m == model)
                return true;
        }
    }
    return false;
}

void Service::afiseazaModeleSuportate() const
{
    cout << "\n=== LISTA ELECTROCASNICE SUPORTATE ===" << endl;
    if (modeleSuportate.empty())
    {
        cout << "Nu exista modele configurate in sistem." << endl;
        return;
    }

    for (const auto &pereche : modeleSuportate)
    {
        cout << "Marca: " << pereche.first << endl;
        cout << "   Modele: ";
        for (const auto &model : pereche.second)
        {
            cout << model << ", ";
        }
        cout << endl;
    }
}

void Service::inregistreazaCerereRespinsa(const string &marca, const string &model)
{
    string key = marca + " " + model;
    statisticaRefuzuri[key]++;
}

void Service::afiseazaStatisticaRefuzuri() const
{
    cout << "\n=== STATISTICA CERERI REFUZATE (Neserviceabile) ===" << endl;
    if (statisticaRefuzuri.empty())
    {
        cout << "Nu exista cereri refuzate inregistrate." << endl;
        return;
    }
    vector<pair<string, int>> listaSortata(statisticaRefuzuri.begin(), statisticaRefuzuri.end());

    sort(listaSortata.begin(), listaSortata.end(),
         [](const pair<string, int> &a, const pair<string, int> &b)
         {
             return a.second > b.second;
         });

    cout << "Aparat (Marca Model) | Numar Solicitari" << endl;
    cout << "---------------------------------------" << endl;
    for (const auto &elem : listaSortata)
    {
        cout << elem.first << " \t\t | " << elem.second << endl;
    }
}

void Service::incarcaCereriDinFisier(const string& numeFisier) {
    ifstream file(numeFisier);
    if (!file) {
        cout << "Nu pot deschide: " << numeFisier << endl;
        return;
    }

    vector<string> row;
    int contor = 0;
    int nrlinie = 0; 

    while (readCSVLine(file, row)) {
        nrlinie++;

        if (row.empty()) continue;

        if (row.size() != 7) {
            cout << "Eroare la citire: Cerere invalida pe linia " << nrlinie 
                 << ", cauza: Numar incorect de coloane (asteptat 7)" << endl;
            continue;
        }

        try {
            string tip = row[0];
            string marca = row[1];
            string model = row[2];
            int an = stoi(row[3]);
            double pret = stod(row[4]);
            string detaliu = row[5];
            int complexitate = stoi(row[6]);

            Electrocasnic* e = nullptr;

            if (tip == "TV")
                e = new Televizor(marca, model, an, pret, detaliu);
            else if (tip == "Frigider")
                e = new Frigider(marca, model, an, pret, detaliu == "1");
            else if (tip == "MasinaSpalat")
                e = new MasinaSpalat(marca, model, an, pret, stoi(detaliu));
            else {
                throw invalid_argument("Tip aparat necunoscut (" + tip + ")");
            }

            if (e) {
                tm now{};
                adaugaCerere(new CerereReparatie(e, now, complexitate));
                contor++;
            }
        }
        catch (const exception& e) {
            cout << "Eroare la citire: Cerere invalida pe linia " << nrlinie 
                 << ", cauza: " << e.what() << endl;
        }
    }

    cout << "[OK] " << contor << " cereri incarcate\n";
}

void Service::incarcaModeleDinFisier(const string &numeFisier)
{
    ifstream file(numeFisier);
    if (!file)
    {
        cout << "Nu pot deschide fisierul: " << numeFisier << endl;
        return;
    }

    vector<string> row;
    int contor = 0;

    while (readCSVLine(file, row))
    {
        if (row.size() != 2)
        {
            cout << "Linie invalida in modele, ignorata\n";
            continue;
        }

        string marca = row[0];
        string model = row[1];

        if (marca.empty() || model.empty())
        {
            cout << "Marca sau model gol\n";
            continue;
        }

        adaugaModelSuportat(marca, model);
        contor++;
    }

    cout << "[OK] " << contor << " modele incarcate\n";
}

void Service::incarcaAngajatiDinFisier(const string &numeFisier)
{
    ifstream file(numeFisier);
    if (!file)
    {
        cout << "Nu pot deschide: " << numeFisier << endl;
        return;
    }

    vector<string> row;
    int contor = 0;
    int nrlinie = 0;
    while (readCSVLine(file, row))
    {
        nrlinie++;
        if (row.size() != 5)
        {
            cout << "Eroare la citire: Angajat invalid pe linia " << nrlinie
                 << ", cauza: Numar incorect de coloane (asteptat 5)" << endl;
            continue;
        }

        string tip = row[0];
        string nume = row[1];
        string pren = row[2];
        string cnp = row[3];
        string oras = row[4];

        tm data{};
        time_t now = time(nullptr);
        data = *localtime(&now);

        try
        {
            if (tip == "T")
                adaugaAngajat(new Tehnician(nume, pren, cnp, data, oras));
            else if (tip == "R")
                adaugaAngajat(new Receptioner(nume, pren, cnp, data, oras));
            else if (tip == "S")
                adaugaAngajat(new Supervizor(nume, pren, cnp, data, oras));
            else
            {
                throw invalid_argument("Tip de angajat necunoscut (" + tip + ")");
                cout<<endl;
            }

            contor++;
        }
        catch (const exception& e)
        {
            cout << "Eroare la citire: Angajat invalid pe linia " << nrlinie << ", cauza: " << e.what()<<endl;
        }
    }

    cout << "[OK] " << contor << " angajati incarcati\n";
}

void Service::incarcaSpecializariDinFisier(const string& numeFisier) {
    ifstream file(numeFisier);
    if (!file) {
        cout << "Nu pot deschide fisierul: " << numeFisier << endl;
        return;
    }

    vector<string> row;
    int contor = 0;
    int numarLinie = 0; 

    while (readCSVLine(file, row)) {
        numarLinie++;
        
        if (row.empty()) continue;

        if (row.size() != 3) {
            cout << "Eroare la citire: Specializare invalida pe linia " << numarLinie 
                 << ", cauza: Numar incorect de coloane (asteptat 3)" << endl;
            continue;
        }

        string cnp   = row[0];
        string tip   = row[1];
        string marca = row[2];

        bool angajatGasit = false;
        bool esteTehnician = false;

        for (auto ang : angajati) {
            if (ang->getCNP() == cnp) {
                angajatGasit = true;
                Tehnician* t = dynamic_cast<Tehnician*>(ang);
                
                if (t) {
                    t->adaugaSpecializare(tip, marca);
                    contor++;
                    esteTehnician = true;
                }
                break; 
            }
        }

        if (!angajatGasit) {
            cout << "Eroare la citire: Specializare invalida pe linia " << numarLinie 
                 << ", cauza: CNP inexistent in sistem (" << cnp << ")" << endl;
        }
        else if (!esteTehnician) {
            cout << "Eroare la citire: Specializare invalida pe linia " << numarLinie 
                 << ", cauza: Angajatul cu acest CNP nu este Tehnician" << endl;
        }
    }

    cout << "[OK] " << contor << " specializari incarcate\n";
}

Service::~Service()
{
    for (auto a : angajati)
        delete a;
    while (!cereriAsteptare.empty())
    {
        delete cereriAsteptare.front();
        cereriAsteptare.pop();
    }
}