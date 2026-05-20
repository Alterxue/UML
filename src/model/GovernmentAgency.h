/*************************************************************************
                           GovernmentAgency  -  description
                             -------------------
    début                : 05/05/2026
    copyright            : (C) 2026 par aeliasmene
    e-mail               : alex.eliasmenet@gmail.com
*************************************************************************/

//---------- Interface de la classe <GovernmentAgency> (fichier GovernmentAgency.h) ----------------
#if ! defined ( GOVERNMENTAGENCY_H )
#define GOVERNMENTAGENCY_H



//--------------------------------------------------- Interfaces utilisées
#include "User.h"
#include "Sensor.h"
#include <string>
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <GovernmentAgency>
//
//
//------------------------------------------------------------------------

class GovernmentAgency : public User
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //

    void manageSystem();
    void flagSensors(Sensor & sensor);
//------------------------------------------------- Surcharge d'opérateurs


//-------------------------------------------- Constructeurs - destructeur
    GovernmentAgency (std::string userID, Role role, std::string agencyID);
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~GovernmentAgency ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    std::string agencyID;
};

//-------------------------------- Autres définitions dépendantes de <User>

#endif // GOVERNMENTAGENCY_H