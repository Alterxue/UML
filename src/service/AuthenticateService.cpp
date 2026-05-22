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
    const map<string, PrivateUser*>& listPrivateUser = dc.getAllUsers();
    map<string, PrivateUser*>::const_iterator it = listPrivateUser.find(id);

    if (it != listPrivateUser.end()){
        return it->second;
    }
    else {
        return nullptr;
    }
} //----- Fin de loginPrivate

Provider* AuthenticateService::loginProvider(DataContainer& dc, string& id)
{
    const map<string, Provider*>& listProvider = dc.getAllProviders();
    map<string, Provider*>::const_iterator it = listProvider.find(id);

    if (it != listProvider.end()){
        return it->second;
    }
    else {
        return nullptr;
    }
} //----- Fin de loginProvider

GovernmentAgency* AuthenticateService::loginGovernmentAgency(string& id)
{
    if (id == "admin"){
        return new GovernmentAgency(id, GOVERNMENT_AGENCY,"GovernmentAgency");
    }
    else {
        return nullptr;
    }
} //----- Fin de loginGovernmentAgency
    
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
