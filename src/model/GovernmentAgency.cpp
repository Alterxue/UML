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
#include <iostream>
#include <string>
using namespace std;

//------------------------------------------------------ Include personnel
#include "GovernmentAgency.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void GovernmentAgency::manageSystem()
{
    // Implementation for managing the system
}

void GovernmentAgency::flagSensors(Sensor & sensor)
{
    sensor.setReliability(false);
}

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