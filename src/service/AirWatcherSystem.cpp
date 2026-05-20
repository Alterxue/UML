/*************************************************************************
                           AirWatcherSystem  -  description
                             -------------------
    début                : 19/05/2026
    copyright            : (C) 19/05/2026 par tautret
    e-mail               : tom.autret@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe <AirWatcherSystem> (fichier AirWatcherSystem.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <string>

//------------------------------------------------------ Include personnel
#include "AirWatcherSystem.h"
#include "../model/DataContainer.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// Nom de la méthode
// Algorithme :
//
// {
// } //----- Fin de méthode

bool AirWatcherSystem::setPrivateUser(DataContainer& dc, string& id)
{
    PrivateUser* privateUser = authService->loginPrivate(dc, id);
    if (privateUser == nullptr){
        return false;
    }
    return true;
} //----- Fin de setPrivateUser

bool AirWatcherSystem::setProvider(DataContainer& dc, std::string& id)
{
    Provider* provider = authService->loginProvider(dc, id);
    if (provider == nullptr){
        return false;
    }
    return true;
} //----- Fin de setProvdider

bool AirWatcherSystem::setGovernmentAgency(DataContainer& dc, std::string& id)
{
    GovernmentAgency* govagency = authService->loginGovernmentAgency(id);
    if (govagency == nullptr){
        return false;
    }
    return true;
} //----- Fin de setGovernmentAgency

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
AirWatcherSystem::AirWatcherSystem ()
// Algorithme :
{
    #ifdef MAP
    cout << "Appel au constructeur <AirWatcherSystem>" << endl;
    #endif
    currentPrivateUser = nullptr;
    currentProvider = nullptr;
    currentGovernmentAgency = nullptr;
    statsService = new StatisticsService();
    securityService = new SecurityService();
    dataService = new DataService();
    authService = new AuthenticateService();
} //----- Fin de AirWatcherSystem 


AirWatcherSystem::~AirWatcherSystem ( )
// Algorithme :
{
    #ifdef MAP
        cout << "Appel au destructeur de <AirWatcherSystem>" << endl;
    #endif
    if (currentPrivateUser != nullptr){
        delete currentPrivateUser;
    }
    if (currentProvider != nullptr){
        delete currentProvider;
    }
    if (currentGovernmentAgency != nullptr){
        delete currentGovernmentAgency;
    }
    delete statsService;
    delete securityService;
    delete dataService;
    delete authService;
} //----- Fin de ~AirWatcherSystem


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

