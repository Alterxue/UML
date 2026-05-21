/*************************************************************************
                           GovernmentAgency  -  description
                             -------------------
    début                : 05/05/2026
    copyright            : (C) 2026 par aeliasmene
    e-mail               : alex.eliasmenet@gmail.com
*************************************************************************/

//---------- Réalisation de la classe <GovernmentAgency> (fichier GovernmentAgency.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <string>

//------------------------------------------------------ Include personnel
#include "GovernmentAgency.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
string GovernmentAgency::getAgencyID() const
{
    return agencyID;
} //----- Fin de getAgencyID

//------------------------------------------------- Surcharge d'opérateurs


//-------------------------------------------- Constructeurs - destructeur
GovernmentAgency::GovernmentAgency (string userID, Role role,string a_agencyID) : User(userID, role), agencyID(a_agencyID)
{
    #ifdef MAP
        cout << "Appel au constructeur de <GovernmentAgency>" << endl;
    #endif
}

GovernmentAgency::~GovernmentAgency ()
{
    #ifdef MAP
        cout << "Appel au destructeur de <GovernmentAgency>" << endl;
    #endif
} //----- Fin de ~GovernmentAgency


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées