#include "cerere_reparatie.h"

int CerereReparatie::generatorId = 1;

CerereReparatie::CerereReparatie(Electrocasnic *ap, tm timp, int complexitate): aparat(ap), timestamp(timp), complexitate(complexitate), status(StatusCerere::ASTEPTARE)
{
    id = generatorId++;

    time_t now = time(0);
    tm *ltm = localtime(&now);
    int anCurent = 1900 + ltm->tm_year;
    int vechime = anCurent - aparat->getAnFabricatie();
    if (vechime < 0)
        vechime = 0;
    durataRamasa = vechime * complexitate;
    durataTotala = durataRamasa;
    pret = aparat->getPretCatalog() * durataRamasa;
}

int CerereReparatie::getId() const { return id; }
int CerereReparatie::getDurata() const { return durataRamasa; }
double CerereReparatie::getPret() const { return pret; }
StatusCerere CerereReparatie::getStatus() const { return status; }

void CerereReparatie::scadeDurata()
{
    if (durataRamasa > 0)
    {
        durataRamasa--;
        status = StatusCerere::ACTIVA;
    }
}

void CerereReparatie::finalizeaza()
{
    status = StatusCerere::FINALIZATA;
    durataRamasa = 0;
}

CerereReparatie::~CerereReparatie()
{
    if (aparat != nullptr)
    {
        delete aparat;
        aparat = nullptr;
    }
}