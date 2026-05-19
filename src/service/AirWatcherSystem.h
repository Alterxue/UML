/*************************************************************************
                           AirWatcherSystem  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <AirWatcherSystem> (fichier AirWatcherSystem.h) ----------------
#if ! defined ( AIRWATCHERSYSTEM_H)
#define AIRWATCHERSYSTEM_H

//--------------------------------------------------- Interfaces utilisées
#include <string>

#include "DataService.h"
#include "StatisticsService.h"
#include "SecurityService.h"
#include "AuthenticateService.h"
#include "../model/User.h"
#include "../model/Role.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <AirWatcherSystem>
// 
//
//------------------------------------------------------------------------

class AirWatcherSystem
{
//----------------------------------------------------------------- PUBLIC
public:
//----------------------------------------------------- Méthodes publiques
    // Nom de la méthode
    // Mode d'emploi :
    //
    // Contrat :
    
    bool setPrivateUser(DataContainer& dc,std::string& id);
    // appelle le loginprivate du auth et va set en fonction de l'objet renvoyé par le login de auth

    bool setProvider(DataContainer& dc, std::string& id);

    bool setGovernmentAgency(DataContainer& dc, std::string& id);

//-------------------------------------------- Constructeurs - destructeur
    AirWatcherSystem();
    // Mode d'emploi :
    //
    // Contrat :
    //
    
    ~AirWatcherSystem(); 
    // Mode d'emploi :
    //
    // Contrat :
    //
 
//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Attributs protégés
    PrivateUser* currentPrivateUser;
    Provider* currentProvider;
    GovernmentAgency* currentGovernmentAgency;
    StatisticsService* statsService;
    SecurityService* securityService;
    DataService* dataService;
    AuthenticateService* authService;
};


#endif 

