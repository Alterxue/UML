/*************************************************************************
                           AirWatcherSystem  -  description
                             -------------------
    debut                : 19/05/2026
    copyright            : (C) 19/05/2026 par tautret
    e-mail               : tom.autret@insa-lyon.fr
*************************************************************************/

//---------- Realisation de la classe <AirWatcherSystem> (fichier AirWatcherSystem.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include systeme
using namespace std;
#include <iostream>
#include <string>

//------------------------------------------------------ Include personnel
#include "AirWatcherSystem.h"
#include "../model/DataContainer.h"
#include "../model/PrivateUser.h"
#include "../model/Provider.h"
#include "../model/GovernmentAgency.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Methodes publiques

PrivateUser * AirWatcherSystem::getCurrentPrivateUser() {
    return currentPrivateUser;
}

Provider * AirWatcherSystem::getCurrentProvider() {
    return currentProvider;
}

GovernmentAgency * AirWatcherSystem::getCurrentGovernmentAgency() {
    return currentGovernmentAgency;
}

User * AirWatcherSystem::getCurrentUser() {
    return currentUser;
}

bool AirWatcherSystem::setPrivateUser(DataContainer& dc, const std::string& id)
{
    clearCurrentUser();

    std::string idCopy = id;
    PrivateUser* privateUser = authService->loginPrivate(dc, idCopy);
    if (privateUser == nullptr) {
        return false;
    }

    currentPrivateUser = privateUser;
    currentUser = privateUser;
    return true;
} //----- Fin de setPrivateUser

bool AirWatcherSystem::setProvider(DataContainer& dc, const std::string& id)
{
    clearCurrentUser();

    std::string idCopy = id;
    Provider* provider = authService->loginProvider(dc, idCopy);
    if (provider == nullptr) {
        return false;
    }

    currentProvider = provider;
    currentUser = provider;
    return true;
} //----- Fin de setProvider

bool AirWatcherSystem::setGovernmentAgency(const std::string& id)
{
    clearCurrentUser();

    std::string idCopy = id;
    GovernmentAgency* agency = authService->loginGovernmentAgency(idCopy);
    if (agency == nullptr) {
        return false;
    }

    currentGovernmentAgency = agency;
    currentUser = agency;
    return true;
} //----- Fin de setGovernmentAgency

void AirWatcherSystem::logout()
{
    clearCurrentUser();
}

void AirWatcherSystem::clearCurrentUser()
{
    if (currentGovernmentAgency != nullptr) {
        delete currentGovernmentAgency;
    }

    currentPrivateUser = nullptr;
    currentProvider = nullptr;
    currentGovernmentAgency = nullptr;
    currentUser = nullptr;
}

//------------------------------------------------- Surcharge d'operateurs

//-------------------------------------------- Constructeurs - destructeur
AirWatcherSystem::AirWatcherSystem ()
// Algorithme :
{
    #ifdef MAP
    cout << "Appel au constructeur <AirWatcherSystem>" << endl;
    #endif

    authService = new AuthenticateService();
    currentPrivateUser = nullptr;
    currentProvider = nullptr;
    currentGovernmentAgency = nullptr;
    currentUser = nullptr;
} //----- Fin de AirWatcherSystem


AirWatcherSystem::~AirWatcherSystem ( )
// Algorithme :
{
    #ifdef MAP
        cout << "Appel au destructeur de <AirWatcherSystem>" << endl;
    #endif

    clearCurrentUser();
    delete authService;
} //----- Fin de ~AirWatcherSystem


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Methodes protegees
