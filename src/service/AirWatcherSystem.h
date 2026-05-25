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

#include "AuthenticateService.h"
#include "../model/User.h"

class DataContainer;
class PrivateUser;
class Provider;
class GovernmentAgency;

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
    User * getCurrentUser();

    bool setPrivateUser(DataContainer& dc, const std::string& id);
    // Mode d'emploi :
    // Va initialiser le PrivateUser courrant si il existe
    // et renvoyer true si la connexion a réussi

    bool setProvider(DataContainer& dc, const std::string& id);

    bool setGovernmentAgency(const std::string& id);

    void logout();

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
    AuthenticateService* authService;
    User* currentUser;

    void clearCurrentUser();
};


#endif 

