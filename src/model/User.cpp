/*************************************************************************
                           User  -  description
                             -------------------
    début                : 05/05/2026
    copyright            : (C) 2026 par aeliasmene
    e-mail               : alex.eliasmenet@gmail.com
*************************************************************************/

//---------- Réalisation de la classe <User> (fichier User.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <string>

//------------------------------------------------------ Include personnel
#include "User.h"
#include "Role.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
string User::getUserID() const
{
    return userID;
} //----- Fin de getUserID

Role User::getRole() const
{
    return role;
} //----- Fin de getRole

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
User::User(string userID, Role role) : userID(userID),role(role)
{
    #ifdef MAP
        cout << "Appel au constructeur de <User>" << endl;
    #endif
}

User::~User ()
{
    #ifdef MAP
        cout << "Appel au destructeur de <User>" << endl;
    #endif
} //----- Fin de ~User

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

