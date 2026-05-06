/*************************************************************************
                           AuthenticateService  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <AuthenticateService> (fichier AuthenticateService.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "AuthenticateService.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
bool AuthenticateService::login(const std::string& id, Role role, User& outUser)
{
    bool trouve = false;
    // recherche de l'utilisateur ID dans tous les CSV avec le data manager
    if (trouve){
        // création tempUSer = 
        tempUSer = 
        outUser = tempUSer;
        return true;
    }

    else {
        return false;
    }
}