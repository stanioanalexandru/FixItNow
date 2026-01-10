#pragma once
#include <ctime>
#include "Electrocasnic.h"

enum class StatusCerere { ASTEPTARE, ACTIVA, FINALIZATA, INVALIDA };

class CerereReparatie {
    static int generatorId;
    int id;
    Electrocasnic* aparat;
    tm timestamp{};
    int complexitate;
    int durataRamasa;
    double pret;
    StatusCerere status;

public:
    CerereReparatie(Electrocasnic* aparat, tm timp, int complexitate);

    int getId() const;
    int getDurata() const;
    double getPret() const;
    StatusCerere getStatus() const;
    Electrocasnic* getAparat() const { return aparat; }
    void scadeDurata();
    void finalizeaza();
    ~CerereReparatie();
};
