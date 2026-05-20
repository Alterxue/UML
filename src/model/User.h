/*************************************************************************
                           User  -  description
                             -------------------
    début                : 05/05/2026
    copyright            : (C) 2026 par aeliasmene
    e-mail               : alex.eliasmenet@gmail.com
*************************************************************************/

//---------- Interface de la classe <User> (fichier User.h) ----------------
#if ! defined ( USER_H )
#define USER_H


//--------------------------------------------------- Interfaces utilisées
#include "Role.h"
#include <string>
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <User>
//
//
//------------------------------------------------------------------------

class User 
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //
    std::string getUserID() const;

    Role getRole() const;

//------------------------------------------------- Surcharge d'opérateurs



//-------------------------------------------- Constructeurs - destructeur
    User (const User & unUser);
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    User (std::string userID, Role role);
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~User ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    std::string userID;
    Role role;
};

//-------------------------------- Autres définitions dépendantes de <User>

#endif // USER_H