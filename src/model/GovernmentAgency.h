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

#include <string>
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <GovernmentAgency>
// Représente une agence gouvernementale
//------------------------------------------------------------------------

class GovernmentAgency : public User
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    std::string getAgencyID() const;
    // Mode d'emploi :
    // Retourne l'ID de l'agence gouvernementale
    
//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
    GovernmentAgency (std::string userID, Role role, std::string agencyID);
    // Mode d'emploi :
    // Construction d'une agence gouvernementale à partir de son ID, de son rôle et de son ID d'agence

    ~GovernmentAgency ( );
    // Mode d'emploi :
    // Destructeur de l'agence gouvernementale

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    std::string agencyID;
};

//-------------------------------- Autres définitions dépendantes de <GovernmentAgency>

#endif // GOVERNMENTAGENCY_H