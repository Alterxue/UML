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
#include <iostream>
#include "Role.h"
#include <string>
using namespace std;

//------------------------------------------------------ Include personnel
#include "User.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

string User::getUserID() const
{
    return userID;
}

Role User::getRole() const
{
    return role;
}

//------------------------------------------------- Surcharge d'opérateurs



//-------------------------------------------- Constructeurs - destructeur
User::User (const User & unUser)
// Algorithme :
{
    #ifdef MAP
        cout << "Appel au constructeur de copie de <User>" << endl;
    #endif
} //----- Fin de User (constructeur de copie)



User::User(string userID, Role role) : userID(userID),role(role)
{
    #ifdef MAP
        cout << "Appel au constructeur de <User>" << endl;
    #endif
}

User::~User ()
// Algorithme :
{
    #ifdef MAP
        cout << "Appel au destructeur de <User>" << endl;
    #endif
} //----- Fin de ~User


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

