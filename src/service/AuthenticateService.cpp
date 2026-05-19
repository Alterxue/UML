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

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
bool loginPrivate(DataContainer& dc, string& id, Role role)
{
    map<string, PrivateUser*> listPrivateUser = dc.getAllUsers();
    if ((dc.getAllUsers()).find(id)){
        PrivateUser* privateUser = new PrivateUser(id, role);
        return privateUser;
    }

    else {
        return nullptr;
    }
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
