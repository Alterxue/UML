/*************************************************************************
                           AirWatcherSystem  -  description
                             -------------------
    début                : 19/05/2026
    copyright            : (C) 19/05/2026 par tautret
    e-mail               : tom.autret@insa-lyon.fr
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
    // Mode d'emploi :
    // Va initialiser le PrivateUser courrant si il existe
    // et renvoyer true si la connexion a réussi

    bool setProvider(DataContainer& dc, std::string& id);

    bool setGovernmentAgency(std::string& id);

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

