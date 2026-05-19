/*************************************************************************
                           AuthenticateService  -  description
                             -------------------
    début                : 19/05/2026
    copyright            : (C) 2026 par tautret
    e-mail               : tom.autret@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe <AuthenticateService> (fichier AuthenticateService.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "AuthenticateService.h"
#include "../model/DataContainer.h"
#include "../model/Role.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
PrivateUser* AuthenticateService::loginPrivate(DataContainer& dc, string& id)
{
    map<string, PrivateUser*> listPrivateUser = dc.getAllUsers();
    map<string, PrivateUser*>::const_iterator it = listPrivateUser.find(id);

    if (it != listPrivateUser.end()){
        return it->second;
    }
    else {
        return nullptr;
    }
}

Provider* AuthenticateService::loginProvider(DataContainer& dc, string& id)
{
    map<string, Provider*> listProvider = dc.getAllProviders();
    map<string, Provider*>::const_iterator it = listProvider.find(id);

    if (it != listProvider.end()){
        return it->second;
    }
    else {
        return nullptr;
    }
}

GovernmentAgency* AuthenticateService::loginGovernmentAgency(string& id)
{
    return new GovernmentAgency("admin", GOVERNMENT_AGENCY,"admin");
}


//-------------------------------------------- Constructeurs - destructeur
AuthenticateService::AuthenticateService()
{
    #ifdef MAP
        cout <<"Appel au constructeur de <AuthenticateService>"<< endl;
    #endif
}

AuthenticateService::~AuthenticateService()
{
   #ifdef MAP
        cout <<"Appel au destructeur de <AuthenticateService>"<< endl;
    #endif 
}
