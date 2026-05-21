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
#include <string>

#include "Role.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <User>
// Cette classe abstraite représente un utilisateur du système, qui peut être un 
// utilisateur privé, un fournisseur ou une agence gouvernementale. 
// Elle contient des informations telles que l'identifiant de l'utilisateur 
// et son rôle dans le système.
//------------------------------------------------------------------------

class User 
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    std::string getUserID() const;
    // Mode d'emploi :
    // Retourne l'identifiant de l'utilisateur.

    Role getRole() const;
    // Mode d'emploi :
    // Retourne le rôle de l'utilisateur dans le système.

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
    User (std::string userID, Role role);
    // Mode d'emploi :
    // Constructeur de la classe User.

    virtual ~User () = 0;
    // Mode d'emploi :
    // Destructeur virtuel de la classe User.
//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    std::string userID;
    Role role;
};

//-------------------------------- Autres définitions dépendantes de <User>

#endif // USER_H