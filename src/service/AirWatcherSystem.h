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
    //

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
    User* currentUser;
    StatisticsService* statsService;
    SecurityService* securityService;
    DataService* dataService
    AuthenticateService* authService;
};


#endif 

